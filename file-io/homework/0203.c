#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#define BUFSIZE 64
static int line_num=0;
FILE *Fopen(const char *path,const char *mode)
{
    FILE *fp;
    fp=fopen(path,mode);
    if(fp==NULL)
    {
        perror("fopen failed");
    }
    return fp;
}
int main(int argc,char *argv[])
{
    FILE *fp=NULL;
    FILE *fpline=NULL;
    if(access(argv[1],F_OK))
        fpline=Fopen(argv[1],"w+");
    else
    {
        fpline=Fopen(argv[1],"r");
        fread(&line_num,sizeof(int),1,fpline);
        freopen(argv[1],"w+",fpline);
    }
    setvbuf(fpline,NULL,_IONBF,0);
    char num_str[BUFSIZE];
    time_t *tloc=(time_t *)malloc(sizeof(time_t));
    while(1)
    {
        snprintf(num_str,BUFSIZE,"%d\t",++line_num);
        time(tloc);
        snprintf(num_str+strlen(num_str)-1,BUFSIZE,"\t%s",ctime(tloc));
        rewind(fpline);
        fwrite(&line_num,sizeof(int),1,fpline);
        fputs(num_str,stdout);
        sleep(1);
    }
    return 0;
}