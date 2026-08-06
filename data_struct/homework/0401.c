#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
typedef struct stack
{
    int *data;
    int top;
    int size;
}stack;
stack *init_stack(int size)
{
    stack *p=malloc(sizeof(stack));
    if(p!=NULL)
    {
        p->data=calloc(size,sizeof(int));
        p->size=size;
        p->top=-1;
    }
    return p;
}
bool is_full(stack *p)
{
    return p->top==p->size-1;
}
bool is_empty(stack *p)
{
    return p->top==-1;
}
bool push(stack *p,int data)
{
    if(is_full(p))
    {
        return false;
    }
    p->top++;
    p->data[p->top]=data;
    return true;
}
bool pop(stack *p,int *tmp)
{
    if(is_empty(p))
    {
        return false;
    }
    *tmp=p->data[p->top];
    p->top--;
    return true;
}
void show(stack *p)
{
    if(is_empty(p))
    {
        printf("空栈\n");
        return;
    }
    for(int i=p->top;i>=0;i--)
    {
        printf("   %d",p->data[i]);
        if(p->top==i)
        {
            printf("<-栈顶");
        }
        printf("\n");
    }
}
int main()
{
    stack *s=init_stack(20);
    int n;
    scanf("%d",&n);
    int m=abs(n);
    while(m>0)
    {
        push(s,m%16);
        m/=16;
    }
    printf("%c0x",n<0?'-':'\r');
    int tmp;
    while(!is_empty(s))
    {
        pop(s,&tmp);
        printf("%c", tmp < 10 ? tmp + '0' : tmp - 10 + 'A');
    }
    printf("\n");
    return 0;
}