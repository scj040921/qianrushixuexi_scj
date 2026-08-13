#ifndef USER_H
#define USER_H
#include"list.h"
//定义用户类型
typedef enum usertype
{
    admin=0,
    passenger=1
}usertype;
typedef struct User
{
    usertype type;
    char id[20];
    char name[20];
    char pwd[20];
    char phone[20];
    list_head bookings;
    list_head list;
}User;
void register_user(User *user);
int login_user(User *user);
void display_user_info(User *user);
#endif