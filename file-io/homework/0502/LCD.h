#ifndef LCD_H
#define LCD_H

#include <stdbool.h>

struct lcdinfo {
    int lcdfd;
    unsigned char *fbmem;
    int width;
    int height;
    int bpp;
    int pitch;
    int screensize;
    int red_offset;
    int red_length;
    int green_offset;
    int green_length;
    int blue_offset;
    int blue_length;
    int transp_offset;
    int transp_length;
};

extern bool lcd_init(const char *dev_name, struct lcdinfo *p);
extern void release_lcd(struct lcdinfo *p);

#endif
