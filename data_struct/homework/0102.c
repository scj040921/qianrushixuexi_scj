#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    struct node* next;
    int data;
}node;
node *list_cinit(void)
{
    node *head=malloc(sizeof(node));
    if(head!=NULL)
    {
        head->next=head;
    }
    return head;
}
// void del_list(node *list,int n)
// {
//     if(n<=0||list==NULL)
//     {
//         return;
//     }
//     for(int i=0;i<n-1;i++)
//     {
//         list=list->next;
//     }
//     node *temp;
//     temp=list->next;
//     list->next=temp->next;
//     free(temp);
// }
node *new_node(int data)
{
    node *newNode=malloc(sizeof(node));
    if(newNode!=NULL)
    {
        newNode->data=data;
        newNode->next=NULL;
    }
    return newNode;
}
void add_node(node *list,node *num)
{
    if(list==NULL||num==NULL)
    {
        return;
    }
    num->next=list->next;
    list->next=num;
    
}
int main()
{
     node *mylist=list_cinit();
    int a[]={13,12,11,10,9,8,7,6,5,4,3,2,1};
    for(int i=0;i<13;i++)
    {
        add_node(mylist,new_node(a[i]));
    }
    node *prev=mylist;
    node *cur=mylist->next;
    int count=1;
   while(mylist->next->next->next!=mylist)
   {
    if(cur==mylist)
    {
        prev=cur;
        cur=cur->next;
        continue;
    }
    if(count==3)
    {
        prev->next=cur->next;
        free(cur);
        cur=prev->next;
        count=1;
    }else{
        prev=cur;
        cur=cur->next;
        count++;
    }
   }
    printf("Survivors: %d and %d\n", mylist->next->data, mylist->next->next->data);

    free(mylist->next->next);
    free(mylist->next);
    free(mylist);

    return 0;
}