#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef DATATYPE
#define DATATYPE int
#endif
typedef DATATYPE datatype;
typedef struct node
{
    datatype data;
    struct node *prev;
    struct node *next;
}listnode,*linklist;
static linklist init_list(void)
{
    linklist head=malloc(sizeof(listnode));
    if(head==NULL)
    {
        printf("malloc failed");
        return NULL;
    }
    head->prev=head;
    head->next=head;
    return head;
}
static linklist new_node(datatype n,void(*assignment(datatype *,datatype)))
{
    linklist new=malloc(sizeof(listnode));
    if(new==NULL)
    {
        printf("malloc failed");
        return NULL;
    }
    if(assignment==NULL)
    {
        new->data=n;
    }
    else{
        assignment(&new->data,n);
    }
    new->prev=new;
    new->next=new;
    return new;
}
static void list_add_tail(linklist head,linklist new)
{
    new->prev=head->prev;
    new->next=head;

    head->prev->next=new;
    head->prev=new;
}
static void list_traverse(linklist head, void (*visit)(datatype))
{
    linklist p = head->next;
    while(p != head)
    {
        visit(p->data); // 访问具体的数据
        p = p->next;
    }
    printf("\n");
}
static void list_node_del(linklist p)
{
    p->prev->next=p->next;
    p->next->prev=p->prev;
    p->prev=p->next=p;
}
static void list_destory(linklist head,void(*destory)(datatype *))
{
    if (head==NULL)
        return;
    linklist p=head->next;
    for(;p!=head;p=p->next)   
    {
        list_node_del(p);
        if(destory==NULL)
            free(p);
        else
            destory(&p->data);
    }
    free(head);
    head=NULL;
}