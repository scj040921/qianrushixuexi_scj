#include"list.h"
node *list_init(void)
{
    node *head =malloc(sizeof(node));
    if(head!=NULL)
    {
        head->next=NULL;
    }
    return head;
}
node *new_node(int data)
{
    node *newNode=malloc(sizeof(node));
    if(newNode!=NULL)
    {
        newNode->data=data;
        newNode->next=NULL;
    }
    return newNode;
}
void add_node(node *list,node *new)
{
    if(list==NULL||new==NULL)
    {
        return;
    }
        new->next=list->next;
        list->next=new;
}
void add_node_tail(node *list,node *new)
{
    node *tail;
    for(tail=list;tail->next!=NULL;tail->next=tail);
    tail->next=new;
}
void list_for_each(node *list)
{
    for(node *p=list->next;p!=NULL;p->next=p)
    {
        printf("%d\t",p->data);
    }
    printf("\n");
}
void list_destory(node *list)
{
    node *temp;
    for(node *p=list;p!=NULL;p=temp)
    {
        temp==list->next;
        free(p);
    }
    return;
}