struct student{
    int id;
    char name[20];
    int age;
};
#define DATATYPE struct student
#include "list.h"
void assignment(int *p,int n)
{

}
void show_list(struct student n)
{
    printf("姓名：%s,年龄：%d\n",n.name,n.age);
}
int main()
{
    linklist head=init_list();
    struct student Jack={1001,"Jack",18};
    struct student Mary={1002,"Mary",19};
    list_add_tail(head,new_node(Jack,NULL));
    list_add_tail(head,new_node(Mary,NULL));
    list_traverse(head,show_list);
    printf("\n");
    return 0;
}