#include"myhead.h"

int main()
{
    int tcpsock;
    int ret;
    char sbuf[100];
    //定义ipv4地址结构体变量，存放需要绑定的ip地址和端口号
    struct sockaddr_in bindaddr;
    bzero(&bindaddr,sizeof(bindaddr));
    bindaddr.sin_family=AF_INET;//ipv4地址协议
    bindaddr.sin_addr.s_addr=inet_addr("172.19.154.41");//绑定本机地址
    bindaddr.sin_port=htons(8888);//自己指定的端口号,尽量大于1024
    //定义ipv4地址结构体变量，存放服务器的ip和端口号
    struct sockaddr_in serveraddr;
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("172.19.154.41");
    serveraddr.sin_port=htons(20000);
    //创建tcp套接字
    tcpsock=socket(AF_INET,SOCK_STREAM,0);
    if(tcpsock<0)
    {
        perror("创建套接字失败\n");
        return -1;
    }
    //绑定ip和端口号
    ret=bind(tcpsock,(struct sockaddr*)&bindaddr,sizeof(bindaddr));
    if(ret<0)
    {
        perror("绑定失败\n");
        return -1;
    }
    //连接服务器
    ret=connect(tcpsock,(struct scokaddr*)&serveraddr,sizeof(serveraddr));
    if(ret<0)
    {
        perror("连接服务器失败\n");
        return -1;
    }
    //发送信息给服务器
    while(1)
    {
        bzero(sbuf,sizeof(sbuf));
        printf("请输入要发送的信息：");
        scanf("%s",sbuf);
        send(tcpsock,sbuf,strlen(sbuf),0);
    }
    //关闭套接字
    close(tcpsock);
    return 0;
    }
