#include"user.h"
#include<stdio.h>
#include<string.h>
void register_user(user *user)
{
    printf("注册用户：%s\n",user->name);
}
int login_user(user *user)
{
    printf("用户登录：%s\n",user->id);
    return 1;
}
void display_user_info(user *user)
{
    printf("用户ID:%s\n",user->id);
    printf("用户名：%s\n",user->name);
    printf("用户类型：%s\n",user->type);
    printf("电话号码：%s\n",user->phone);
}