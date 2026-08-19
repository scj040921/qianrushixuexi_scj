#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dlfcn.h>
int main(int argc,char *argv[])
{
    FILE *fp=fopen("config","r");
    if(fp==NULL)
    {
        printf("open config failed\n");
        return -1;
    }
    char libstr[50]={0};
    fgets(libstr,50,fp);
    fclose(fp);
    void *hanle=dlopen(libstr,RTLD_NOW);
    if(hanle==NULL)
    {
        printf("load lib error\n");
        return -1;
    }
    void(*detect)(void);
    detect=dlsym(hanle,"detection");
    if(detect==NULL)
    {
        printf("get func error\n");
        return -1;
    }
    detect();
}