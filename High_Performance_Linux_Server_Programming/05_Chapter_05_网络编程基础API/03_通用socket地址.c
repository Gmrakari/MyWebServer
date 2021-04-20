#include <bits/socket.h>

struct sockaddr{
	sa_family_t sa_family;
	char sa_data[14];
}


#include <bits/socket.h>

struct sockaddr{
	sa_family_t sa_family;
	unsigned long int __ss_align;
	char __ss_padding[128-sizeof(__ss_align)];
}


