#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "lcd.h"
#include "image.h"
void show_bmp(struct lcdinfo *LCD,const char *bmpfile)
{
    printf("[%s][%d]\n",__func__,__LINE__);
    int bmp_fd=open(bmpfile,O_RDWR);
    if(bmp_fd==-1)
    {
        perror("open bmp failed");
        return;
    }
    struct bitmap_header bmp_header;
    struct bitmap_info bmp_info;
    bzero(&bmp_header,sizeof(bmp_header));
    bzero(&bmp_info,sizeof(bmp_info));
    read(bmp_fd,&bmp_header,sizeof(bmp_header));
    read(bmp_fd,&bmp_info,sizeof(bmp_info));

    if(bmp_info.compression!=0)
    {
        struct rgb_quad quad;
        bzero(&quad,sizeof(quad));
        read(bmp_fd,&quad,sizeof(quad));
    }
    int bmp_width=bmp_info.width;
    int bmp_height=bmp_info.height;
    int bmp_bpp=bmp_info.bit_count;
    int bmp_pitch=bmp_width*bmp_bpp/8;
    int pad=(4-bmp_pitch%4)%4;
    int bmp_pitch_real=bmp_pitch+pad;
    int bmp_size=bmp_pitch*bmp_height;
    int bmp_size_real=bmp_pitch_real*bmp_height;

    int i,j;
    unsigned char *p=LCD->fbmem+LCD->pitch*(LCD->height-1);
    for(j=0;j<bmp_height&&j<LCD->height;j++)
    {
        for(i=0;i<bmp_width&&i<LCD->width;i++)
        {
            read(bmp_fd,p+4*i,bmp_bpp/8);
        }
        lseek(bmp_fd,bmp_pitch_real-bmp_bpp/8*i,SEEK_CUR);
        p-=LCD->pitch;
    }

}

void show_image(struct lcdinfo *LCD,const char *filename)
{
    show_bmp(LCD, filename);
}