#ifndef LCD_H
#define LCD_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <stdbool.h>

struct lcdinfo {
    int lcdfd;
    unsigned int *fbmem;
    int width;
    int height;
    int bpp;
    int pitch;
    int screensize;
};
extern bool lcd_init(const char *dev_name, struct lcdinfo *p);
extern void release_lcd(struct lcdinfo *p);
#endif