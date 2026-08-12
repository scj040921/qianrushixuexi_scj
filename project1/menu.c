#include "menu.h"
#include <stdio.h>
void main_menu(void)
{
    int choice =0;
    while(1)
    {
        display_main_menu();
        printf("请输入选择：");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                handle_login();
                break;
            case 2:
                handle_registration();
                break;
            case 3:
                guest_brose_flights();
                break;
            case 0:
                return;
            default:
                printf("无效选择，请重新输入\n");     
        }
    }
}
//处理登录
void handle_login(void)
{
    int choice;
    display_login_menu();
    printf("请输入选择：");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            if(login_admin_system())
            {
                admin_menu_loop();
            }
            break;
        case 2:
            if(login_user_system())
            {
                passenger_menu_loop();
            }
            break;
        case 0:
            return;
        default:
            printf("无效选择，请重新输入\n");
    }
}       
//处理注册
void handle_registration(void)
{
    int choice;
    display_registration_menu();
    printf("请输入选择");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            register_new_user();
            break;
        case 0:
            return;
        default:
            printf("无效选择，请重新输入\n");
    }
}
//显示主材单
void display_main_menu(void)
{
    printf("\n==========================\n");
    printf("          航班管理系统\n");
    printf("1.登录\n");
    printf("2.注册\n");
    printf("3.浏览航班\n");
    printf("0.退出\n");
    printf("==========================\n");
}
void display_login_menu(void)
{
    printf("\n==========================\n");
    printf("          登录系统\n");
    printf("1.管理员登录\n");
    printf("2.用户登录\n");
    printf("0.返回\n");
    printf("==========================\n");
}
void display_registration_menu(void)
{
    printf("\n==========================\n");
    printf("            注册菜单\n");
    printf("1.乘客注册\n");
    printf("0.返回\n");
    printf("==========================\n");
}
//显示管理员菜单
void diaplay_admin_menu()
{
    printf("\n==========================\n");
    printf("          管理员菜单\n");
    printf("1.添加航班\n");
    printf("2.删除航班\n");
    printf("3.编辑航班信息\n");
    printf("4.查看所有航班\n");
    printf("5.查看所有用户\n");
    printf("6.编辑用户信息\n");
    printf("7.查看预订统计\n");
    printf("0,退出\n");
    printf("==========================\n");
}
void display_passenger_menu()
{
    printf("\n==========================\n");
    printf("          乘客菜单\n");
    printf("1.查看航班\n");
    printf("2.预订航班\n");
    printf("3.取消预订\n");
    printf("4.查看预订\n");
    printf("5.修改个人信息\n");
    printf("0.退出\n");
    printf("==========================\n");
}