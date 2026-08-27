#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "jpeglib.h"
#include "LCD.h"

static unsigned char *jpg_to_rgb(const unsigned char *jpgdata, size_t jpgsize,
                                 int *width, int *height, int *pitch)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_mem_src(&cinfo, jpgdata, jpgsize);
    if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) {
        jpeg_destroy_decompress(&cinfo);
        return NULL;
    }
    jpeg_start_decompress(&cinfo);
    *width = (int)cinfo.output_width;
    *height = (int)cinfo.output_height;
    *pitch = *width * (int)cinfo.output_components;
    size_t size = (size_t)*pitch * (size_t)*height;
    unsigned char *rgb = calloc(1, size);
    if (rgb == NULL) {
        jpeg_destroy_decompress(&cinfo);
        return NULL;
    }
    while (cinfo.output_scanline < cinfo.output_height) {
        unsigned char *row = rgb + (size_t)cinfo.output_scanline * (size_t)*pitch;
        jpeg_read_scanlines(&cinfo, &row, 1);
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    return rgb;
}

static uint32_t pack_channel(unsigned char value, int length)
{
    if (length <= 0)
        return 0;
    unsigned int max = (1u << length) - 1u;
    return ((uint32_t)value * max + 127u) / 255u;
}

void show_jpg(struct lcdinfo *lcd, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "fopen %s: %s\n", filename, strerror(errno));
        return;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return;
    }
    long file_size = ftell(fp);
    if (file_size <= 0 || fseek(fp, 0, SEEK_SET) != 0) {
        fclose(fp);
        return;
    }
    unsigned char *jpgdata = malloc((size_t)file_size);
    if (jpgdata == NULL || fread(jpgdata, 1, (size_t)file_size, fp) != (size_t)file_size) {
        fprintf(stderr, "read %s failed\n", filename);
        free(jpgdata);
        fclose(fp);
        return;
    }
    fclose(fp);

    int jpg_w, jpg_h, jpg_pitch;
    unsigned char *rgb = jpg_to_rgb(jpgdata, (size_t)file_size,
                                    &jpg_w, &jpg_h, &jpg_pitch);
    free(jpgdata);
    if (rgb == NULL) {
        fprintf(stderr, "decode %s failed\n", filename);
        return;
    }

    int bytes_per_pixel = lcd->bpp / 8;
    int copy_w = jpg_w < lcd->width ? jpg_w : lcd->width;
    int copy_h = jpg_h < lcd->height ? jpg_h : lcd->height;
    if ((lcd->bpp != 16 && lcd->bpp != 32) || bytes_per_pixel <= 0) {
        fprintf(stderr, "unsupported framebuffer: %d bpp\n", lcd->bpp);
        free(rgb);
        return;
    }

    for (int y = 0; y < copy_h; ++y) {
        for (int x = 0; x < copy_w; ++x) {
            const unsigned char *src = rgb + y * jpg_pitch + x * 3;
            unsigned char *dst = lcd->fbmem + y * lcd->pitch + x * bytes_per_pixel;
            uint32_t pixel = (pack_channel(src[0], lcd->red_length) << lcd->red_offset) |
                    (pack_channel(src[1], lcd->green_length) << lcd->green_offset) |
                    (pack_channel(src[2], lcd->blue_length) << lcd->blue_offset);
            if (lcd->bpp == 32 && lcd->transp_length > 0)
                pixel |= ((1u << lcd->transp_length) - 1u) << lcd->transp_offset;
            memcpy(dst, &pixel, (size_t)bytes_per_pixel);
        }
    }
    free(rgb);
}
