//按字节读文件，统计读取次数
// #include <stdio.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// int main(int argc,char *argv[])
// {
//     FILE *fp=fopen(argv[1],"r");
//     long size=0;
//     char ch;
//     while(1)
//     {
//         int n=fread(&ch,1,1,fp);
//         if(n==0&&feof(fp))
//         {
//             printf("文件大小：%ld\n",size);
//             fclose(fp);
//             break;
//         }
//         size++;
//     }
//     return 0;
// }

//使用stat函数直接获取文件大小
// #include <stdio.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include<strings.h>
// int main(int argc,char *argv[])
// {
//     struct stat info;
//     bzero(&info,sizeof(info));
//     stat(argv[1],&info);
//     printf("文件大小：%ld\n",info.st_size);
//     return 0;
// }

//使用lseek/fseek函数定位到文件末尾，然后获取文件位置
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<strings.h>
int main(int argc,char *argv[])
{
    FILE *fp=fopen(argv[1],"r");
    fseek(fp,0L,SEEK_END);
    printf("文件大小：%ld\n",ftell(fp));
    fclose(fp);
    return 0;
}
