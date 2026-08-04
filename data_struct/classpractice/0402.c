#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//链式栈的节点
typedef struct node
{
    int data;
    struct node *next;
}node;
//创建栈管理结构体
typedef struct stack
{
    struct node *top;
    int size;
}stack;
//初始化空栈
stack *init_stack(void)
{
    stack *s=malloc(sizeof(stack));
    if(s!=NULL)
    {
        s->top=NULL;
        s->size=0;
    }
    return s;
}
//入栈
void push(int data,stack *s)
{
    node *p=malloc(sizeof(node));
    if(p!=NULL)
    {
        p->data=data;
        p->next=s->top;
        s->top=p;
        s->size++;
    }
}
//判空
bool is_empty(stack *s)
{
    return s->size==0;
}
//出栈
bool pop(stack *s,int *pm)
{
    if(is_empty(s))
        return false;
    *pm=s->top->data;
    node *tmp=s->top;
    s->top=s->top->next;
    free(tmp);
    s->size--;
    return true;    
}
int main()
{
    stack *s=init_stack();
    int n;
    scanf("%d",&n);
    while(n>0)
    {
        push(n%8,s);
        n/=8;
    }
    int m;
    printf("0");
    while(1)
    {
        if(is_empty(s))
            break;
        pop(s,&m);
        printf("%d",m);
    }
    printf("\n");
    return 0;
}