#include<stdio.h>
void strip_space(char *s)
{
    int i=0;
    while(s[i]!=' '&&s[i]!='\0')//定位第一个空格
    i++;
    if(s[i]=='\0')
    {
        return;
    }
    int j=i+1;
    while(s[j]==' ')
        j++;
    for(;s[j]!='\0';j++)
    {
        if(s[j]!=' ')
        {
            s[i]=s[j];
            i++;
        }
    }
    s[i]=s[j];
}
int main()
{
    char s[50];
    int len = strlen(s);
    if (len > 0 && s[len-1] == '\n') s[len-1] = '\0';   
    fgets(s,50,stdin);
    strip_space(s);
    printf("%s",s);
    return 0;
}