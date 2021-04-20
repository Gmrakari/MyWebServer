#include <sys/un.h>
struct sockaddr_un{
	sa_family_t sin_family;
	char sun_path[108];
};

struct sockaddr_in{
	sa_family_t sin_family;
	u_int16_t sin_port;
	struct in_addr sin_addr;
};

struct in_addr{
	u_int32_t s_addr;
};

struct sockaddr_int6{
	sa_family_t sin6_family;
	u_int16_t sin6_port;
	u_int32_t sin6_flowinfo;
	struct in6_addr sin6_addr;
	u_int32_t sin6_scope_id;
};

struct in6_addr{
	unsigned char sa_addr[16];
};


