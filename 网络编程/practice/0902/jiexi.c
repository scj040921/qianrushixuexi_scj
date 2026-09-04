#include"myhead.h"
#include"cJSON.h"
int main()
{
    char *jsondata="{\"影片名\":\"疯狂的石头\",\"票价\":29.9,\"上映时间\":\"2026-9-1\",\"主演\":{\"一号男\":\"刘德华\",\"二号男\":\"梁朝伟\",\"一号女\":\"张曼玉\"}}";
    cJSON *obj=cJSON_Parse(jsondata);
    cJSON *val1=cJSON_GetObjectItem(obj,"影片名");
    printf("影片名:%s\n",val1->valuestring);
    cJSON *val2=cJSON_GetObjectItem(obj,"票价");
    printf("票价:%f\n",val2->valuedouble);
    cJSON *val3=cJSON_GetObjectItem(obj,"上映时间");
    printf("上映时间:%s\n",val3->valuestring);
    cJSON *val4=cJSON_GetObjectItem(obj,"主演");
    printf("主演:\n");
    cJSON *val5=cJSON_GetObjectItem(val4,"一号男");
    printf("一号男:%s\n",val5->valuestring);
    cJSON *val6=cJSON_GetObjectItem(val4,"二号男");
    printf("二号男:%s\n",val6->valuestring);
    cJSON *val7=cJSON_GetObjectItem(val4,"一号女");
    printf("一号女:%s\n",val7->valuestring);

}