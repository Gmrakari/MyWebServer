#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <strings.h>
#include <arpa/inet.h>
int getsockopt(int sockfd,int level,int option_name,void* option_value,socklen_t* restrict option_len );

int setsockopt(int sockfd,int level,int option_name,const void* option_value,socklen_t option_len);

//重要的socket选项有SO_REUSEADDR、SO_RECVBUF、SO_SNDBUF、SO-REVLOWAT、SO_SNDLOWAT、SO_LINGER


int sock = socket(PF_INET,SOCK_STREAM,0);
assert(sock >= 0);
int reuse = 1;
setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
//经过setsocketopt的设置之后，即使sock处于TIME_WAIT状态，与之绑定的socket地址也可以立即被重用

struct sockaddr_in address;
bzero(&address,sizeof(address));
address.sin_family = AF_INET;
inet_pton(AF_INET,ip,&address.sin_addr);
address.sin_port = htons(port);

int ret = bind(sock,(struct sockaddr *)&address,sizeof(address));


