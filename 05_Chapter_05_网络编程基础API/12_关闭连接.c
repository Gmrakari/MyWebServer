
#include <unistd.h>
int close(int fd);


//如果无论如何都要立即终止连接（而不是将socker的引用计数减1），可以使用shutdown
//

#include <sys/socket.h>
int shutdown(int sockfd,int howto);
//sockfd参数是待关闭的socket。howto参数决定了shutdown行为
