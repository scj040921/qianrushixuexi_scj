#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
typedef struct queue
{
    int *data;
    int size;
    int head;
    int tail;
}queue;
queue *init_queue(int size)
{
    queue *q=malloc(sizeof(queue));
    if(q!=NULL)
    {
        q->data=malloc(size*sizeof(int));
        if(q->data==NULL)
        {
            free(q);
            return NULL;
        }
        q->size=size;
        q->head=q->tail=0;
    }
    return q;
}
bool is_empty(queue *q)
{
    return q->head==q->tail;
}
bool is_full(queue *q)
{
    return (q->tail+1)%q->size==q->head;
}
bool outqueue(queue *q,int *pm)
{
    if(is_empty(q))
        return false;
    *pm=q->data[q->head];
    q->head=(q->head+1)%q->size;
    return true;
}
bool en_queue(queue *q ,int data)
{
    if(is_full(q))
        return false;
    q->data[q->tail]=data;
    q->tail=(q->tail+1)%q->size;
    return true;
}
void show(queue *q)
{
    if(is_empty(q))
        return ;
    int i;
    for(i=q->head;i!=q->tail;i=(i+1)%q->size)
    {
        if(i==q->head)
        {
            printf("队头");
        }
        printf("%d",q->data[i]);
        if((i+1)%q->size==q->tail)
            printf("队尾");
        printf("\t");
    }
    printf("\n");
}
int main()
{
    queue *q=init_queue(5);
    int n,data;
    while(1)
    {
        if(scanf("%d",&n)==1)
        {
            if(!en_queue(q,n))
            {
                printf("队满\n");
                continue;
            }
        }
        else{
            while(getchar()!='\n');
            if(!outqueue(q,&data))
            {
                printf("队空\n");
                continue;
            }
            printf("%d已出队\n",data);
        }
        show(q);
    }
    return 0;
}