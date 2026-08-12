#ifndef USER_H
#define USER_H
#include"list.h"
//定义用户类型
typedef struct usertype
{
    admin=0,
    passenger=1
}usertype;
typedef struct user
{
    usertype type;
    char id[20];
    char name[20];
    char pwd[20];
    char phone[20];
    list_head boolings;
    list_head list;
}user;
void register_user(user *user);
int login_user(user *user);
void display_user_info(user *user);
#endif