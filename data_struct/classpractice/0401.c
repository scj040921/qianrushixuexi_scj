#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct stack
{
    int *data;
    int size;
    int top;
}stack;
//初始化
stack *init_stack(int size)
{
    stack *s=malloc(sizeof(stack));
    if(s!=NULL)
    {
        s->data=calloc(size,sizeof(int));
        s->size=size;
        s->top=-1;
    }
    return s;
}
//盘满
bool is_full(stack *s)
{
    return s->top==s->size-1;
}
//入栈
bool push(stack *s,int data)
{
    if(is_full(s))
    {
        return false;
    }
    s->data[++s->top]=data;
    return true;
}
//判空
bool is_empty(stack *s)
{
    return s->top==-1;
}
//出栈
bool pop(stack *s,int *pm)
{
    if(is_empty(s))
    {
        return false;
    }
    *pm=s->data[s->top];
    s->top--;
    return true;
}
void show(stack *s)
{
    if(is_empty(s))
    {
        printf("空栈\n");
        return ;
    }
    for(int i=s->top;i>=0;i--)
    {
        printf("   %d",s->data[i]);
        if(i==s->top)
        {
            printf("栈顶");
        }
        printf("\n");
    }
}
int main()
{
    stack *s=init_stack(10);
    int n,k;
    while(1)
    {
        //如果输入数字就入栈
        if(scanf("%d",&n)==1)
        {
            if(!push(s,n))
            {
                printf("栈满\n");
                continue;
            }
        }
        else
        {
            while(getchar()!='\n');
            if(!pop(s,&k))
            {
                printf("栈空\n");
                continue;
            }
        }
        show(s);
    }
    return 0;
}