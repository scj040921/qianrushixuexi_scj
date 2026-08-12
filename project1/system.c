#include"system.h"
#include"menu.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

list_head *user_list;
list_head *flight_list;
list_head *booking_record_list;
user *current_user=NULL;
//系统初始化
void init_system(void)
{
    user_list=init_list();
    flight_list=init_list();
    booking_record_list=init_list();
    //创建默认管理员
    user *admin=(user*)malloc(sizeof(user));
    if(admin)
    {
        admin->type=admin;
        strcpy(admin->id,"admin");
    }
}
