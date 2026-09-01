#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
int main()
{
    //创建具名管道
    if(mkfifo("myfifo",0666)<0)
}