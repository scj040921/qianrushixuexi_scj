#ifndef __LIST_H
#define __LIST_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>

typedef struct node
{
    struct node *next;
    int data;
}node;
node *list_init(void);
node *new_node(int data);
void add_node(node *list,node *new);
void add_node_tail(node *list,node *new);
void list_for_each(node *list);
void list_destory(node *lst);


#endif