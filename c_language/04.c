#include <stdio.h>
void  getString(char  **p)
{
    *p = "hello world";
}

int main(void)
{
    char *str = NULL;
    getString(&str);
    printf("%s\n",  str);
}