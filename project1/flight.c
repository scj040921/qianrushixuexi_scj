#include "flight.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void add_flight(list_head *flight_list,const char *id,const char *airline,const char *departure,const char *destination,const char *departure_time,const char *arrival_time,int capacity,float price)
{
    flight *flight=malloc(sizeof(flight));
    if(flight)
    {
        strcpy(flight->id,id);
        strcpy(flight->airline,airline);
        strcpy(flight->departure,departure);
        strcpy(flight->destination,destination);
        strcpy(flight->departure_time,departure_time);
        strcpy(flight->arrival_time,arrival_time);
        flight->capacity=capacity;
        flight->available_seats=capacity;
        flight->price=price;
        INIT_LIST_HEAD(&flight->list);
        add_node(&flight->list,flight_list);
        printf("航班添加成功\n");
    }
}
void remove_flight(list_head *flight_list,const char *id)
{
    flight *flight;
    list_for_each_entry(flight,flight_list,list)
    {
        if(strcmp(flight->id,id)==0)
        {
            list_del(&flight->list);
            free(flight);
            printf("航班%s删除成功\n",id);
            return;
        }
    }
    printf("航班%s不存在\n",id);
}
void display_flights(list_head *flight_list)
{
    flight *flight;
    list_for_each_entry(flight,flight_list,list)
    {
        printf("\n航班列表:\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("航班ID | 航空公司 | 出发地 | 目的地 | 出发时间 | 到达时间 | 容量 | 可用座位 | 价格\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    list_for_each_entry(flight, flight_list, list) {
        printf("%s | %s | %s | %s | %s | %s | %d | %d | %.2f\n",
               flight->id, flight->airline, flight->departure, flight->destination,
               flight->departure_time, flight->arrival_time, flight->capacity,
               flight->available_seats, flight->price);
    }
    printf("---------------------------------------------------------------------------------------------------\n");
    }
}
flight *find_flight(list_head *flight_list,const char *id)
{
    flight *flight;
    list_for_each_entry(flight,flight_list,list)
    {
        if(strcmp(flight->id,id)==0)
        {
            return flight;
        }
    }
    return NULL;
}
void update_flight(flight *flight,int seats)
{
    if(flight)
    {
        flight->available_seats+=seats;
        if(flight->available_seats<0)
        {
            flight->available_seats=0;
        }
        if(flight->available_seats>flight->capacity)
        {
            flight->available_seats=flight->capacity;
        }
    }
}