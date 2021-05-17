

/*
 * Date:2021-05-17 20:40
 * filename:04_msgrcv.cpp
 *
 */

/*
 * msgrcv系统调用从消息队列中获取消息
 *
 */
#include <sys/msg.h>
int msgrcv(int msqid,void* msg_ptr,size_t msg_sz,long int msgtype,int msgflg);

/*
 * msqid参数是由msgget调用返回的消息队列标识符
 * msg_ptr用于存储接收的消息
 * msg_sz参数指的是消息数据部分的长度
 * msgtype参数指定接收何种类型的消息
 * msgtype = 0,读取消息队列中的第一个消息
 * msgtype > 0,读取消息队列中第一个类型为msgtype的消息
 * msgtype < 0,读取消息队列中第一个类型值比msgtype的绝对值小的消息
 *
 * msgrcv成功时返回0,失败时返回-1并设置errno.msgrcv成功时将修改内核数据结构msqid_ds的部分字段
 * 将msg_qnum - 1
 * 将msg_lrpid设置为调用进程的pid
 * 将msg_rtime设置为当前的时间
 */
