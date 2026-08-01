
#include<stdio.h>
#include<string.h>
int main()
{
    int num;
    scanf("%d",&num);
    char *str=(char *)&num;
    int len=strlen(str);
    for(int i=0;i<len/2;i++)
    {
        char temp=str[i];
        str[i]=str[len-i-1];
        str[len-i-1]=temp;
    }
    printf("%d",num);
    return 0;
}
//编写一个函数，返回两个字符串的最大公串
int max_common_str(char *str1,char *str2)
{
    int len=strlen(str1);
    int len2=strlen(str2);
    for(int i=len;i>0;i--)
    {
        if(strncmp(str1,str2,i)==0)
        {
            return i;
        }
    }
    return 0;
}