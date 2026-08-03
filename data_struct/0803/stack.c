#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
struct stack
{
    int *stack;
    int size;
    int top;
};
struct stack *init_stack(int size)
{
    struct stack *s=malloc(sizeof(struct stack));
    if(s!=NULL)
    {
        s->stack=calloc(size,sizeof(int));
        if(s->stack==NULL)
        {
            free(s);
            return NULL;
        }
        s->size=size;
        s->top=-1;
    }
    return s;
}
bool is_full(struct stack *s)
{
    return s->top==s->size-1;
}
void push(struct stack *s,int val)
{
    if(is_full(s))
    {
        int *tmp=realloc(s->stack,(s->size+10)*sizeof(int));
        if((tmp==NULL))
        {
            return;
        }
        s->stack=tmp;
        s->size+=10;
    }
    s->stack[++s->top]=val;
}
bool is_empty(struct stack *s)
{
    return s->top==-1;
}
int pop(struct stack *s)
{
    if(is_empty(s))
        return -1;
    return s->stack[s->top--];
}
void destroy_stack(struct stack *s)
{
    if(s==NULL)
        return;
    free(s->stack);
}
int main(void)
{
    struct stack *s=init_stack(10);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        push(s,i);
    }
    while(!is_empty(s))
    {
        printf("%d",pop(s));
    }
    printf("\n");
    destroy_stack(s);
    free(s);
    return 0;
}