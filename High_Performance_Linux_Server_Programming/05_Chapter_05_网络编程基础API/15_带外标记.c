#include <sys/socket.h>

int sockatmark(int sockfd);

//判断sockfd是否处于带外标记，即下一个被读取到的数据是否带外数据。
//如果是 sockatmark返回1 此时我们就可以利用带MSG_OOB标志的recv调用来接收带外数据。如果不是，则sockatmark返回0


