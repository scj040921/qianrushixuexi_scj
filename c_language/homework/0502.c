#include<stdio.h>
int maxvalue(int a,int b,int c)
{
    int temp=a>b?a:b;
    return temp>c?temp:c;

}