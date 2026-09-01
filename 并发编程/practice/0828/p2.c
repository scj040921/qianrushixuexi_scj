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
    long mtype;
    char mtext[1024];
};
int main()
{
    key_t key=ftok("/home/scj/0828/msg_queue",1);
    int msg_qid=msgget(key,IPC_CREAT|0666);
    if(msg_qid==-1)
    {
        perror("msgget");
        exit(1);
    }
    struct msgbuf msg;
    while(1)
    {
        bzero(&msg,sizeof(msg));
        msgrcv(msg_qid,&msg,sizeof(msg),P1_P2,0);
        printf("收到消息：%s",msg.mtext);
    }
    return 0;
}