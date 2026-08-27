#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/types.h>
#include <linux/input.h> // 系统定义输入设备操作的API
#include "LCD.h"

void click(int tp)
{
    int x1, y1;//起点坐标
    int x2, y2;//当前坐标

    bool x1done = false;
    bool y1done = false;//标记是否已经捕获到起点坐标，如果为false表示还没有收到该轴的坐标

    struct input_event buf;//用于接受输入设备读取的事件
    while(1)
    {
        bzero(&buf, sizeof(buf));//清零防止残余垃圾干扰
        read(tp, &buf, sizeof(buf));//从tp中读取一个事件到buf中

        // get first pos
        if(buf.type == EV_ABS && buf.code == ABS_X && !x1done)//当收到的事件类型是 EV_ABS（绝对坐标事件），且代码是 ABS_X（X 轴坐标），并且之前没有捕获到过 X 起点
        {
            x2 = x1 = buf.value;
            x1done = true;
        }
        if(buf.type == EV_ABS && buf.code == ABS_Y && !y1done)
        {
            y2 = y1 = buf.value;
            y1done = true;
        }

        if(buf.type == EV_ABS && buf.code == ABS_X)
            x2 = buf.value;
        if(buf.type == EV_ABS && buf.code == ABS_Y)
            y2 = buf.value;
//无论 x1done 是否为真，只要收到 X 坐标事件，就更新 x2（最新 X 值）。同样更新 
        if(buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0)
        //当收到 EV_KEY 事件，代码为 BTN_TOUCH，且 value == 0 时，表示触摸释放（手指抬起）。
        {
            if(abs(x1-x2)<=20 && abs(y1-y2)<=20)
            /*
            如果满足，说明手指几乎没有移动，视为一次点击，return 退出函数。

            如果不满足，说明发生了滑动，因此这次操作不是有效点击。
            需要重置起点标志 x1done = false; y1done = false;
，          然后 continue 继续循环，等待下一次触摸。
            */ 
                return;
            else
            {
                x1done = false;
                y1done = false;
                continue;
            }
        }
    }
}

void fill_screen(struct lcdinfo *lcd, unsigned int color)
{
    // 假设 32 位色深（常见格式），颜色值直接写入 unsigned int
    //unsigned int *pixel = lcd->fbmem;
    //int total_pixels = lcd->width * lcd->height;

    // 使用 pitch 处理可能存在的行填充
    // 但为简单，我们假设 pitch == width * sizeof(unsigned int)
    // 如果实际 pitch 不同，需要按行处理，这里提供通用方法：
    unsigned char *fb_ptr = (unsigned char *)lcd->fbmem;
    //将 lcd->fbmem（unsigned int * 类型）强制转换为 unsigned char *，以便按字节进行地址计算。因为 pitch 是以字节为单位的行长度。
    int x, y;//定义循环变量 x（列）和 y（行）。

    for (y = 0; y < lcd->height; y++) {
        unsigned char *row = fb_ptr + y * lcd->pitch;
        unsigned int *row_pixel = (unsigned int *)row;
        for (x = 0; x < lcd->width; x++) {
            row_pixel[x] = color;
        }
    }
}

// 循环切换颜色
void change_color(struct lcdinfo *lcd)
{
    static unsigned int colors[] = {
        0xFF0000,   // 红
        0x00FF00,   // 绿
        0x0000FF,   // 蓝
        0xFFFF00,   // 黄
        0xFF00FF,   // 品红
        0x00FFFF,   // 青
        0xFFFFFF,   // 白
        0x000000    // 黑
    };
    static int idx = 0;

    fill_screen(lcd, colors[idx]);
    idx = (idx + 1) % (sizeof(colors) / sizeof(colors[0]));
}

int main(int argc, char const *argv[])
{
    struct lcdinfo lcd;

    // 使用动态库初始化 LCD
    if (!lcd_init("/dev/fb0", &lcd)) {
        fprintf(stderr, "Failed to initialize LCD\n");
        return 1;
    }

    int tp = open("/dev/input/event6", O_RDWR);
    if (tp < 0) {
        perror("open touchscreen");
        release_lcd(&lcd);
        return 1;
    }

    while(1)
    {
        click(tp);
        change_color(&lcd);   // 传入 lcd 结构体指针
        printf("change color!\n");
    }

    // 清理（通常不会执行到这里）
    close(tp);
    release_lcd(&lcd);
    return 0;
}