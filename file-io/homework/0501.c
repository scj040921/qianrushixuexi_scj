#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>

void click(int tp)
{
    int x1,y1;
    int x2,y2;
    bool x1done=false;
    bool x2done=false;
    struct input_event buf;
    while(1)
    {
        bzero(&buf,sizeof(buf));
        read(tp,&buf,sizeof(buf));
    }
}