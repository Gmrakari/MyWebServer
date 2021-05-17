

/*
 * Date:2021-05-17 20:46
 * filename:05_msgctl.cpp
 *
 */

/*
 * 控制消息队列的某些属性
 */

#include <sys/msg.h>
int msgctl(int msqid,int command,struct msqid_ds* buf);
/*
 * msqid参数是由msgget调用返回的共享内存标识符
 * command指定要执行的命令
 * msgctl支持的命令:
 * IPC_STAT
 * IPC_SET
 * IPC_RMID
 * IPC_INFO
 * MSG_INFO
 * MSG_STAT
 */
