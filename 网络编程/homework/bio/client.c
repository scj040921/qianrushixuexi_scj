#include"myhead.h"

int tcpsock;
//线程的任务函数负责接收信息
void *recv_msg(void *arg)
{
    int ret;
    char rbuf[100];
    while(1)
    {
        bzero(rbuf,sizeof(rbuf));
        ret=recv(tcpsock,rbuf,sizeof(rbuf),0);
       if (ret <= 0)   // 服务器关闭连接或出错
        {
            printf("服务器已断开，客户端退出\n");
            close(tcpsock);
            exit(0);
        }
        printf("客户端收到的信息是:%s，recv返回值代表成功接收的字节数:%d\n",rbuf,ret);
         if(strcmp(rbuf, "quit") == 0)
        {
            printf("收到退出指令，客户端即将退出\n");
            exit(0);
        }
    }
}

int main()
{
    int ret;
    char sbuf[100];
    pthread_t ptid;//创建线程
    //定义ipv4地址结构体变量，存放需要绑定的ip地址和端口号
    struct sockaddr_in bindaddr;
    bzero(&bindaddr,sizeof(bindaddr));
    bindaddr.sin_family=AF_INET;
    bindaddr.sin_addr.s_addr=inet_addr("172.19.154.41");
    bindaddr.sin_port=htons(8888);
    //定义ipv4结构体变量，存放服务器的ip地址和端口号
    struct sockaddr_in serveraddr;
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("172.19.154.41");
    serveraddr.sin_port=htons(2000);
    //创建套接字
    tcpsock=socket(AF_INET,SOCK_STREAM,0);
    if(tcpsock==-1)
    {
        perror("创建失败\n");
        return -1;
    }
    int opt = 1;
    setsockopt(tcpsock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //绑定ip地址和端口号
    ret=bind(tcpsock,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
    if(ret==-1)
    {
        perror("绑定失败\n");
        return -1;
    }
    //连接服务器
    ret=connect(tcpsock,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    if(ret==-1)
    {
        perror("连接失败\n");
        return -1;
    }
    //创建专门的线程接收消息
    pthread_create(&ptid,NULL,recv_msg,NULL);
    //发送消息
    while(1)
    {
        bzero(sbuf,sizeof(sbuf));
        printf("请输入要发送的信息:");
        scanf("%s",sbuf);
        if (strcmp(sbuf, "quit") == 0)
        {
            printf("客户端主动退出\n");
            close(tcpsock);
            exit(0);   // 直接退出，连接关闭，服务器会检测到
        }
        ret=send(tcpsock,sbuf,sizeof(sbuf),0);
        printf("发送成功，send返回值:%d\n",ret);
      
    }
    close(tcpsock);
    return 0;
}