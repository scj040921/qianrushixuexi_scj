#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <linux/input.h>

#include "LCD.h"
void wait_click(int tp)
{
    struct input_event ev;
    int x1=-1,y1=-1;
    int x2=-1,y2=-1;
    while(1)
    {
        if(read(tp,&ev,sizeof(ev))<0)
        {
            perror("read failed");
            return;
        }
        if(ev.type==EV_ABS&&ev.code==ABS_X)
        {
            if(x1==-1)
                x1=ev.value;
            else
                x2=ev.value;
        }
        if(ev.type==EV_ABS&&ev.code==ABS_Y)
        {
            if(y1==-1)
                y1=ev.value;
            else
                y2=ev.value;
        }
        if(ev.type==EV_KEY&&ev.code==BTN_TOUCH&&ev.value==0)
        {
            if(x2==-1||y2==-1)
                return;
            if(abs(x1-x2)<20&&abs(y1-y2)<20)
                return;
        }
    }
}
int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr,"Usage: %s <dev_name>\n",argv[0]);
        return -1;
    }
    struct lcdinfo lininfo;
    bzero(&lininfo,sizeof(lininfo));
    printf("[%s][%d]\n",__FILE__,__LINE__);
    if(!lcd_init(argv[1],&lininfo))
    {
        return -1;
    }
    printf("[%s][%d]\n",__FILE__,__LINE__);
    int tp=open("/dev/input/event6",O_RDONLY);
    if(tp==-1)
    {
        perror("open tp failed");
        return -1;
    }
    printf("[%s][%d]\n",__FILE__,__LINE__);
    while(1)
    {
        wait_click(tp);
        printf("[%s][%d]\n",__FILE__,__LINE__);
        printf("click\n");
    }
    release_lcd(&lininfo);
    return 0;
}
