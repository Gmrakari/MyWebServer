
SO_RCVLOWAT和SO_SNDLOWAT选项分别表示TCP结婚搜缓冲区和发送缓冲区的低水位标记

他们一般被I/O服用系统调用 用来判断socket是否可读或可写。

当TCP接收缓冲区中可读数据的总数大于其低水位标记时，I/O复用系统调用将通知应用程序可以从对应的socket上读取数据

当TCP发送缓冲区中的空闲空间(可以写入数据的空间)大于其低水位标记时，I/O复用系统调用将通知应用程序可以往对应的socket上写入数据


