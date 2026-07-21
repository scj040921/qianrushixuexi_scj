#include <stdio.h>
#include <stdint.h>

int main(void)
{
    int64_t a[4] = {1, 2, 3, 4};//int64_t八个字节
    int64_t *p1=(int64_t *)(&a+1);//&a指向整个数组的地址
    int64_t *p2=(int64_t *)((int64_t)a+1);
 //a[i]==*(a+i)
    printf("%llx\n", p1[-1]);//4
    printf("%llx\n", *p2);
    
    return 0;
}