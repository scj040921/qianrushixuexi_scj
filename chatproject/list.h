#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>  //文件IO有关的头文件
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>  //目录有关的头文件
#include <errno.h> //perror有关  errno有关的头文件
#include <stdbool.h>
#include <sys/socket.h>  //跟网络编程有关的头文件
#include <netinet/in.h>  //跟网络编程有关的头文件
#include <arpa/inet.h>   //跟网络编程有关的头文件
#include <pthread.h>  //跟线程有关的头文件

//定义结构体来表示单链表
typedef struct singlelist
{
    //数据域--》存放所有连接成功的客户端信息
    int sock;
    char ip[20]; //客户端ip地址
    unsigned short port; //客户端端口号
    //指针域
    struct singlelist *next;
} list;

extern list *list_init(void);
extern int list_insert_tail(list *newnode, list *head);
extern int list_delete(char *delip, unsigned short delport, list *head);

#endif
