#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include "bmp.h"
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage:%s bmp\n",argv[0]);
        return -1;
    }
    //准备LCD资源
    int lcd=open("/dev/fb0",O_RDWR);
    if(lcd==-1)
    {
        perror("open lcd failed");
        return -1;
    }
    struct fb_var_screeninfo vinfo;
    ioctl(lcd,FBIOGET_VSCREENINFO,&vinfo);
    int lcd_w=vinfo.xres;
    int lcd_h=vinfo.yres;
    int lcd_bpp=vinfo.bits_per_pixel;
    int lcd_line_size=lcd_w*lcd_bpp/8;
    int lcd_size=lcd_w*lcd_h*lcd_bpp/8;

    char *p=mmap(NULL,lcd_size,PROT_READ|PROT_WRITE,MAP_SHARED,lcd,0);
    if(p==MAP_FAILED)
    {
        perror("mmap lcd failed");
        return -1;
    }
    //清屏（黑色）
    bzero(p,lcd_size);
    getchar();
    //清屏（白色）
    memset(p,0xFF,lcd_size);
    //读取bmp文件格式头
    int fd=open(argv[1],O_RDONLY);
    if(fd==-1)
    {
        perror("open bmp failed");
        return -1;
    }
    //读取bmp文件RGB数据
    struct bitmap_header header;
    struct bitmap_info info;
    bzero(&header,sizeof(header));
    bzero(&info,sizeof(info));

    read(fd,&header,sizeof(header));
    read(fd,&info,sizeof(info));
    if(info.compression!=0)
    {
        struct rgb_quad quad;
        bzero(&quad,sizeof(quad));
        read(fd,&quad,sizeof(quad));
    }
    int bmp_w=info.width;
    int bmp_h=info.height;
    int bmp_bpp=info.bit_count;

    printf("图片分辨率：%dx%d\n",info.width,info.height);
    //计算一行中的无效字节
    int pad=(4-(bmp_w*bmp_bpp/8%4))%4;
    int bmp_line_size=bmp_w*bmp_bpp/8+pad;
    int bmp_size=bmp_line_size*bmp_h;

    char *rgb = malloc(bmp_size);
    if(rgb==NULL)
    {
        perror("malloc failed");
        return -1;
    }
    bzero(rgb, bmp_size);
    //读取bmp文件的RGB数据
    while(bmp_size>0)
    {
        int n=read(fd,rgb,bmp_size);
        if(n==-1)
        {
            perror("read bmp failed");
            return -1;
        }
        bmp_size-=n;
    }
    //将RGB数据写入LCD
    int x_offset=0,y_offset=0;
    if (lcd_w>bmp_w)
        x_offset=(lcd_w-bmp_w)/2;
    if (lcd_h>bmp_h)
        y_offset=(lcd_h-bmp_h)/2;
 char *p1 = p+lcd_line_size*y_offset + x_offset*lcd_bpp/8;

    int w = bmp_w < lcd_w ? bmp_w : lcd_w;
    int h = bmp_h < lcd_h ? bmp_h : lcd_h;

    int pixel=bmp_bpp/8;
    for(int j=0;j<bmp_h&&j<lcd_h-y_offset;j++)
    {
        int lcd_offset=j*lcd_line_size;
        int bmp_offset=(bmp_h-j-1)*bmp_line_size;
        for(int i=0;i<bmp_w&&i<lcd_w-x_offset;i++)
        {
            memcpy(p1+4*i+lcd_offset,rgb+i*pixel+bmp_offset,pixel);
        }
    }
    munmap(p, lcd_size);
    close(lcd);
    close(fd);
    free(rgb);

    return 0;
}