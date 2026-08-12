#include "list.h"
#include <stdlib.h>
#include<stdio.h>
list_head *init_list()
{
    list_head *head=malloc(sizeof(list_head));
    if(head)
    {
        head->next=head;
        head->prev=head;
    }
    return head;
}
void add_node(list_head *head,list_head *new_node)
{
    new_node->next=head;
    new_node->prev=head->prev;
    head->prev->next=new_node;
    head->prev=new_node;
}
void remove_node(list_head *node)
{
    node->prev->next=node->next;
    node->next->prev=node->prev;
    free(node);
}
void traverse_list(list_head *head,void(*func)(list_head *node))
{
    list_head *current=head->next;
    while(current!=head)
    {
        func(current);
        current=current->next;
    }
}

