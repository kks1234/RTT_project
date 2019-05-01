# RTT_project

## 简介

RT-Thread包含了一个自有的、传统的硬实时内核：可抢占的多任务实时调度器，信号量，互斥量，邮箱，消息队列，信号等。当然，它和传统的实时操作系统还存在着三种不同：

- 设备驱动框架；
- 软件组件；
- 应用模块

设备驱动框架更类似一套驱动框架，涉及到UART，IIC，SPI，SDIO，USB从设备/主设备，EMAC，NAND闪存设备等。它会把这些设备驱动中的共性抽象/抽取出来，而驱动工程师只需要按照固定的模式实现少量的底层硬件操作及板级配置。通过这样的方式，让一个硬件外设更容易地对接到RT-Thread系统中，并获得RT-Thread平台上的完整软件栈功能。

软件组件是位于RT-Thread内核上的软件单元，例如命令行（finsh/msh shell），虚拟文件系统（FAT，YAFFS，UFFS，ROM/RAM文件系统等），TCP/IP网络协议栈（lwIP），Libc/POSIX标准层等。一般的，一个软件组件放置于一个目录下，例如RT-Thread/components目录下的文件夹，并且每个软件组件通过一个 SConscript文件来描述并被添加到RT-Thread的构建系统中。当系统配置中开启了这一软件组件时，这个组件将被编译并链接到最终的RT-Thread固件中。

注：随着RT-Thread 3.0中的包管理器开启，越来越多的软件组件将以package方式出现在RT-Thread平台中。而RT-Thread平台更多的是指：

- RT-Thread内核；
- shell命令行；
- 虚拟文件系统；
- TCP/IP网络协议栈；
- 设备驱动框架；
- Libc/POSIX标准层。

更多的IoT软件包则以package方式被添加到RT-Thread系统中。