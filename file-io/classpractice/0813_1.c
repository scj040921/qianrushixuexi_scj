#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/fb.h>
#include<stdint.h> 

int main(int argc,char *argv[])
{
    int lcd=open("/dev/fb0",O_RDWR);
    if(lcd==-1)
    {
        perror("open lcd failed");
        return 1;
    }
    struct fb_var_screeninfo lcd_info;
    ioctl(lcd,FBIOGET_VSCREENINFO,&lcd_info);
    int lcd_w=lcd_info.xres;
    int lcd_h=lcd_info.yres;
    int lcd_bpp=lcd_info.bits_per_pixel;
    int screen_size=lcd_w*lcd_h*lcd_bpp/8;
    int lcd_line_size=lcd_w*lcd_bpp/8;
    printf("LCD分辨率：%dx%d\n",lcd_w,lcd_h);
    printf("LCD bpp: %d\n", lcd_bpp);
    char *p=mmap(NULL,screen_size,PROT_READ|PROT_WRITE,MAP_SHARED,lcd,0);
    if(p==MAP_FAILED)
    {
        perror("mmap failed");
        return 1;
    }
    int bytes_per_pixel = lcd_bpp / 8;   // 每个像素占用的字节数
    int flag = 0;
    while(1)
    {
        for(int y=0;y<lcd_h;y++)
        {
            for(int x=0;x<lcd_w;x++)
            {
                uint32_t color;
                if (flag == 0) {   // 法国：左蓝、中白、右红
                    if (x < lcd_w / 3)
                        color = 0x000000FF;      // 蓝
                    else if (x < 2 * lcd_w / 3)
                        color = 0x00FFFFFF;      // 白
                    else
                        color = 0x00FF0000;      // 红
                } else if (flag == 1) { // 德国：上黑、中红、下金
                    if (y < lcd_h / 3)
                        color = 0x00000000;      // 黑
                    else if (y < 2 * lcd_h / 3)
                        color = 0x00FF0000;      // 红
                    else
                        color = 0x00FFD700;      // 金
                } else {              // 俄罗斯：上白、中蓝、下红
                    if (y < lcd_h / 3)
                        color = 0x00FFFFFF;      // 白
                    else if (y < 2 * lcd_h / 3)
                        color = 0x000000FF;      // 蓝
                    else
                        color = 0x00FF0000;      // 红
                }
                int offset = (y * lcd_w + x) * bytes_per_pixel;
                memcpy(p + offset, &color, bytes_per_pixel);
            }
        }
        sleep(3);
        flag = (flag + 1) % 3;
    }
    munmap(p, screen_size);
    close(lcd);
    return 0;
}