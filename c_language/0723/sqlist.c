#include<stdio.h>
#include"sqlist.h"
sort(sql)
{
    int count=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(sql->data[j]>sql->data[j++])
            {
                swap(sql[j],sql[j+1]);
                count=1;
            }
        }
        if(count==0)
        {
            break;
        }
    }
}