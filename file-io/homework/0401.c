#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

int main()
{
    int lcd=open("/dev/fb0",O_RDWR);//打开屏幕设备
    struct fb_var_screeninfo vinfo;
    ioctl(lcd,FBIOGET_VSCREENINFO,&vinfo);//获取屏幕可变参数，ioctl 是 设备控制 系统调用，用于向设备驱动程序发送控制命令，获取或设置设备的特定参数。
    int lcdw=vinfo.xres;
    int lcdh=vinfo.yres;
    int bpp=vinfo.bits_per_pixel;
    char *fbm=mmap(NULL,lcdw*lcdh*bpp/8,PROT_WRITE,MAP_SHARED,lcd,0);//内存映射
    if(fbm==MAP_FAILED)
    {
        perror("mmap failed");
        return 0;
    }
    bzero(fbm,lcdw*lcdh*bpp/8);
    int colors[]= {0x00FF0000,
                    0x0000FF00,
                    0x000000FF,
                    0x00FF00FF,
                    0x0000FFFF,
                    0x00FFFF00,
                    0x00FF8EFF,
                    0x00DAA520,
                    };
    int n=0;
    int w=lcdw/4;
    int h=lcdh/2;
    char *p = fbm;
    for(int k=0;;k++)
    {
        for(int i=0;i<h;i++)
        {
           for(int j=0;j<w;j++)
           {
                memcpy(p+4*(j+0*w)+lcdw*4*(i+0*h), &colors[(k+0)%8], 4);
                memcpy(p+4*(j+1*w)+lcdw*4*(i+0*h), &colors[(k+1)%8], 4);
                memcpy(p+4*(j+2*w)+lcdw*4*(i+0*h), &colors[(k+2)%8], 4);
                memcpy(p+4*(j+3*w)+lcdw*4*(i+0*h), &colors[(k+3)%8], 4);

                memcpy(p+4*(j+0*w)+lcdw*4*(i+1*h), &colors[(k+7)%8], 4);
                memcpy(p+4*(j+1*w)+lcdw*4*(i+1*h), &colors[(k+6)%8], 4);
                memcpy(p+4*(j+2*w)+lcdw*4*(i+1*h), &colors[(k+5)%8], 4);
                memcpy(p+4*(j+3*w)+lcdw*4*(i+1*h), &colors[(k+4)%8], 4);
           }
        }
        sleep(1);
    }
    return 0;
}