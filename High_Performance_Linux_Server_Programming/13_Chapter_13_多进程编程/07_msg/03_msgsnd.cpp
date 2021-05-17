

/*
 * Date:2021-05-17 20:33
 * filename:03_msgsnd.cpp
 *
 */

/*
 * 把一条消息添加到消息队列中
 */

#include <sys/msg.h>
int msgsnd(int msqid,const void* msg_ptr,size_t msg_sz,int msgflg);

/*
 * msqid 参数由msgget调用返回的消息队列标识符
 * msg_ptr参数指向一个准备发送的消息,消息必须被定义如下:
 */
struct msgbuf
{
	long mtype;			//消息类型
	char mtext[512];	//消息数据
};

/*
 * mtype 成员指定消息的类型，它必须是一个正整数
 * mtext是消息数据
 * msg_sz参数是消息的数据部分(mtext)的长度,这个长度可以为0,表示没有消息数据
 */

/*
 * msgflg控制msgsnd的行为,它通常仅支持IPC_NOWAIT标志,即以非阻塞的方式发送消息.
 * 默认情况下，发送消息时如果消息队列满了，则msgsnd将阻塞,若IPC_NOWAIT标志被指定,则msgsnd调用可能被如下两种异常情况所中断
 * 消息队列被移除
 * 程序接收到信号
 */
