#include<stdio.h>
#include<string.h>
void strip(char *str)
{
    if(str==NULL)
    {
        return;
    }
    int i,j;
    char *p=str;
    for(i=1;str[i]!='\0';i++)
    {
        for(j=0;j<i;j++)
        {
            if(p[j]==str[i])
            {
                str[i]=-1;
                break;
            }
        }
    }
    int first=0,second=0;
    for(int i=1;str[i]!='\0';i++)
    {
        if(str[i]!=REDUNDANT)
        i++;
    }
}
int main()
{
//     int n;
//     printf("请输入字符串的长度\n");
//     scanf("%d",&n);
//     printf("请输入要去重的字符串\n");
//     char s[n];
//     scanf("%s",s);
//     char temp[n+1];
//    temp[0]='\0';
//     int j=0;
//     for(int i=0;i<n;i++)
//     {
//         if(strchr(temp,s[i]))
//         {
//             continue;
//         }else{
//             temp[j++]=s[i];
//             temp[j]='\0';//每次赋值后将下一位设为结束标记防止内存垃圾影响输出
//         }
//     }
//    printf("%s",temp);
//    return 0;

}