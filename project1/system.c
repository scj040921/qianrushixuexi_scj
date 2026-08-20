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
// 根据用户名查找用户
User* find_user_by_username(const char *username) {
    User *user;
    list_for_each_entry(user, user_list, list) {
        if (strcmp(user->id, username) == 0) {
            return user;
        }
    }
    return NULL;
}

// 注册新用户
int register_new_user(usertype user_type) {
    User *user = (User *)malloc(sizeof(User));
    if (!user) {
        return 0;
    }
    
    user->type = user_type;
    
    printf("请输入用户ID: ");
    scanf("%s", user->id);
    
    if (is_username_exists(user->id)) {
        printf("用户ID已存在，请重新输入\n");
        free(user);
        return 0;
    }
    
    printf("请输入用户姓名: ");
    scanf("%s", user->name);
    
    printf("请输入密码: ");
    scanf("%s", user->pwd);
    
    printf("请输入电话号码: ");
    scanf("%s", user->phone);
    
    INIT_LIST_HEAD(&user->bookings);
    INIT_LIST_HEAD(&user->list);
    list_add(&user->list, user_list);
    
    printf("注册成功！\n");
    return 1;
}

// 管理员登录
int login_admin_system(void) {
    char id[20], pwd[20];
    printf("请输入管理员ID: ");
    scanf("%s", id);
    printf("请输入密码: ");
    scanf("%s", pwd);
    
    User *user = find_user_by_username(id);
    if (user && user->type == admin && strcmp(user->pwd, pwd) == 0) {
        current_user = user;
        printf("登录成功！\n");
        return 1;
    }
    
    printf("登录失败，请检查ID和密码\n");
    return 0;
}

// 用户登录
int login_user_system(void) {
    char id[20], pwd[20];
    printf("请输入用户ID: ");
    scanf("%s", id);
    printf("请输入密码: ");
    scanf("%s", pwd);
    
    User *user = find_user_by_username(id);
    if (user && user->type == passenger && strcmp(user->pwd, pwd) == 0) {
        current_user = user;
        printf("登录成功！\n");
        return 1;
    }
    
    printf("登录失败，请检查ID和密码\n");
    return 0;
}

// 管理员菜单循环
void admin_menu_loop(void) {
    int choice;
    while (1) {
        display_admin_menu();
        printf("请输入选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_new_flight();
                break;
            case 2:
                delete_flight();
                break;
            case 3:
                edit_flight_info();
                break;
            case 4:
                display_flights(flight_list);
                break;
            case 5:
                display_all_users();
                break;
            case 6:
                edit_user_info();
                break;
            case 7:
                display_booking_statistics();
                break;
            case 0:
                current_user = NULL;
                return;
            default:
                printf("无效选择，请重新输入\n");
        }
    }
}

// 乘客菜单循环
void passenger_menu_loop(void) {
    int choice;
    while (1) {
        display_passenger_menu();
        printf("请输入选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                guest_browse_flights();
                break;
            case 2:
                book_flight();
                break;
            case 3:
                cancel_booking();
                break;
            case 4:
                display_booking_history();
                break;
            case 5:
                modify_personal_info();
                break;
            case 0:
                current_user = NULL;
                return;
            default:
                printf("无效选择，请重新输入\n");
        }
    }
}

// 游客浏览航班
void guest_browse_flights(void) {
    display_flights(flight_list);
}

// 显示所有用户
void display_all_users(void) {
    User *user;
    printf("\n用户列表:\n");
    printf("--------------------------------------------------\n");
    printf("用户ID | 用户姓名 | 用户类型 | 电话号码\n");
    printf("--------------------------------------------------\n");
    list_for_each_entry(user, user_list, list) {
        printf("%s | %s | %s | %s\n",
               user->id, user->name,
               user->type == admin ? "管理员" : "乘客",
               user->phone);
    }
    printf("--------------------------------------------------\n");
}

// 显示预订统计
void display_booking_statistics(void) {
    booking *booking;
    int total_bookings = 0, active_bookings = 0;
    
    list_for_each_entry(booking, booking_record_list, list) {
        total_bookings++;
        if (booking->status == 0 || booking->status == 1) {
            active_bookings++;
        }
    }
    
    printf("\n预订统计:\n");
    printf("总预订数: %d\n", total_bookings);
    printf("活跃预订数: %d\n", active_bookings);
}

// 编辑航班信息
void edit_flight_info(void) {
    char id[20];
    printf("请输入要编辑的航班ID: ");
    scanf("%s", id);
    
    flight *flight = find_flight(flight_list, id);
    if (!flight) {
        printf("航班不存在\n");
        return;
    }
    
    printf("当前航班信息:\n");
    printf("航班ID: %s\n", flight->id);
    printf("航空公司: %s\n", flight->airline);
    printf("出发地: %s\n", flight->departure);
    printf("目的地: %s\n", flight->destination);
    printf("出发时间: %s\n", flight->departure_time);
    printf("到达时间: %s\n", flight->arrival_time);
    printf("容量: %d\n", flight->capacity);
    printf("价格: %.2f\n", flight->price);
    
    printf("请输入新的航空公司: ");
    scanf("%s", flight->airline);
    printf("请输入新的出发地: ");
    scanf("%s", flight->departure);
    printf("请输入新的目的地: ");
    scanf("%s", flight->destination);
    printf("请输入新的出发时间: ");
    scanf("%s", flight->departure_time);
    printf("请输入新的到达时间: ");
    scanf("%s", flight->arrival_time);
    printf("请输入新的容量: ");
    scanf("%d", &flight->capacity);
    printf("请输入新的价格: ");
    scanf("%f", &flight->price);
    
    flight->available_seats = flight->capacity;
    printf("航班信息更新成功\n");
}

// 编辑用户信息
void edit_user_info(void) {
    char id[20];
    printf("请输入要编辑的用户ID: ");
    scanf("%s", id);
    
    User *user = find_user_by_username(id);
    if (!user) {
        printf("用户不存在\n");
        return;
    }
    
    printf("当前用户信息:\n");
    display_user_info(user);
    
    printf("请输入新的用户姓名: ");
    scanf("%s", user->name);
    printf("请输入新的密码: ");
    scanf("%s", user->pwd);
    printf("请输入新的电话号码: ");
    scanf("%s", user->phone);
    
    printf("用户信息更新成功\n");
}

// 添加新航班
void add_new_flight(void) {
    char id[20], airline[50], departure[50], destination[50], departure_time[20], arrival_time[20];
    int capacity;
    float price;
    
    printf("请输入航班ID: ");
    scanf("%s", id);
    printf("请输入航空公司: ");
    scanf("%s", airline);
    printf("请输入出发地: ");
    scanf("%s", departure);
    printf("请输入目的地: ");
    scanf("%s", destination);
    printf("请输入出发时间: ");
    scanf("%s", departure_time);
    printf("请输入到达时间: ");
    scanf("%s", arrival_time);
    printf("请输入容量: ");
    scanf("%d", &capacity);
    printf("请输入价格: ");
    scanf("%f", &price);
    
    add_flight(flight_list, id, airline, departure, destination, departure_time, arrival_time, capacity, price);
}

// 删除航班
void delete_flight(void) {
    char id[20];
    printf("请输入要删除的航班ID: ");
    scanf("%s", id);
    remove_flight(flight_list, id);
}

// 预订航班
void book_flight(void) {
    char flight_id[20];
    printf("请输入要预订的航班ID: ");
    scanf("%s", flight_id);
    
    flight *flight = find_flight(flight_list, flight_id);
    if (!flight) {
        printf("航班不存在\n");
        return;
    }
    
    if (flight->available_seats <= 0) {
        printf("航班已满，无法预订\n");
        return;
    }
    
    // 创建预订记录
    booking *booking = (booking *)malloc(sizeof(booking));
    if (booking) {
        strcpy(booking->user_id, current_user->id);
        strcpy(booking->flight_id, flight_id);
        sprintf(booking->flight_info, "%s %s->%s %s", flight->airline, flight->departure, flight->destination, flight->departure_time);
        
        // 获取当前时间
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        sprintf(booking->booking_date, "%04d-%02d-%02d %02d:%02d:%02d", 
                tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday,
                tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
        
        booking->status = 0; // 预订中
        INIT_LIST_HEAD(&booking->list);
        list_add(&booking->list, booking_record_list);
        list_add(&booking->list, &current_user->bookings);
        
        // 更新航班座位
        update_flight_seats(flight, -1);
        
        printf("预订成功！\n");
    }
}

// 取消预订
void cancel_booking(void) {
    char flight_id[20];
    printf("请输入要取消的航班ID: ");
    scanf("%s", flight_id);
    
    booking *booking, *booking_tmp;
    int found = 0;
    
    list_for_each_entry_safe(booking, booking_tmp, &current_user->bookings, list) {
        if (strcmp(booking->flight_id, flight_id) == 0 && (booking->status == 0 || booking->status == 1)) {
            // 更新航班座位
            Flight *flight = find_flight(flight_list, flight_id);
            if (flight) {
                update_flight_seats(flight, 1);
            }
            
            // 更新预订状态
            booking->status = 2; // 已取消
            found = 1;
            printf("预订取消成功！\n");
            break;
        }
    }
    
    if (!found) {
        printf("未找到该航班的预订记录\n");
    }
}

// 显示预订历史
void display_booking_history(void) {
    booking *booking;
    printf("\n预订历史:\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("航班ID | 航班信息 | 预订日期 | 状态\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    
    list_for_each_entry(booking, &current_user->bookings, list) {
        const char *status_str;
        switch (booking->status) {
            case 0:
                status_str = "预订中";
                break;
            case 1:
                status_str = "已出票";
                break;
            case 2:
                status_str = "已取消";
                break;
            default:
                status_str = "未知";
        }
        printf("%s | %s | %s | %s\n",
               booking->flight_id, booking->flight_info, booking->booking_date, status_str);
    }
    printf("---------------------------------------------------------------------------------------------------\n");
}

// 修改个人信息
void modify_personal_info(void) {
    printf("当前个人信息:\n");
    display_user_info(current_user);
    
    printf("请输入新的用户姓名: ");
    scanf("%s", current_user->name);
    printf("请输入新的密码: ");
    scanf("%s", current_user->pwd);
    printf("请输入新的电话号码: ");
    scanf("%s", current_user->phone);
    
    printf("个人信息更新成功\n");
}

// 添加预订记录
void add_booking_record(const char *user_id, const char *flight_id, const char *flight_info) {
    BookingRecord *booking = (BookingRecord *)malloc(sizeof(BookingRecord));
    if (booking) {
        strcpy(booking->user_id, user_id);
        strcpy(booking->flight_id, flight_id);
        strcpy(booking->flight_info, flight_info);
        
        // 获取当前时间
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        sprintf(booking->booking_date, "%04d-%02d-%02d %02d:%02d:%02d", 
                tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday,
                tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
        
        booking->status = 0; // 预订中
        INIT_LIST_HEAD(&booking->list);
        list_add(&booking->list, booking_record_list);
        
        // 添加到用户的预订列表
        User *user = find_user_by_username(user_id);
        if (user) {
            list_add(&booking->list, &user->bookings);
        }
    }
}

// 更新预订记录
void update_booking_record(const char *user_id, const char *flight_id, int status) {
    booking *booking;
    list_for_each_entry(booking, booking_record_list, list) {
        if (strcmp(booking->user_id, user_id) == 0 && strcmp(booking->flight_id, flight_id) == 0) {
            booking->status = status;
            break;
        }
    }
}