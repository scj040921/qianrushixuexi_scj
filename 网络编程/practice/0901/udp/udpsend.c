#include"myhead.h"
int main()
{
    int udpsock;
    int ret;
    char sbuf[100];
    char ip[20];
    unsigned short port;
    struct sockaddr_in bindaddr;
    bzero(&bindaddr,sizeof(bindaddr));
    bindaddr.sin_family=AF_INET;
    bindaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    bindaddr.sin_port=htons(8888);
    struct sockaddr_in otheraddr;//设置目标地址
    udpsock=socket(AF_INET,SOCK_DGRAM,0);
    if(udpsock==-1)
    {
        perror("创建失败\n");
        return -1;
    }
    in on=1;
    setsockopt(udpsock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));//设置端口复用
    ret=bind(udpsock,(struct sockaddr*)&bindaddr,sizeof(bindaddr));
    if(ret==-1)
    {
        perror("绑定失败\n");
        return -1;
    }
    while(1)
    {
        bzero(sbuf,sizeof(sbuf));
        bzero(ip,sizeof(ip));

    }
}