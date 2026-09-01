#include"myhead.h"

int newsock;//全局变量，用于保存新连接的套接字
typedef struct client_node
{
    int sockfd;//客户端套接字
    int ip[20];//客户端地址
    unsigned short port;//客户端端口号
    struct client_node *next;
}client_node;
client_node *head = NULL;            // 链表头
client_node *list_init()
{
   client_node *head=malloc(sizeof(client_node));
   head->next=NULL;
   return head;
}
int insert_tail(client_node *node,client_node *head)
{
    client_node *p=head;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    p->next=node;
    return 0;
}
//线程的任务函数：发送信息
void *send_msg(void *arg)
{
    char sbuf[100];
    char ipbuf[20];
    unsigned short port;
    while(1)
    {
        bzero(sbuf,sizeof(sbuf));
        bzero(ipbuf,sizeof(ipbuf));
        printf("要发送的IP地址：");
        scanf("%s",ipbuf);
        printf("请输入要发送的端口号：");
       scanf("%hu",&port);
        printf("请输入要发送的信息：");
        scanf("%s",sbuf);
         if (strcmp(sbuf, "quit") == 0)
        {
            printf("服务器主动退出\n");
            close(newsock);
            exit(0);   // 直接退出，连接关闭，客户端会检测到
        }
        //遍历链表，找到这个客户端对应的套接字，然后发送信息
        client_node *p=head->next;
        while(p!=NULL)
        {
            if(strcmp(p->ip,ipbuf)==0 && p->port==port)
            {
                break;
            }
            p=p->next;
        }
        if(p!=NULL)
        {
            send(p->sockfd,sbuf,strlen(sbuf),0);
        }
        
    }
}
void*recv_msg(void *arg)
{
    client_node *p=(client_node *)(arg);
    char rbuf[100];
    int ret;
    while(1)
    {
        bzero(rbuf,sizeof(rbuf));
        ret=recv(p->sockfd,rbuf,sizeof(rbuf),0);
        if(ret <= 0)
        {
            printf("客户端: %s %hu已断开连接\n",p->ip,p->port);
            pthread_exit(NULL);
        }   
        printf("接收到的信息为：%s\n",rbuf);
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
    bindaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    bindaddr.sin_port=htons(2000);
    struct sockaddr_in clientaddr;
    bzero(&clientaddr,sizeof(clientaddr));
    int len=sizeof(clientaddr);
    head=list_init();
    tcpsock=socket(AF_INET,SOCK_STREAM,0);
    if(tcpsock<0)
    {
        perror("创建失败");
        return -1;
    }
    int opt = 1;
    setsockopt(tcpsock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
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
    
    pthread_create(&ptid,NULL,send_msg,NULL);
    while(1)
    {
        newsock=accept(tcpsock,(struct sockaddr *)&clientaddr,&len);
        if(newsock<0)
        {
            perror("接受失败");
            return -1;
        }
       
        bzero(rbuf,sizeof(rbuf));
        client_node *newnode=malloc(sizeof(client_node));
        newnode->sockfd=newsock;
        strcpy(newnode->ip,inet_ntoa(clientaddr.sin_addr));
        newnode->port=ntohs(clientaddr.sin_port);
        insert_tail(newnode,head);
        pthread_create(&ptid,NULL,recv_msg,newnode);
    }
    close(newsock);
    close(tcpsock);
    return 0;
}