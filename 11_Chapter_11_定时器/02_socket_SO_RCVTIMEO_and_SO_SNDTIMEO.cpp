
socket选项SO_RCVTIMEO和SO_SNDTIMEO,它们分别用来设置socket接收数据超时时间和发送数据超时时间

这两个选项仅对与数据接收和发送相关的socket专用系统调用有效
包括send,sendmsg,recv,recvmsg,accept和connect

send	SO_SNDTIMEO 	返回-1,设置errno为EAGAIN或EWOULDBLOCK
sendmsg SO_SNDTIMEO 	返回-1,设置errno为EAGAIN或EWOULDBLOCK

recv 	SO_RCVTIMEO 	返回-1,设置errno为EAGAIN或EWOULDBLOCK
recvmsg SO_RCVTIMEO 	返回-1,设置errno为EAGAIN或EWOULDBLOCK

accept 	SO_RCVTIMEO 	返回-1,设置errno为EAGAIN或EWOULDBLOCK
connect SO_SNDTIMEO 	返回-1,设置errno为 EINPROGRESS



