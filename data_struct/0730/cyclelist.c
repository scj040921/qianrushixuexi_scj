#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}node;
node* init_list(void)
{
    node *head=malloc(sizeof(node));
    if(head==NULL)
    {
        printf("malloc failed");
        return NULL;
    }
    head->prev=head;
    head->next=head;
    return head;
}
node *new_node(int n)
{
    node *new=malloc(sizeof(node));
    if(new==NULL)
    {
        printf("malloc failed");
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
    for(int i=0;i<10;i++)
    {
        list_add_tail(head,new_node(i));
    }
    show_list(head);
    return 0;
}