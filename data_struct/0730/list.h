#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef DATATYPE
#define DATATYPE int
#endif
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
void list_add_tail(linklist head,linklist new)
{
    new->prev=head->prev;
    new->next=head;

    head->prev->next=new;
    head->prev=new;
}
void list_traverse(linklist head, void (*visit)(datatype))
{
    linklist p = head->next;
    while(p != head)
    {
        visit(p->data); // 访问具体的数据
        p = p->next;
    }
    printf("\n");
}