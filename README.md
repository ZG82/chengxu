一、项目简介
	该项目为五子棋小游戏的实现。
	但是目前还未完全实现，只有一个雏形。

	***第三方库：EasyX

二、主要功能说明
	目前主要是窗口的构建，简单的页面跳转，没有具体功能。

	***注意：运行之后控制板没有自主推出，存在bug，需要手动退出。(已修复)

三、项目目录结构解释
	1、assets里存放了棋盘图片。
	2、Easyx本来打算可以从本文件里引用easyx，使得其他电脑没有EasyX库也可以运行，但是从github的十一次测试后发现无法实现，但是暂时保留到这里，便于后续调整。
	3、chengxu.slnx是vs写出来的一个文件，
	其中头文件包括Button（实现按钮类的封装，其中主要使用的外部接口为drawButton（），用于绘制按钮，其他成员函数为辅助）
	还有Initialization，初始化初始窗口，单独写出来目的为后续可能可以开发五子棋，贪吃蛇等等游戏集合，用类封装可以有多个对象，同时可以通过继承对于不同游戏具体化。
	对于Mouse，作用为main调用控制游戏进程，各个功能实现的联系，while循环使得页面按钮等可以具体一点，每个都可以不同，没有对应的cpp，比较粗糙的写了个这么个东西。
	Page为页面，类似于Initialization，我认为页面区别较大（我的程序比较简单，所以基本一样），不同类便于实现这样的需求。
	4.cpp为具体的函数实现。

四、构建方式与运行方式
	chengxu/
	├── CMakeLists.txt
	├── src/
	│   ├── Head/
	│   │   ├── Button.h
	│   │   ├── Initialization.h
	│   │   ├── Mouse.h
	│   │   └── Page.h
	│   ├── SourceFile/
	│   │   ├── Buttons/
	│   │   │   └── Button.cpp
	│   │   ├── Pages/
	│   │   │   ├── Page_game.cpp
	│   │   │   ├── Page_menu.cpp
	│   │   │   ├── Page_save.cpp
	│   │   │   └── Page_setting.cpp
	│   │   ├── Initialization.cpp
	│   │   └── main.cpp
	├── build/
	└── README.md

五、其他
	存档文件存入数据，但是时间不足，不能实现，其他同理，之前这个任务一直拖着，最后才做，后续会进一步完善这个程序，这个程序也是我的课程设计。