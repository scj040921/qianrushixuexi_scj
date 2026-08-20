#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "image.h"
#include "lcd.h"
enum IMG_FMT{JPG,BMP,PNG}; 
get_fmt(const char *filename)
{
    if(strstr(filename,".jpg")||strstr(filename,".jpeg"))
        return JPG;
    if(strstr(filename,".bmp"))
        return BMP;
    if(strstr(filename,".png"))
        return PNG;
}
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s <filename>\n",argv[0]);
        return -1;
    }
    struct lcdinfo *LCD=calloc(1,sizeof(struct lcdinfo));
    lcd_init("/dev/fb0",LCD);
    void *handler=NULL;
    void (*show_image)(struct lcdinfo *,const char *)=NULL;
    switch(get_fmt(argv[1]))
    {
        case JPG:
            handler=dlopen("libjpg.so",RTLD_LAZY);
            break;
        case BMP:
            handler=dlopen("libbmp.so",RTLD_LAZY);
            break;
    }
    show_image=dlsym(handler,"show_image");
    show_image(LCD,argv[1]);
    lcd_release(LCD);
    return 0;
}