#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "head.h"
struct msgbuf
{
    //消息类型
    long mtype;
    //消息正文
    char mtext[1024];
};
int main()
{
    //创建消息队列IPC对象
    //参数含义
    //在路径/home/scj/0828/msg_queue下创建的第一个key
    key_t key=ftok("/home/scj/0828/msg_queue",1);
    //存在则直接打开，不存在则创建
    int msg_qid=msgget(key,IPC_CREAT|0666);
    if(msg_qid==-1)
    {
        perror("msgget error");
        exit(1);
    }
    //向对方发送消息
    struct msgbuf msg;
    while(1)
    {
        bzero(msg.mtext,sizeof(msg.mtext));
        fgets(msg.mtext,sizeof(msg.mtext),stdin);
        msg.mtype=P1_P2;
        msgsnd(msg_qid,&msg,strlen(msg.mtext),0);
    }
    return 0;
}