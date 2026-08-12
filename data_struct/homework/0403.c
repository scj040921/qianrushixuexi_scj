#include<stdio.h>
#define MAX_SIZE 20
int stack[MAX_SIZE];
int top =0;
int output[MAX_SIZE];
int out_idx=0;
int n;
int total=0;
void dfs(int push_val)
{
    if(out_idx==n)
    {
        total++;
        for(int i=0;i<n;i++)
        {
            printf("%d",output[i]);
        }
        printf("\n");
        return;
    }
    if(top>0)
    {
        int poped=stack[--top];
        output[out_idx++]=poped;
        dfs(push_val);
        out_idx--;
        stack[top++]=poped;
    }
    if(push_val<=n)
    {
        stack[top++]=push_val;
        dfs(push_val+1);
        top--;
    }
}
int main() {
    printf("请输入车厢数量N: ");
    scanf("%d", &n);
    printf("所有可能的排列如下：\n");
    dfs(1);
    return 0;
}