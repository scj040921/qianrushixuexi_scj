#include"system.h"
#include"menu.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

list_head *user_list;
list_head *flight_list;
list_head *booking_record_list;
User *current_user=NULL;
//系统初始化
void init_system(void)
{
    user_list=init_list();
    flight_list=init_list();
    booking_record_list=init_list();
    //创建默认管理员
    User *admin=(User *)malloc(sizeof(User));
    if(admin)
    {
        admin->type=admin;
        strcpy(admin->id,"admin");
        strcpy(admin->name,"管理员");
        strcpy(admin->pwd,"admin123");
        strcpy(admin->phone,"12345678900");
        INIT_LIST_HEAD(&admin->bookings);
        INIT_LIST_HEAD(&admin->list);
        list_add(&admin->list,user_list);
    }
    add_flight(flight_list, "CA1234", "中国国航", "北京", "上海", "2026-04-21 08:00", "2026-04-21 10:00", 150, 800.0);
    add_flight(flight_list, "MU5678", "东方航空", "上海", "广州", "2026-04-21 10:00", "2026-04-21 12:00", 180, 900.0);
    add_flight(flight_list, "CZ3456", "南方航空", "广州", "北京", "2026-04-21 14:00", "2026-04-21 16:00", 200, 1000.0);
}
//系统清理
void cleanup_system(void)
{
    //清理用户列表
    User *user,*user_tmp;
    list_for_each_entry_safe(user,user_tmp,user_list,list)
    {
        list_del(&user->list);
        free(user);
    }
    free(user_list);
    //清理航班列表
    flight *flight,*flight_tmp;
    list_for_each_entry_safe(flight,flight_tmp,flight_list,list)
    {
        list_del(&flight->list);
        free(flight);
    }
    free(flight_list);
    //清理预定记录列表
    bookingrecord *booking,*booking_tmp;
    list_for_each_entry_safe(booking,booking_tmp,booking_record_list,list)
    {
        list_del(&booking->list);
        free(booking);
    }
    free(booking_record_list);
}
//根据用户名查找用户
User *find_user_by_name(const char *username)
{
    User *user;
    list_for_each_entry(user,user_list,list)
    {
        if(strcmp(user->id,username)==0)
        {
            return user;
        }
    }
    return NULL;
}
//检查用户名是否存在
int is_username_exist(const char *username)
{
    User *user;
    list_for_each_entry(user,user_list,list)
    {
        if(strcmp(user->id,username)==0)
        {
            return 1;
        }
    }
    return 0;
}
