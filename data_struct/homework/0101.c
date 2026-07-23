#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    struct node *next;
    int data;
}node;
node *list_init(void)
{
    node *head=malloc(sizeof(node));
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
void add_node(node *list,node *num)
{
    if(list==NULL||num==NULL)
    {
        return;
    }
    num->next=list->next;
    list->next=num;
}
void add_tail(node *list,node *num)
{
    node *tail;
    for(tail=list;tail->next!=NULL;tail=tail->next);
    tail->next=num;
    num->next=NULL;
}
int main()
{
    node *mylist=list_init();
    int a[]={1,2,3,4,5};
    for(int i=0;i<5;i++)
    {
        add_tail(mylist,new_node(a[i]));
    }
    node *p=mylist->next;
    node *relist=list_init();
    for(;p!=NULL;)
    {
        node *next=p->next;
        add_node(relist,p);
        p=next;
    }
   for(int i=0;i<5;i++)
   { 
    relist=relist->next;
    printf("%d",relist->data);
   }
    return 0;
}
