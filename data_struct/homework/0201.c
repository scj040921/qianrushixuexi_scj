#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
}node;
node *init_list(void)
{
    node *head=malloc(sizeof(node));
    if(head==NULL)
    {
        printf("malloc failed");
        return NULL;
    }
    head->next=head;
    head->prev=head;
    return head;
}
node *new_node(int n)
{
    node *new=malloc(sizeof(node));
    if(new==NULL)
    {
        printf("new failed");
        return NULL;
    }
    new->data=n;
    new->prev=new;
    new->next=new;
    return new;
}
void list_add_tail(node *head,node *new)
{
    new->prev=head->prev;
    new->next=head;
    head->prev->next=new;
    head->prev=new;
}
void sort_list(node *head)
{
    if(head==NULL||head->next==head)
    return;
    node *p=head->prev;
   
    while(p!=head)
    { 
        node *q=p->prev;
        if(p->data%2!=0)
        {
            p=p->prev;
        }else{
            p->prev->next=p->next;
            p->next->prev=p->prev;
            p->prev=head->prev;
            p->next=head;
            head->prev->next=p;
            head->prev=p;
            p=q;            
        }
    }
}
void show_list(node *head)
{
    node *p=head->next;
    while(p!=head)
    {
        printf("%d",p->data);
        p=p->next;
    }
    printf("\n");
}
int main()
{
    node *head=init_list();
    for(int i=1;i<11;i++)
    {
        list_add_tail(head,new_node(i));
        printf("%d",i);
    }
    printf("\n");
    sort_list(head);
    show_list(head);
}
