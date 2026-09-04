#include "list.h"

list *head;

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

static list *find_client(const char *ip, unsigned short port)
{
    list *p = head->next;
    while(p != NULL)
    {
        if(strcmp(p->ip, ip) == 0 && p->port == port) return p;
        p = p->next;
    }
    return NULL;
}

static void send_online_list(list *client)
{
    char message[2048] = "getlist#";
    list *p = head->next;
    while(p != NULL)
    {
        char item[64];
        snprintf(item, sizeof(item), "%s:%hu#", p->ip, p->port);
        if(strlen(message) + strlen(item) + 2 >= sizeof(message)) break;
        strcat(message, item);
        p = p->next;
    }
    strcat(message, "\n");
    send_all(client->sock, message, strlen(message));
}

static int relay_data(int from_sock, int to_sock, long size)
{
    char buf[2048];
    long total = 0;
    while(total < size)
    {
        size_t want = size - total < (long)sizeof(buf) ? (size_t)(size - total) : sizeof(buf);
        ssize_t n = recv(from_sock, buf, want, 0);
        if(n <= 0 || send_all(to_sock, buf, (size_t)n) < 0) return -1;
        total += n;
    }
    return 0;
}

static void *recv_fun(void *arg)
{
    list *sender = arg;
    char line[2048];
    while(recv_line(sender->sock, line, sizeof(line)) == 0)
    {
        if(strcmp(line, "getlist") == 0)
        {
            send_online_list(sender);
            continue;
        }
        char *cmd = strtok(line, "@");
        char *ip = strtok(NULL, "@");
        char *port_text = strtok(NULL, "@");
        char *field4 = strtok(NULL, "@");
        if(cmd == NULL || ip == NULL || port_text == NULL || field4 == NULL) continue;
        list *target = find_client(ip, (unsigned short)atoi(port_text));
        if(target == NULL)
        {
            printf("没有找到目标客户端 %s:%s\n", ip, port_text);
            continue;
        }
        if(strcmp(cmd, "chat") == 0)
        {
            char message[2048];
            snprintf(message, sizeof(message), "chat#%s\n", field4);
            send_all(target->sock, message, strlen(message));
        }
        else if(strcmp(cmd, "file") == 0 || strcmp(cmd, "emoji") == 0)
        {
            char *type = strtok(NULL, "@");
            char *size_text = strtok(NULL, "@");
            long size;
            char message[2048];
            if(type == NULL || size_text == NULL || (size = atol(size_text)) < 0)
            {
                printf("%s消息格式错误\n", cmd);
                continue;
            }
            static unsigned int file_id = 1;
            static unsigned int emoji_id = 1;
            char filename[64];
            if(strcmp(cmd, "file") == 0)
                snprintf(filename, sizeof(filename), "file_%u", file_id++);
            else
                snprintf(filename, sizeof(filename), "emoji_%u", emoji_id++);
            snprintf(message, sizeof(message), "%s#%s#%ld#%s\n",
                     strcmp(cmd, "file") == 0 ? "sendfile" : "emoji", filename, size, type);
            if(send_all(target->sock, message, strlen(message)) < 0 || relay_data(sender->sock, target->sock, size) < 0)
                printf("转发%s失败\n", strcmp(cmd, "file") == 0 ? "文件" : "表情包");
        }
    }
    printf("客户端%s:%hu已断开连接\n", sender->ip, sender->port);
    close(sender->sock);
    list_delete(sender->ip, sender->port, head);
    return NULL;
}

int main(void)
{
    int listen_sock;
    struct sockaddr_in bindaddr = {0}, clientaddr = {0};
    pthread_attr_t attr;
    head = list_init();
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(10000);
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_sock < 0) { perror("socket"); return 1; }
    int on = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(bind(listen_sock, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) < 0) { perror("bind"); return 1; }
    if(listen(listen_sock, 10) < 0) { perror("listen"); return 1; }
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    printf("服务器已启动，监听端口 10000\n");
    while(1)
    {
        socklen_t size = sizeof(clientaddr);
        int sock = accept(listen_sock, (struct sockaddr *)&clientaddr, &size);
        if(sock < 0) { perror("accept"); continue; }
        list *node = calloc(1, sizeof(*node));
        if(node == NULL) { close(sock); continue; }
        node->sock = sock;
        snprintf(node->ip, sizeof(node->ip), "%s", inet_ntoa(clientaddr.sin_addr));
        node->port = ntohs(clientaddr.sin_port);
        list_insert_tail(node, head);
        printf("客户端%s:%hu已连接\n", node->ip, node->port);
        pthread_t tid;
        pthread_create(&tid, &attr, recv_fun, node);
    }
}
