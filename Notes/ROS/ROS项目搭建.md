    WorkSpace --- 自定义的工作空间
    
        |--- build:编译空间，用于存放CMake和catkin的缓存信息、配置信息和其他中间文件。
    
        |--- devel:开发空间，用于存放编译后生成的目标文件，包括头文件、动态&静态链接库、可执行文件等。
    
        |--- src: 源码
    
            |-- package：功能包(ROS基本单元)包含多个节点、库与配置文件，包名所有字母小写，只能由字母、数字与下划线组成
    
                |-- CMakeLists.txt 配置编译规则，比如源文件、依赖项、目标文件
    
                |-- package.xml 包信息，比如:包名、版本、作者、依赖项...(以前版本是 manifest.xml)
    
                |-- scripts 存储python文件和sh脚本文件
    
                |-- src 存储C++源文件
    
                |-- include 头文件
    
                |-- msg 消息通信格式文件
    
                |-- srv 服务通信格式文件
    
                |-- action 动作格式文件
    
                |-- launch 可一次性运行多个节点 
    
                |-- config 配置信息
    
            |-- CMakeLists.txt: 编译的基本配置



**vscode执行大致流程：**

##### 1. 创建 ROS 工作空间

```
mkdir -p xxx_ws/src
cd xxx_ws
catkin_make
```

##### 2. 启动 vscode

进入 xxx_ws 启动 vscode

```
cd xxx_ws
code .
```

##### 3. vscode 中编译 ros

快捷键 ctrl + shift + B 调用编译，选择:`catkin_make:build`

可以点击配置设置为默认，修改.vscode/tasks.json 文件

##### 4. 创建 ROS 功能包

选定 src 右击 ---> create catkin package

**设置包名 添加依赖**

##### 5. C++ 实现

**在功能包的 src 下新建 cpp 文件**

**PS1: 如果没有代码提示**

修改 .vscode/c_cpp_properties.json

设置 "cppStandard": "c++17"

**PS2: main 函数的参数不可以被 const 修饰**

**PS3: 当ROS__INFO 终端输出有中文时，会出现乱码**

解决办法：在函数开头加入下面的代码

```cpp
setlocale(LC_ALL, "");
```

**6. 配置CMakeists.txt**

```
add_executable(节点名称 src/C++源文件名.cpp)
target_link_libraries(节点名称
  ${catkin_LIBRARIES}
)
```

**7. 编译执行**

编译: ctrl + shift + B

执行: 

**先启动命令行1：**

```
roscore
```

**再启动命令行2：**

```shell
cd 工作空间
source ./devel/setup.bash
rosrun 包名 C++节点
```

**PS:**`source ~/工作空间/devel/setup.bash`可以添加进`.bashrc`文件，使用上更方便

添加方式1: 直接使用 gedit 或 vim 编辑 .bashrc 文件，最后添加该内容

添加方式2:`echo "source ~/工作空间/devel/setup.bash" >> ~/.bashrc`



**launch文件：**

**1. 实现**

1. 选定功能包右击 ---> 添加 launch 文件夹

2. 选定 launch 文件夹右击 ---> 添加 launch 文件

3. 编辑 launch 文件内容

   ```
   <launch>
       <node pkg="helloworld" type="demo_hello" name="hello" output="screen" />
       <node pkg="turtlesim" type="turtlesim_node" name="t1"/>
       <node pkg="turtlesim" type="turtle_teleop_key" name="key1" />
   </launch>
   ```

- node ---> 包含的某个节点
- pkg -----> 功能包 
- type ----> 被运行的节点文件
- name --> 为节点命名
- output-> 设置日志的输出目标

**2. 运行 launch 文件**

```
roslaunch 包名 launch文件名
```



**计算图**

开始执行节点后，启动新终端，键入：rqt_graph或rosrun_ rqt_graph rqt_graph，可看到网络拓扑图，显示当前系统运行情况和不同节点之间的关系。



### 自定义源文件调用

**需求:**设计头文件与源文件，在可执行文件中包含头文件。

**流程:**

1. 编写头文件；
2. 编写源文件；
3. 编写可执行文件；
4. 编辑配置文件并执行。

------

首先展示一下示例文件结构:

```
.
├── CMakeLists.txt
├── include
│   └── plumbing_head_src
│       └── hello.h
├── package.xml
└── src
    ├── hello.cpp
    └── use_hello.cpp
```

#### 1.头文件

在功能包下的 include/功能包名 目录下新建头文件: hello.h，示例内容如下:

```cpp
#ifndef _HELLO_H
#define _HELLO_H

namespace hello_ns {

class My {

public:
    void run();

};

}

#endif
```

**注意:**

在 VScode 中，为了后续包含头文件时不抛出异常，请配置 .vscode 下 c_cpp_properties.json 的 includepath属性

```
"/home/用户/工作空间/src/功能包/include/**"
```

#### 2.源文件

在 src 目录下新建文件:hello.cpp，示例内容如下:

```cpp
#include "test_head_src/hello.h"
#include "ros/ros.h"

namespace hello_ns{

void My::run(){
    ROS_INFO("hello,head and src ...");
}

}
```

#### 3.可执行文件

在 src 目录下新建文件: use_hello.cpp，示例内容如下:

```cpp
#include "ros/ros.h"
#include "test_head_src/hello.h"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"hello");
    hello_ns::My my;
    my.run();
    return 0;
}
```

#### 4.配置文件

头文件与源文件相关配置:

```makefile
include_directories(
include
  ${catkin_INCLUDE_DIRS}
)

## 声明C++库
add_library(head_src
  include/plumbing_head_src/hello.h
  src/hello.cpp
)

add_dependencies(head_src ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(head_src
  ${catkin_LIBRARIES}
)
```

可执行文件配置:

```makefile
add_executable(use_hello src/use_hello.cpp)

add_dependencies(use_hello ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#此处需要添加之前设置的 head 库
target_link_libraries(use_hello
  head_src
  ${catkin_LIBRARIES}
)
```
