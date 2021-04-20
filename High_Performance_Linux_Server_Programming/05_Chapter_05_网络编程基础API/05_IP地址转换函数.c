#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

in_addr_t inet_addr(const char* strptr);
//将用点分十进制字符串表示的IPv4地址转化为用网络字节序整数表示的IPv4地址

int inet_aton(const char* cp,struct in_addr* inp);
//与inet_addr函数完成同样的功能，但是将转化结果存储于参数inp指向的地址结构中。成功1 失败返回0

char* inet_ntoa(struct in_addr in);
//将用网络字节序整数表示的IPv4地址转化为用点分十进制字符串表示的IPv4地址


int main(){
		struct in_addr in;
	
	char* szValue1 = inet_ntoa("1.2.4.5");
	char* szValue2 = inet_ntoa("10.194.71.60");

	printf("address 1:%s\n",szValue1);
	printf("address 2:%s\n",szValue2);

}




