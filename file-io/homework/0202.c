#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
    struct stat info;
    bzero(&info,sizeof(info));
    FILE *fp=fopen(argv[1],"w");
    while(1)
    {
        fwrite("a",1,1,fp);
        stat(argv[1],&info);
        if(info.st_size>0)
            break;
    }
    printf("缓冲区的大小：%ld\n",info.st_size);
    fclose(fp);
    return 0;
}