#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include"kernel_list.h"

struct student
{
    int age;
    char name[10];
    float score;
    struct list_head list;
};
struct student *init_list(void)
{
    struct student *head=malloc(sizeof(struct student));
    if(head!=NULL)
    {
        INIT_LIST_HEAD(&head->list);
    }
    return head;
}
struct student *show_list(struct student *head)
{
    struct list_head *pos;
    list_for_each_prev(pos,&head->list)
    {
        struct student *p=list_entry(pos,struct student,list);
        printf("年龄：%d\t姓名：%s\t成绩：%.2f\n",p->age,p->name,p->score);
    }
}
int main()
{
    struct student *head=init_list();
    struct student *Jack = malloc(sizeof(struct student));
    Jack->age = 18;
    strcpy(Jack->name, "Jack");
    Jack->score = 90.0;
    list_add_tail(&Jack->list, &head->list);

    struct student *Rose = malloc(sizeof(struct student));
    Rose->age = 18;
    strcpy(Rose->name, "Rose");
    Rose->score = 80.0;
    list_add_tail(&Rose->list, &head->list);

    struct student *Mike = malloc(sizeof(struct student));
    Mike->age = 18;
    strcpy(Mike->name, "Mike");
    Mike->score = 70.0;
    list_add_tail(&Mike->list, &head->list);
    show_list(head);
    list_del(&Rose->list);
    show_list(head);
    struct list_head *pos,*n;
    list_for_each_safe(pos,n,&head->list)
    {
        list_del(pos);
        free(list_entry(pos,struct student,list));
    }
    free(head);
    return 0;
}