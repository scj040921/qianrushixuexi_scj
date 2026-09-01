#include"myhead.h"

int newsock;//全局变量，用于保存新连接的套接字
//线程的任务函数：发送信息
void *send_msg(void *arg)
{
    char sbuf[100];
    while(1)
    {
        bzero(sbuf,sizeof(sbuf));
        printf("请输入要发送的信息：");
        scanf("%s",sbuf);
        send(newsock,sbuf,strlen(sbuf),0);
    }
}
int main()
{
    int tcpsock;
    int ret;
    char rbuf[100];
    pthread_t ptid;
    struct sockaddr_in bindaddr;
    bzero(&bindaddr,sizeof(bindaddr));
    bindaddr.sin_family=AF_INET;
    bindaddr.sin_addr.s_addr=inet_addr("172.19.154.41");
    bindaddr.sin_port=htons(2000);
    struct sockaddr_in clientaddr;
    bzero(&clientaddr,sizeof(clientaddr));
    int len=sizeof(clientaddr);
    tcpsock=socket(AF_INET,SOCK_STREAM,0);
    if(tcpsock<0)
    {
        perror("创建失败");
        return -1;
    }
    ret=bind(tcpsock,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
    if(ret<0)
    {
        perror("绑定失败");
        return -1;
    }
    ret=listen(tcpsock,5);
    if(ret<0)
    {
        perror("监听失败");
        return -1;
    }
    printf("旧的套接字为%d",tcpsock);
    newsock=accept(tcpsock,(struct sockaddr *)&clientaddr,&len);
    if(newsock<0)
    {
        perror("接受失败");
        return -1;
    }
    printf("新的套接字为%d",newsock);
    pthread_create(&ptid,NULL,send_msg,NULL);
    while(1)
    {
        bzero(rbuf,sizeof(rbuf));
        ret=recv(newsock,rbuf,sizeof(rbuf),0);
        printf("接收到的信息为：%s\n",rbuf);
    }
    close(newsock);
    close(tcpsock);
    return 0;
}