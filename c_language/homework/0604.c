#include<stdio.h>
#include<string.h>
char *myStrcat(char *str1,char *str2)
{
    int i;
    i=strlen(str1);
    int j;
    for(j=0;j<50-i-1;j++)
    {
        str1[j+i]=str2[j];
    }
    return str1;
}
int main()
{
    char str1[50]="hello";
    char str2[50]="123456789012345";
    printf("合并后：%s\n",myStrcat(str1,str2));
    return 0;
}