#ifndef FLIGHT_H
#define FLIGHT_H
#include "list.h"
typedef struct flight
{
    char id[20];//航班ID
    char airline[50];//航空公司
    char departure[50];//出发地
    char destination[50];//目的地
    char departure_time[20];//出发时间
    char arrival_time[20];//到达时间
    int capacity;//容量
    int available_seats;//可用座位数
    float price;//价格
    list_head list;
}flight;
typedef struct bookingrecord
{
    char user_id[20];//用户id
    char flight_id[20];//航班id
    char flight_info[200];//航班信息
    char booking_date[20];//预定日期
    int status;//状态
    list_head list;
}bookingrecord;
void add_flight(list_head *flight_list,const char *id,const char *airline,const char *departure,const char *destination,const char *departure_time,const char *arrival_time,int capacity,float price);
void remove_flight(list_head *flight_list,const char *id);
void display_flights(list_head *flight_list);
flight *find_flight(list_head *flight_list,const char *id);
void update_flight_seats(flight *flight,int seats);
#endif