#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define SIZE 20
typedef int datatype;
typedef struct node
{
    datatype data;
    struct node *next;
}node;
typedef struct hash
{
    unsigned long table_size;//记录哈希桶的数量
    struct node **table_entry;//一个动态分配的指针数组，每个元素是一个链表的头街迪阿尼地址
}hash;
void show(hash *h,unsigned long pos,datatype data);
hash *init_hash(unsigned long size)
{
    hash *h=malloc(sizeof(hash));
    h->table_size=size;
    h->table_entry=calloc(size,sizeof(node *));
    return h;
}
void hash_add(datatype data,hash *h)
{
    unsigned long addr=data%(SIZE-1);
    node *new=malloc(sizeof(node));
    new->data=data;
    new->next=NULL;
    show(h,addr,data);
    if(h->table_entry[addr]==NULL)
    {
        h->table_entry[addr]=new;
    }
    else
    {
        node *p=h->table_entry[addr];
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=new;
    }
}
void show(hash *h,unsigned long pos,datatype data)
{
    node *p;
    int i;
    for(i=0;i<h->table_size;i++)
    {
        p=h->table_entry[i];
        printf("table_entry[%d]:",i);
        if(p!=NULL)
        {
            node *q=p;
            while(q!=NULL)
            {
                printf("%d",q->data);
                q=q->next;
            }
        }
        if(pos==i)
        {
            printf("\t<--%d\n",data);
        }
        else
        {
            printf("\n");
        }
    }
}
int main()
{
    hash *h=init_hash(SIZE);
    srand(time(NULL));
    int i;
    for(i=0;i<10;i++)
    {
        hash_add(rand()%1000,h);
        sleep(1);
    }
    show(h,-1,-1);
    return 0;
}