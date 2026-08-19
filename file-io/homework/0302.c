#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#define MAX_LINE 255

#define cyan(string)\
do{\
    char s[MAX_LINE];\
    readlink(string,s,MAXLINE);\
    printf("\033[1;36m%-4s->%s\033[m\n",string,s);\
}while(0);