#include "LCD.h"
bool lcd_init(const char *dev_name,struct lcdinfo *p)
{
    if(dev_name==NULL||p==NULL)
    {
        return false;
    }
    printf("[%s][%d]\n",__func__,__LINE__);
    p->lcdfd=open(dev_name,O_RDWR);
    if(p->lcdfd<0)
    {
        perror("open lcd failed");
        return false;
    }
    struct fb_var_screeninfo vinfo;
    if(ioctl(p->lcdfd,FBIOGET_VSCREENINFO,&vinfo)==-1)
    {
        perror("ioctl FBIOGET_VSCREENINFO failed");
        return false;
    }
    printf("[%s][%d]\n",__func__,__LINE__);
    p->width=vinfo.xres;
    p->height=vinfo.yres;
    p->bpp=vinfo.bits_per_pixel;
    p->pitch=vinfo.xres*vinfo.bits_per_pixel/8;
    p->screensize=p->pitch*p->height;
    p->fbmem=mmap(NULL,p->screensize,PROT_WRITE,MAP_SHARED,p->lcdfd,0);
    if(p->fbmem==MAP_FAILED)
    {
        perror("mmap failed");
        return false;
    }
    bzero(p->fbmem,p->screensize);
    return true;
}
void lcd_release(struct lcdinfo *p)
{
    if(p==NULL)
        return;
    munmap(p->fbmem,p->screensize);
    close(p->lcdfd);
}