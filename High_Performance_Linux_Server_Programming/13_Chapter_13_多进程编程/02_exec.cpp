

/*
 * Date:2021-05-06 20:18
 * filename:02_exec.cpp
 *
 */

/*
 * 在子进程中执行其他程序，即替换当前进程映像
 */

#include <unistd.h>
#include <iostream>
#include <cstdio>
using namespace std;
//extern char** environ;

int execl(const char* path,const char* arg,...);
int execlp(const char* file,const char* arg,...);
//int execle(const char* path,const char* arg,...,char* const envp[]);
int execle( char *pathname,char *arg0,char *arg1,char *argn,char *envp[]);
//int execv(const char* path,char* const argv[]);
int execvp(const char* file,char* const argv[]);
int execve(const char* path,char* const argv[],char* const envp[]);

/*
 *
path可执行文件的完整路径
file接收文件名，该文件的具体欸之则在环境变量PATH中搜寻
arg接受可变参数,atgv则接受参数数组
envp参数用于设置新程序的环境变量。如果未设置它，则新程序将使用由全局变量environ指定的环境变量

一般情况下,exec调用之后的代码都不会执行，因为此时原程序已经被exec的参数指定的程序完全替换(包括代码和数据)

exec函数不会关闭原程序打开的文件描述符，除非该文件描述符被设置了类似SOCK_CLOEXEC的属性
*/


int main()
{
	execl("/bin/ls","ls","-al","/etc/passwd",(char*)0);
	printf("\n");
	execlp("ls","ls","-al","/etc/passwd",(char *)0);

	printf("execv\n");
	//char* argv[] = {"ls","-al","/etc/passwd"};
	char* argv[5]={"ls","-l","/",NULL};
	execv("/bin/ls",argv);

}
