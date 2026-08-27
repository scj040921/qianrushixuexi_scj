#include "LCD.h"
#include <stdio.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>

bool lcd_init(const char *dev_name, struct lcdinfo *p)
{
    if (dev_name == NULL || p == NULL)
        return false;

    memset(p, 0, sizeof(*p));
    p->lcdfd = open(dev_name, O_RDWR);
    if (p->lcdfd < 0) {
        perror("open lcd");
        return false;
    }

    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    if (ioctl(p->lcdfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("FBIOGET_VSCREENINFO");
        close(p->lcdfd);
        return false;
    }
    if (ioctl(p->lcdfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("FBIOGET_FSCREENINFO");
        close(p->lcdfd);
        return false;
    }

    p->width = (int)vinfo.xres;
    p->height = (int)vinfo.yres;
    p->bpp = (int)vinfo.bits_per_pixel;
    p->pitch = (int)finfo.line_length;
    p->screensize = (int)finfo.smem_len;
    p->red_offset = (int)vinfo.red.offset;
    p->red_length = (int)vinfo.red.length;
    p->green_offset = (int)vinfo.green.offset;
    p->green_length = (int)vinfo.green.length;
    p->blue_offset = (int)vinfo.blue.offset;
    p->blue_length = (int)vinfo.blue.length;
    p->transp_offset = (int)vinfo.transp.offset;
    p->transp_length = (int)vinfo.transp.length;

    printf("LCD: %dx%d, %dbpp, pitch=%d, screensize=%d\n",
           p->width, p->height, p->bpp, p->pitch, p->screensize);

    p->fbmem = mmap(NULL, (size_t)p->screensize, PROT_READ | PROT_WRITE,
                    MAP_SHARED, p->lcdfd, 0);
    if (p->fbmem == MAP_FAILED) {
        perror("mmap lcd");
        close(p->lcdfd);
        return false;
    }

    memset(p->fbmem, 0, (size_t)p->screensize);
    return true;
}

void release_lcd(struct lcdinfo *p)
{
    if (p == NULL)
        return;
    if (p->fbmem != NULL && p->fbmem != MAP_FAILED)
        munmap(p->fbmem, (size_t)p->screensize);
    if (p->lcdfd >= 0)
        close(p->lcdfd);
}
