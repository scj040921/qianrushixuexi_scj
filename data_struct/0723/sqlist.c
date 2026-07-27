#include<stdio.h>
#include"sqlist.h"
sqlist *sqlist_init(int cap)
{
    sqlist *sql=malloc(sizeof(sqlist));
    if(sql!=NULL)
    {
        sql->data=calloc(cap,sizeof(int));
        if(sql->data==NULL)
        {
            free(sql);
            return NULL;
        }
        sql->capacity=cap;
        sql->last=-1;
    }
    return sql;
}
bool add_data(sqlist *sql,int n)
{
    if(sql->last>=sql->capacity-1)
    {
        return false;
    }
    sql->data[++sql->last]=n;
    return true;
}
bool is_empty(sqlist *sql)
{
    return sql->last==-1;
}
bool dl_data(sqlist *sql,int n)
{
    if(is_empty(sql))
    {
        return false;
    }
    for(int i=0;i<+sql->last;i++)
    {
        if(sql->data[i]==n)
        {
            for(int j=i;j<sql->last;j++)
            {
                sql->data[j]=sql->data[j+1];
            }
            sql->last--;return true;
        }
    }
    return false;
}
void output(sqlist *sql)
{
    if(is_empty(sql))
        return;
    for(int i=0;i<=sql->last;i++)
        printf("%d\t",sql->data[i]);
    printf("\n");
}
void reverse_output(sqlist *sql)
{
    if(is_empty(sql))
        return;
    for(int i=sql->last;i>=0;i--)
    {
        printf("%d\t",sql->data[i]);
    }
    printf("\n");
}
void sqlist_destory(sqlist *sql)
{
    if(sql!=NULL)
    {
        free(sql->data);
    }
    free(sql);
}


sort(sqlist *sql)
{
    int count=0;
    for(int i=0;i<sql->last;i++)
    {
        for(int j=0;j<sql->last-i-1;j++)
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