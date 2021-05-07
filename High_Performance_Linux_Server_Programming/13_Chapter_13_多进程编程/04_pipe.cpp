

/*
 * Date:2021-05-07 21:10
 * filename:04_pipe.cpp
 *
 */

/*
 *
管道能在父、子进程间传递数据，利用的是fork调用之后两个管道文件描述符(fd[0] 和fd[1])都保持打开

一对这样的文件描述符只能保证父、子进程间一个方向的数据传输，
父进程和子进程必须有一个关闭fd[0]，另一个关闭fd[1]。

如果要实现父、子进程之间的双向数据传输，就必须使用两个管道
socket编程接口提供了一个创建全双工管道的系统调用:socketpair

*/

