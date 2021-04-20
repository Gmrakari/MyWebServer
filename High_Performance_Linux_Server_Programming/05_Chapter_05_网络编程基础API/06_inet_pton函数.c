#include <arpa/inet.h>

int inet_pton(int af,const char* src,void* dst);

const char* inet_ntop(int af,const void* src,char* dst,socklen_t cnt);

/*
----------------------------------------------------------------------
*/

#include <netinet/in.h>

#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46


