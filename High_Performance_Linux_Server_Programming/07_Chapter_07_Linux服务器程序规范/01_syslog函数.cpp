
#include <syslog.h>
void syslog(int priority,const char* message,...);

//该函数采用可变参数(第二个参数message 和 第三个参数...)来结构化输出
//
//priority参数是所谓的设施值与日志级别的按位或

//日志级别

#define LOG_MERGE	0 /* 系统不可用 */
#define LOG_ALERT 	1 /* 报警，需要立即采取行动 */
#define LOG_CRIT 	2 /* 非常严重的情况 */
#define LOG_ERR 	3 /* 错误 */
#define LOG_WRANING 4 /* 警告 */
#define LOG_NOTICE  5 /* 通知 */
#define LOG_INFO 	6 /* 信息 */
#define LOG_DEBUG 	7 /* 调试 */

void openlog( const char* ident,int logopt,int facility )
{
	//ident参数指定的字符串将被添加到日志消息的日期和时间之后，他通常被设置为程序的名字
}

	//logopt参数对后续syslog调用的行为进行配置，它可取下列值得按位或
#define LOG_PID 	0x01 /* 在日志消息中包含程序PID */
#define LOG_CONS	0x02 /* 如果消息不能记录到日志文件，则打印至终端 */
#define LOG_ODELAY  0x04 /* 延迟打开日志功能直到第一次调用syslog */
#define LOG_NDELAY  0x08 /* 不延迟打开日志功能 */

//facility 参数可用来修改syslog函数中的默认设施值

//设置日志掩码，使日志级别大于日志掩码的日志信息被系统忽略
//用于设置syslog的日志掩码
int setlogmask(int maskpri);

//maskpri参数指定日志掩码值，该函数始终会成功，它返回调用进程先前的日志掩码值

//关闭日志功能
void closelog();









