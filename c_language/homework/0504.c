#include<stdio.h>
#include<string.h>

void myStrncat(char *s1, char *s2, int n)
{
    char *p=s1+strlen(s1);
    int i;
    for(i=0;s2[i]!='\0'&&i<n;i++)
    {
        p[i]=s2[i];
    }
    p[i]='\0';
}
int main()
{
    char s1[50];
    char s2[50];;
    fgets(s1,50,stdin);
    fgets(s2,50,stdin);
    strtok(s1,"\n");
    strtok(s2,"\n");

    myStrncat(s1,s2,sizeof(s1)-strlen(s1)-1);
    printf("%s",s1);
    printf("%s",s2);
    return 0;
}