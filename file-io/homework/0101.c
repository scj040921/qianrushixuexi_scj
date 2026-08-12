#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#define BLKSIZE 200
int main(int argc,char **argv)
//argc:命令行传入参数的总个数，即使不传入任何参数，argc也至少为1
//argv:是一个字符串数组每一个元素都是命令行参数，argv[0]是程序名，argv[1~argc-1]是用户传入的参数，argv[argc]标准规定是一个空指针方便遍历参数
{
    int fd_from,fd_to;
    if(argc!=3)
    {
        printf("对不起，必须指定两个文件\n");
        exit(0);
    }
//打开源文件
    fd_from=open(argv[1],O_RDONLY);
    if(fd_from==-1)
    {
        printf("打开文件%s失败：%s\n",argv[1],strerror(errno));
        exit(0);
    }
//打开目标文件
    fd_to=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(fd_to==-1)
    {
        printf("打开文件%s失败：%s\n",argv[2],strerror(errno));
        exit(0);
    }
    char buf[BLKSIZE];
    char *bp;
    int nread,nwrite;
    while(1)
    {
        while(((nread=read(fd_from,buf,BLKSIZE))==-1)&&(errno==EINTR));
        if(nread==-1)
        {
            perror("读取源文件失败");
            break;
        }
        if(nread==0)
        {
            break;
        }
        bp=buf;
        while(nread>0)
        {
            while(((nwrite=write(fd_to,bp,nread))==-1)&&(errno==EINTR));
            if(nwrite==-1)
            {
                perror("写入目标文件失败");
                exit(0);
            }
            nread-=nwrite;
            bp+=nwrite;
        }
    }
    close(fd_from);
    close(fd_to);
    return 0;
}
