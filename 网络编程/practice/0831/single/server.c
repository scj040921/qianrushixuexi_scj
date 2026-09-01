#include"myhead.h"

int main()
{
    int tcpsock;
	int newsock; //存放新的套接字
	int ret;
	char rbuf[100];
   
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;//IPV4
    bindaddr.sin_addr.s_addr = inet_addr("172.19.154.41");
    //绑定ip地址，一定要绑定本地主机自己的
    //ubuntu是采用小端序存放，计算机网络协议要求大端序存放，所以要转换
    //Linux提供了专门的转换函数：in_addr_t inet_addr(const char *cp);
    bindaddr.sin_port = htons(20000);//绑定端口号
    //定义ipv4地址结构体变量，存放目前链接成功的客户端信息
    struct sockaddr_in clientaddr;
    bzero(&clientaddr,sizeof(clientaddr));
    int len=sizeof(clientaddr);
    //创建套接字
    tcpsock=socket(AF_INET,SOCK_STREAM,0);
    if(tcpsock<0)
    {
        perror("创建失败");
        return -1;
    }
    //绑定ip号和端口号
    ret=bind(tcpsock,(struct sockaddr*)&bindaddr,sizeof(bindaddr));
    if(ret<0)
    {
        perror("绑定失败");
        return -1;
    }
    //监听
    ret=listen(tcpsock,10);
    if(ret<0)
    {
        perror("监听失败");
        return -1;
    }
    //接受客户端的链接请求
    printf("等待客户端连接...\n");
    newsock=accept(tcpsock,(struct sockaddr*)&clientaddr,&len);
    if(newsock<0)
    {
        perror("接受失败");
        return -1;
    }
    printf("新的套接字是：%d\n",newsock);
    while(1)
    {
        bzero(rbuf,sizeof(rbuf)); 
        recv(newsock,rbuf,sizeof(rbuf),0);
        printf("客户端说：%s\n",rbuf);
    }
    close(newsock);
    close(tcpsock);
    return 0;
}   