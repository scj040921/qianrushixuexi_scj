#include "myhead.h"
#include "cJSON.h"

/*
	发送post请求获取天气预报
	   1.公司：杭州快证签科技有限公司
	   2.需要注意的问题
	       问题1：完整的网址  https://kzqtqyb.market.alicloudapi.com/api/weather/one/forty
		          完整的网址分成三个部分：
				          https://  协议头
						  kzqtqyb.market.alicloudapi.com  网址
						  /api/weather/one/forty  路径名
		          写代码：去掉https://，去掉.com后面的内容
		   
	     
*/
int main()
{
	int ret;//用于保存函数返回值
	int tcpsock;
	char rbuf[50000]={0};
	
	//定义ipv4地址结构体变量，存放需要绑定的ip地址和端口号
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;  //ipv4地址协议
	bindaddr.sin_addr.s_addr=htonl(INADDR_ANY); //自动匹配本地主机的ip地址把数据转换成网络需要的格式。
	bindaddr.sin_port=htons(10086); //程序员自己指定端口号，不要使用1024以内的端口号
	
	//获取天气预报服务器ip地址
	//写代码：去掉https://，去掉.com后面的内容
	struct hostent *urlmsg=gethostbyname("kzqtqyb.market.alicloudapi.com");
	//获取ip地址
	//第一步：二级指针解引用，变成char *
	char *ippoint=*(urlmsg->h_addr_list);
	//第二步：把char*强制转换成struct in_addr*
	struct in_addr *otherip=(struct in_addr *)ippoint;
	//第三步：把转换后的当成参数传递
	char *trueip=inet_ntoa(*otherip);
	
	
	//定义ipv4地址结构体变量，存放服务器的ip和端口号
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;  //ipv4地址协议
	serveraddr.sin_addr.s_addr=inet_addr(trueip); //天气预报服务器的ip地址
	serveraddr.sin_port=htons(80); //服务器的端口号,http端口号固定是80
	
	//创建tcp套接字
	tcpsock=socket(AF_INET,SOCK_STREAM,0);
	if(tcpsock==-1)
	{
		perror("创建tcp套接字失败了\n");
		return -1;
	}
	
	//设置取消端口号绑定的限制
	int on=1; //类似于开关，非零表示开启对应的功能
	setsockopt(tcpsock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	
	//绑定ip和端口号
	ret=bind(tcpsock,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
	if(ret==-1)
	{
		perror("绑定ip和端口号失败了\n");
		return -1;
	}
	
	//连接天气预报服务器
	ret=connect(tcpsock,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret==-1)
	{
		perror("连接服务器失败了\n");
		return -1;
	}
	
	//发送post请求获取天气预报
	/*
		重点关注：post请求书写格式
		Content-Type:application/x-www-form-urlencoded
		    指定post请求内容格式：form表示表单格式
			表单格式的含义：
			      adcode=440117000000
			      
	*/
	char *postreq="POST /api/weather/one/forty HTTP/1.1\r\n"
				  "Host:kzqtqyb.market.alicloudapi.com\r\n"
				  "Content-Type:application/x-www-form-urlencoded\r\n"
				  //19表示body字段实际长度
				  "Content-Length:19\r\n"  
				  "Authorization: APPCODE 170f18df3d154bf19bc305538d3ffb3c\r\n\r\n"
				  "adcode=440117000000";  //body字段中的内容
	
	//发送这个请求
	send(tcpsock,postreq,strlen(postreq),0);
	
	//接收天气预报服务器回复的应答信息
	recv(tcpsock,rbuf,50000,0);
	//printf("杭州快证签科技有限公司反馈给我信息是: %s\n",rbuf);
	char *json=strchr(rbuf,'{'); //找到第一个{的位置
	if(json==NULL)
	{
		printf("没有找到json数据\n");
		close(tcpsock);
		return -1;
	}
	printf("\n找到的JSON开始位置：\n%s\n", json);

	cJSON *root=cJSON_Parse(json);//得到JSON树的根节点
	if(root==NULL)
	{
		printf("json数据解析失败\n");
		printf("错误位置：%s\n", cJSON_GetErrorPtr());
		close(tcpsock);
		return -1;
	}
	printf("json数据解析成功\n");
	cJSON *msg=cJSON_GetObjectItem(root,"msg");
	if(msg!=NULL)
	{
		printf("msg=%s\n",msg->valuestring);
	}
	cJSON *code=cJSON_GetObjectItem(root,"code");
	if(code!=NULL)
	{
		printf("code=%d\n",code->valueint);
	}
	cJSON *data1=cJSON_GetObjectItem(root,"data");
	cJSON *data2=cJSON_GetObjectItem(data1,"data");
	cJSON *city=cJSON_GetObjectItem(data2,"city");
	if(city!=NULL)
	{
		printf("城市：%s\n",city->valuestring);
	}
	cJSON *weather_array=cJSON_GetObjectItem(data2,"data");
	int count=cJSON_GetArraySize(weather_array);
	printf("天气预报共有%d天\n",count);
	for(int i=0;i<count;i++)
	{
		cJSON *day=cJSON_GetArrayItem(weather_array,i);
		cJSON *date=cJSON_GetObjectItem(day,"date");
		cJSON *week=cJSON_GetObjectItem(day,"week");
		cJSON *wea=cJSON_GetObjectItem(day,"wea");
		cJSON *tem1=cJSON_GetObjectItem(day,"tem1");
		cJSON *tem2=cJSON_GetObjectItem(day,"tem2");
		printf("日期：%s\n",date->valuestring);
		printf("星期：%s\n",week->valuestring);
		printf("天气：%s\n",wea->valuestring);
		printf("最高温度：%s\n",tem1->valuestring);
		printf("最低温度：%s\n",tem2->valuestring);

	}
	cJSON_Delete(root);


	//关闭套接字
	close(tcpsock);
	return 0;
}