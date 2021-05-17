

/*
 * Date:2021-05-17 20:25
 * filename:02_msgget.cpp
 *
 */

/*
 * 创建一个消息队列 或者 获取一个已有的消息队列 
 */

#include <sys/msg.h>
int msgget(key_t key,int msgflg);
/*
 * 和semget系统调用一样，key参数是一个键值，用来标识一个全局唯一的消息队列
 * msgflg成功时返回一个正整数值,它时消息队列的标识符,msgget失败时返回-1,并设置errno
 *
 * 如果msgget用于创建消息队列,则与之关联的内核数据结构msqid_ds将被创建并初始化
 */

struct msqid_ds
{
	struct ipc_perm msg_perm;			//msg_permission 消息队列的操作权限
	time_t msg_stime;					//最后一次调用msgsnd的时间
	time_t msg_rtime;					//最后一次调用msgrcv的时间
	time_t msg_ctime;					//最后一次被修改的时间

	unsigned long __msg_cbytes;			//消息队列中已有的字节数
	msgqnum_t msg_qnum;					//消息队列中已有的消息数
	msglen_t msg_qbytes;				//消息队列允许的最大字节数
	pid_t msg_lspid;					//最后执行msgsnd的进程的pid
	pid_t msg_lrpid;					//最后执行msgrcv的进程的pid
};
