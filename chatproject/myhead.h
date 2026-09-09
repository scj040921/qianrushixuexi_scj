#ifndef _MYHEAD_H
#define _MYHEAD_H

//把C语言所有目前常用的头文件都包含进来
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
#include <sys/mman.h>
#include <sys/wait.h> //跟wait，waitpid有关的头文件
#include <signal.h> //跟信号有关的头文件
#include <pthread.h>  //跟线程有关的头文件
#include <sys/socket.h>  //跟网络编程有关的头文件
#include <netinet/in.h>  //跟网络编程有关的头文件
#include <arpa/inet.h>   //跟网络编程有关的头文件

static int send_all(int sock, const void *buf, size_t len)
{
    const char *p = buf;
    while(len > 0)
    {
        ssize_t n = send(sock, p, len, 0);
        if(n <= 0) return -1;
        p += n;
        len -= (size_t)n;
    }
    return 0;
}

static int recv_line(int sock, char *buf, size_t size)
{
    size_t used = 0;
    while(used + 1 < size)
    {
        char ch;
        ssize_t n = recv(sock, &ch, 1, 0);
        if(n <= 0) return -1;
        if(ch == '\n')
        {
            buf[used] = '\0';
            return 0;
        }
        buf[used++] = ch;
    }
    buf[used] = '\0';
    return -2;
}

#endif
