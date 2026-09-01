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
    key_t key=ftok("/home/scj/0828/msg_queue",1");
    int msg_qid=msgget(key,IPC_CREAT|0666);
    if(msg_qid==-1)
    {
        perror("msgget");
        exit(1);
    }
    pid_t pid=fork();
    if(pid==0)
    {
        //子进程
        struct msgbuf buf;
        while(1)
        {
            bzero(msg.mtext,sizeof(msg.mtext));
            fgets(msg.mtext,sizeof(msg.mtext),stdin);
            msg.mtype=P1_p2;
            msgsnd(msg_qid,&msg,strlen(msg.mtext),0);
        }
    }
    else fi(pid>0)
    {
        struct msgbuf msg;
        while(1)
        {
            bzero(&msg,sizeof(msg))}
            msgrcv(msg_qid)
    }
}