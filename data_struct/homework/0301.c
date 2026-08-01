#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"kernel_list.h"

typedef struct node
{
    int num;
    struct list_head list;    
}node;
struct list_head *new_node(int data)
{
    node *new=malloc(sizeof(node));
    if(new!=NULL)
    {
        new->num=data;
        INIT_LIST_HEAD(&new->list);
    }
    return &new->list;
}
void show_list(struct list_head *head)
{
    if(head ==NULL)
    {
        return; 
    }
    struct node *p;
    list_for_each_entry(p,head,list)
    {
        printf("%d ",p->num);
    }
    printf("\n");
}
int main()
{
    struct list_head *head=malloc(sizeof(struct list_head));
    INIT_LIST_HEAD(head);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=10;i++)
    {
        list_add_tail(new_node(i),head);
    }
    show_list(head);
    struct list_head *pos,*k=head->prev;
    node *p;
    list_for_each_prev(pos,head)
    {
        p=list_entry(pos,node,list);
        if(p->num%2==1)
        {
            k=pos;
        }else{
            list_move_tail(pos,head);
            pos=k;
        }
    }
    show_list(head);
    return 0;
}
strrchr