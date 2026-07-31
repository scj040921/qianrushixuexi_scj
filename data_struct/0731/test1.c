#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"kernel_list.h"
struct node
{
    int data;
    struct list_head list;
};
struct node *init_list(void)
{
    struct node *head=malloc(sizeof(struct node));
    if(head!=NULL)
    {
        INIT_LIST_HEAD(&head->list);
    }
    return head;
}
void show_list(struct node *head)
{
    struct list_head *pos;
    list_for_each_prev(pos,&head->list)
    {
         struct node *p=list_entry(pos,struct node,list);
         printf("%d\t",p->data);
    }
    printf("\n");
}
int main()
{
    struct node *head=init_list();
    for(int i=1;i<=10;i++)
    {
        struct node *n=malloc(sizeof(struct node));
        n->data=i;
        list_add(&n->list,&head->list);
    }
    show_list(head);
    return 0;
}