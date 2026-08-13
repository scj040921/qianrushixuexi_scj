#ifndef LIST_H
#define LIST_H

typedef struct list_head
{
    struct list_head *next;
    struct list_head *prev;
}list_head;
#define INIT_LIST_HEAD(ptr)do {\
(ptr)->next=(ptr);(ptr)->prev=(ptr);\
}while(0)
#define list_add(new,head)do {\
    (new)->next=(head)->next;\
    (new)->prev=(head);\
    (head)->next->prev=(new);\
    (head)->next=(new);\
}while(0)
#define list_del(entry)do {\
    (entry)->next->prev=(entry)->prev;\
    (entry)->prev->next=(entry)->next;\
}while(0)
#define container_of(ptr,type,member) ((type*)((char*)(ptr)-(size_t)&((type*)0)->member))

#define list_for_each_entry(pos,head,member)\
    for(pos=container_of((head)->next,typeof(*pos),member);\
    &pos->member!=(head);\
    pos=container_of(pos->member.next,typeof(*pos),member))

#define list_for_each_entry_safe(pos,n,head,member)\
    for(pos=container_of((head)->next,typeof(*pos),member)),\
    n=container_of(pos->member.next,typeof(*pos),member);\
    &pos->member!=(head);\
    pos=n,n=container_of(n->member.next,typeof(*pos),member)
list_head *init_list(void);
void add_node(list_head *head,list_head *new_node);
void remove_node(list_head *node);
#endif