#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
typedef int datatype;
typedef struct node
{
    datatype data;
    struct node *next;
}node;
typedef struct linkQueue
{
    node *front;
    node *rear;
    int size;
}linkQueue;
linkQueue *initQueue()
{
    linkQueue *q=malloc(sizeof(linkQueue));
    if(q!=NULL)
    {
        q->front=q->rear=NULL;
        q->size=0;
    }
    return q;
}
bool isEmpty(linkQueue *q)
{
    return q->size==0;
}
bool enQueue(linkQueue *q,datatype x)
{
    node *new=malloc(sizeof(node));
    if(new==NULL)
        return false;
    new->data=x;
    new->next=NULL;
    if(isEmpty(q))
        q->front=q->rear=new; 
    else
    {
        q->rear->next=new;
        q->rear=new;
    }  
    q->size++;
    return true;
}    
bool outQueue(linkQueue *q,datatype *pm)
{
    if(isEmpty(q))
        return false;
    *pm=q->front->data;
    if(q->size==1)
    {
        free(q->front);
        q->front=q->rear=NULL;
    }
    else
    {
        node *tmp=q->front;
        q->front=q->front->next;
        tmp->next=NULL;
        free(tmp);
    }
    q->size--;
    return true;
}
bool front(linkQueue *q,datatype *pm)
{
    if(isEmpty(q))
    {
        return false;
    }
    *pm=q->front->data;
    return true;
}
bool find(linkQueue *q,int data)
{
    if(isEmpty(q))
        return false;
    for(node *tmp=q->front;tmp!=NULL;tmp=tmp->next)
    {
        if(tmp->data==data)
        {
            return true;
        }
    }
    return false;
}
int main()
{
    int a[]={5,5,7,2,9,6,5};
    linkQueue *q=initQueue();
    int maxLen=0;
    int tmp;
    for(int i=0;i<6;i++)
    {
        while(!isEmpty(q)&&find(q,a[i]))
        {
            outQueue(q,&tmp);
            maxLen--;
        }
        enQueue(q,a[i]);
        maxLen++;
    }
    printf("%d",maxLen);
}
