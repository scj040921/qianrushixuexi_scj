#ifndef __SQLIST_H
#define __SQLIST_H
#include<stdbool.h>
//顺序结构体类型定义
typedef struct sqlist
{
    int *data;
    int capacity;
    int last;
}sqlist;

//操作的接口声明
struct sqlist *sqlist_init(int cap);
bool add_data(sqlist *sql,int n);
bool del_data(sqlist *sql,int n);
void output(sqlist *sql);
void reverse_output(sqlist* sql);
void sqlist_destory(sqlist *sql);
void sort(sqlist *sql);
#endif