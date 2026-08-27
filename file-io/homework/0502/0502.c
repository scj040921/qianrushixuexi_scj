#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "LCD.h"

enum IMG_FMT { BMP, JPG, PNG, UNKNOWN };
void show_jpg(struct lcdinfo *lcd, const char *filename);

static int wait_touch_event(int tp, int value)
{
    struct input_event ev;
    for (;;) {
        ssize_t n = read(tp, &ev, sizeof(ev));
        if (n < 0 && errno == EINTR)
            continue;
        if (n != (ssize_t)sizeof(ev)) {
            if (n < 0)
                perror("read touchscreen");
            else
                fprintf(stderr, "short touchscreen event\n");
            return -1;
        }
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == value)
            return 0;
    }
}

static enum IMG_FMT get_fmt(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (dot == NULL)
        return UNKNOWN;
    if (strcasecmp(dot, ".jpg") == 0 || strcasecmp(dot, ".jpeg") == 0)
        return JPG;
    if (strcasecmp(dot, ".bmp") == 0)
        return BMP;
    if (strcasecmp(dot, ".png") == 0)
        return PNG;
    return UNKNOWN;
}

static void show_image(struct lcdinfo *lcd, const char *filename)
{
    if (get_fmt(filename) == JPG)
        show_jpg(lcd, filename);
    else
        fprintf(stderr, "unsupported image format: %s\n", filename);
}

int main(int argc, char **argv)
{
    const char *touch_device = argc > 1 ? argv[1] : "/dev/input/event6";
    struct lcdinfo lcd;
    if (!lcd_init("/dev/fb0", &lcd))
        return 1;

    show_image(&lcd, "off.jpg");
    int tp = open(touch_device, O_RDONLY);
    if (tp < 0) {
        perror(touch_device);
        release_lcd(&lcd);
        return 1;
    }

    for (;;) {
        if (wait_touch_event(tp, 1) < 0)
            break;
        printf("on.jpg\n");
        show_image(&lcd, "on.jpg");
        if (wait_touch_event(tp, 0) < 0)
            break;
        printf("off.jpg\n");
        show_image(&lcd, "off.jpg");
    }

    close(tp);
    release_lcd(&lcd);
    return 0;
}
