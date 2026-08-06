#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
typedef struct node
{
    int data;
    struct node *next;
}node;
typedef struct queue
{
    node *head;
    node *tail;
    int size;
}queue;
queue *init_queue()
{
    queue *q=malloc(sizeof(queue));
    if(q!=NULL)
    {
        q->head=q->tail=NULL;
        q->size=0;
    }
    return q;
}
bool is_empty(queue *q)
{
    return q->size==0; 
}
node *out_queue(queue *q)
{
    if(is_empty(q))
        return NULL;
    struct node *tmp=q->head;
    q->head=q->head->next;
    tmp->next=NULL;
    if(q->head==NULL)
        q->tail=NULL;
    return tmp;
}
void en_queue(queue *q,node *new)
{
    if(new==NULL)
        return;
    if(is_empty(q))
    {
        q->head=q->tail=new;
    }
    else{
        q->tail->next=new;
        q->tail=new;
    }
    q->size++;
}
void show(queue *q)
{
    if(is_empty(q))
    {
        return;
    }
    node *tmp;
    for(tmp=q->head;tmp!=NULL;tmp=tmp->next)
    {
        if(tmp==q->head)
        {
            printf("队头");
        }
        printf("%d",tmp->data);
        if(tmp->next==NULL)
        {
            printf("队尾");
        }
        printf("\t");
    }
    printf("\n");
}
struct node *new_node(int data)
{
    node *new=malloc(sizeof(node));
    if(new!=NULL)
    {
        new->data=data;
        new->next=NULL;
    }
    return new;
}
int main()
{
    queue *q=init_queue();
    int n,data;
    while(1)
    {
        if(scanf("%d",&n)==1)
        {
            en_queue(q,new_node(n));
        }
        else{
            while(getchar()!='\n');
            node *head=out_queue(q);
            if(!head)
            {
                printf("队空\n");
                continue;
            }
            printf("%d出队\n",head->data);
        }
        show(q);
    }
    return 0;
}
