#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

//将目标文件作为第3个参数传递给服务器程序，客户telnet到该服务器上即可获得该文件
//此代码没有为目标文件分配任何用户空间的缓存，也没有执行读取文件的操作，但同样实现了文件的发送，其效率显然要高的多
int main( int argc,char* argv[]){
	if(argc <= 3)
	{
		printf("usage: %s ip_address port_number filename\n",basename(argv[0]));
		return 1;
	}
	const char* ip = argv[1];
	int port = atoi(argv[2]);
	const char* file_name = argv[3];

	int filefd=  open(file_name,O_RDONLY);
	assert( filefd >  0);
	struct stat stat_buf;
	fstat( filefd,&stat_buf );

	struct sockaddr_in address;
	bzero( &address,sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET,ip,&address.sin_addr );
	address.sin_port = htons( port );

	int sock = socket(PF_INET,SOCK_STREAM,0);
	assert( sock != -1 );

	int ret = bind(sock,(struct sockaddr*)&address,sizeof( address ));
	assert( ret != -1 );

	struct sockaddr_in client;
	socklen_t client_addrlength = sizeof(client);
	int connfd = accept(sock,(struct sockaddr*)&client,&client_addrlength);
	if( connfd < 0 )
	{
		printf("errno is : %d\n",errno);
	}
	else
	{
		sendfile(connfd,filefd,NULL,stat_buf.st_size);
		close(connfd);
	}

	close( sock );
	return 0;
}
