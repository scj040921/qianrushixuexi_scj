#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid=fork();
    if(pid==0)
    {
        dup2(fd[0],STDIN_FILENO);
        execl("/usr/bin/wc","wc","-w",NULL);
    }
    else if(pid>0)
    {
        dup2(fd[1],STDOUT_FILENO);
       execl("/bin/ls","ls","/etc",NULL);
    }
}