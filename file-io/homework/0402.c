#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdbool.h>
#include "jpeglib.h"

// 解码 JPEG 数据，返回 RGB 数据，并通过参数返回宽、高、每行字节数
char *jpg2rgb(const char *jpgdata, size_t jpgsize,
              int *out_width, int *out_height, int *out_pitch)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // 从内存读取 JPEG 数据
    jpeg_mem_src(&cinfo, (const unsigned char *)jpgdata, jpgsize);

    // 读取 JPEG 头部
    if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) {
        fprintf(stderr, "jpeg_read_header failed\n");
        jpeg_destroy_decompress(&cinfo);
        return NULL;
    }

    // 开始解压
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int channels = cinfo.output_components;   // 通常为 3（RGB）
    int pitch = width * channels;             // 每行字节数

    // 通过参数返回尺寸信息
    if (out_width)  *out_width  = width;
    if (out_height) *out_height = height;
    if (out_pitch)  *out_pitch  = pitch;

    printf("JPEG 宽：%d，高：%d，通道数：%d\n", width, height, channels);

    // 分配 RGB 缓冲区
    unsigned char *rgbdata = (unsigned char *)malloc((size_t)pitch * height);
    if (rgbdata == NULL) {
        fprintf(stderr, "malloc failed\n");
        jpeg_destroy_decompress(&cinfo);
        return NULL;
    }

    // 逐行解码
    while (cinfo.output_scanline < cinfo.output_height) {
        unsigned char *row_ptr[1];
        row_ptr[0] = rgbdata + cinfo.output_scanline * pitch;
        jpeg_read_scanlines(&cinfo, row_ptr, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return (char *)rgbdata;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <jpg-file>\n", argv[0]);
        return 1;
    }

    // 1. 打开 framebuffer
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1) {
        perror("open /dev/fb0");
        return 1;
    }

    // 2. 获取屏幕信息
    struct fb_var_screeninfo lcd_info;
    if (ioctl(lcd_fd, FBIOGET_VSCREENINFO, &lcd_info) == -1) {
        perror("ioctl FBIOGET_VSCREENINFO");
        close(lcd_fd);
        return 1;
    }

    int lcd_width  = lcd_info.xres;
    int lcd_height = lcd_info.yres;
    int lcd_bpp    = lcd_info.bits_per_pixel;   // 通常 32
    int lcd_pitch  = lcd_width * lcd_bpp / 8;   // 每行字节数

    printf("屏幕：%d x %d, bpp=%d\n", lcd_width, lcd_height, lcd_bpp);

    // 3. 映射 framebuffer
    unsigned char *lcd_mem = mmap(NULL,
                                  (size_t)lcd_pitch * lcd_height,
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED,
                                  lcd_fd,
                                  0);
    if (lcd_mem == MAP_FAILED) {
        perror("mmap");
        close(lcd_fd);
        return 1;
    }

    // 清屏（黑色）
    memset(lcd_mem, 0, (size_t)lcd_pitch * lcd_height);

    // 4. 读取 JPEG 文件
    FILE *fp = fopen(argv[1], "rb");   // 使用二进制模式
    if (fp == NULL) {
        perror("fopen");
        munmap(lcd_mem, (size_t)lcd_pitch * lcd_height);
        close(lcd_fd);
        return 1;
    }

    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (file_size <= 0) {
        fprintf(stderr, "文件为空或读取失败\n");
        fclose(fp);
        munmap(lcd_mem, (size_t)lcd_pitch * lcd_height);
        close(lcd_fd);
        return 1;
    }

    // 分配内存并读取整个文件
    char *jpgdata = (char *)malloc(file_size);
    if (jpgdata == NULL) {
        perror("malloc");
        fclose(fp);
        munmap(lcd_mem, (size_t)lcd_pitch * lcd_height);
        close(lcd_fd);
        return 1;
    }

    size_t total_read = 0;
    while (total_read < (size_t)file_size) {
        size_t bytes_read = fread(jpgdata + total_read, 1,
                                  (size_t)file_size - total_read, fp);
        if (bytes_read <= 0) {
            if (ferror(fp)) perror("fread");
            else fprintf(stderr, "文件意外结束\n");
            break;
        }
        total_read += bytes_read;
    }
    fclose(fp);

    if (total_read != (size_t)file_size) {
        fprintf(stderr, "读取文件不完整\n");
        free(jpgdata);
        munmap(lcd_mem, (size_t)lcd_pitch * lcd_height);
        close(lcd_fd);
        return 1;
    }

    // 5. 解码 JPEG
    int jpg_w, jpg_h, jpg_pitch;
    char *rgbdata = jpg2rgb(jpgdata, (size_t)file_size,
                            &jpg_w, &jpg_h, &jpg_pitch);
    if (rgbdata == NULL) {
        fprintf(stderr, "JPEG 解码失败\n");
        free(jpgdata);
        munmap(lcd_mem, (size_t)lcd_pitch * lcd_height);
        close(lcd_fd);
        return 1;
    }

    // 6. 显示 RGB 数据到 framebuffer
    //    注意：这里假设 framebuffer 每像素 4 字节（bpp=32），
    //    且 RGB 顺序与 framebuffer 兼容。
    //    实际项目中需要根据 lcd_info 的颜色偏移量来正确组装像素。
    for (int y = 0; y < lcd_height && y < jpg_h; y++) {
        int lcd_offset = lcd_pitch * y;
        int rgb_offset = jpg_pitch * y;
        for (int x = 0; x < lcd_width && x < jpg_w; x++) {
            // 复制 RGB 三个字节到 framebuffer 的 4 字节像素位置
            // 注意：如果 framebuffer 需要 BGRA，则需要调整顺序或进行转换
            memcpy(lcd_mem + lcd_offset + x * 4,
                   rgbdata + rgb_offset + x * 3,
                   3);
        }
    }

    // 7. 清理资源
    free(rgbdata);
    free(jpgdata);
    munmap(lcd_mem, (size_t)lcd_pitch * lcd_height);
    close(lcd_fd);

    return 0;
}