#ifndef SYSTEM_H
#define SYSTEM_H

#include"flight.h"
#include"user.h"
#include"list.h"
extern list_head *user_list;
extern list_head *flight_list;
extern list_head *booling_record_list;
extern user *current_user;
//系统管理函数
void init_system(void);
void cleanup_system(void);
int is_username_exits(const char *username);
user *find_user_by_username(const char *username);
int register_new_user(usertype *user_type);
int login_admin_system(void);
int login_user_system(void);
void admin_menu_loop(void);
void passenger_menu_loop(void);
void guest_browser_flights(void);
//管理员功能函数
void display_all_users(void);
void display_booking_statics(void);
void edit_flight_info(void);
void edit_user_info(void);
void add_new_flight(void);
void delete_flight(void);
//乘客功能函数
void book_flight(void);
void cancel_booking(void);
void display_booking_history(void);
void modify_personal_info(void);
//预定记录相关函数
void add_booking_record(const char *user_id,const char *flight_id,const char *flight_info);
void update_booking_record(const char *user_id,const char *flight_id,int status);

#endif