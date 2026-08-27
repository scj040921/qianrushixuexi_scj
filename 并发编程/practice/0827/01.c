#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
int main ()
{
    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid==0)
    {
        char buf[20]={0};
        read(fd[0],buf,20);
        printf("from parent:%s\n",buf);
        write(fd[1],"123456789",10);

    }
    else if(pid>0)
    {
        sleep(2);
        write(fd[1],"hi child",10);
        usleep(1000);;
        char buf[20]={0};
        read(fd[0],buf,20);
        printf("from child:%s\n",buf);
    }
    return 0;
}