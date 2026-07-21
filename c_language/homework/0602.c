#include<stdio.h>
 int count()
 {
    static int i=0;
    i++;
    return i;
 }
 int main()
 {
    for(int i=0;i<5;i++)
   {
      printf("%d\n",count());
   }
   return 0;
 }
