# CMake入门学习笔记
> CMake is great. don't waste time on other C++ build tools, seriously.
### 1.  CMake是什么？
`CMake`是一款工程构建工具，类似的工具还有`autotool`，`qmake`，`Scons`等等。

具体见：
[为什么选用cmake](https://www.jianshu.com/p/835f777c9183)

- CMakeLists.txt是使用CMake时唯一需要编写的文件：

```CMake
    cmake_minimum_required(VERSION 2.6)
    project(itest)
    
    # C++标准
    set(CMAKE_CXX_STANDARD 11)
    
    # 指定参与编译的源文件
    add_executable(itest src/main.cpp src/cal/Calculator.cpp src/cal/Calculator.h)
    
    # 指定安装路径，make install 时运用
    install (TARGETS itest DESTINATION bin)
    install(DIRECTORY src/ DESTINATION include/itest FILES_MATCHING PATTERN "*.h")
    
    # 设置不同build类别时的编译参数
    #set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
```
<center><font color=gray>一个示例</font></center>

---
### 2.   CMake怎么用？
> 根据[CMake 入门实战 - Hahack](https://www.hahack.com/codes/cmake/)的实例来学习记录。
>
> 原文C语言Demo源码出自[《CMake入门实战》源码 - wzpan](https://github.com/wzpan/cmake-demo)，本文改写为C++。
- 在`Linux`平台使用`CMake`生成`Makefile`并编译的流程：
1.  编写`CMake`配置文件`CMakeList.txt`
2.  执行命令`cmake ${CMAKELIST_PATH}`生成`Makefile`，`${CMAKELIST_PATH}`是`CMakeList.txt`所在的目录。
3.  执行命令`make`进行编译。

#### 2.1.   单个源文件的例子
##### 2.1.1.    编写CMakeList.txt
以下面的[`Demo_1` - 点击下载代码](https://github.com/BLB0803/Cpp_learning_note/tree/master/Demo_1)的实例来学习程序为例子，项目中的一个源文件`main.cpp`如下：

```cpp
/*
 * power - Calculate the power of number.
 * @param base: Base value.
 * @param exponent: Exponent value.
 *
 * @return base raised to the power exponent.
 */
 
#include <iostream>

using namespace std;

double power(double base, int exponent)
{
    int result = base;
    int i;

    if (exponent == 0) {
        return 1;
    }

    for(i = 1; i < exponent; ++i){
        result = result * base;
    }
    return result;
}
int main(int argc, char *argv[])
{
    if (argc < 3){
        // printf("Usage: %s base exponent \n", argv[0]);
        cout << "Usage: " << argv[0] << "base exponent" <<endl;
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    double result = power(base, exponent);
    // printf("%g ^ %d is %g\n", base, exponent, result);
    cout << base << "^" << exponent << " is " << result <<endl;
    return 0;
}
```
<center><font color=gray>Demo_1/main.cpp</font></center>

首先编写`CMakeList.txt`，并保存在与`main.cpp`文件同一个目录下：
```
~/Demo_1
    |--main.cpp
    |--CMakeList.txt
```
一个最基本的`CMakeList.txt`是这样的：
```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (Demo_1)
# 指定生成目标
add_executable(Demo main.cpp)
```
<center><font color=gray>Demo_1/CMakeList.txt</font></center>

`CMake`中，`#`后面的内容为注释，**命令不区分大小写**，参数之间用空格分隔，基本格式为：
```cmake
commandName(arg1 arg2 ...)
```

上面的`CMakeList.txt`中的三个命令：

- `cmake_minmum_required()`用来指定所需的`CMake`的最低版本。
- `project()`中的参数表示项目名称。
- `add_excutable()`中有两个参数`Demo`和`main.cc`，意思是将`main.cc`源文件编译成一个名为`Demo`的可执行文件。

##### 2.1.2.    编译和运行

在编写完`CMakeList.txt`之后，执行`cmake ${CMAKELIST_PATH}`，会在按照文件中的配置和参数，在当前目录生成编译所需要的一系列文件，其中包含`Makefile`文件。
- `cmake`命令是可以附带各种参数的，在命令后用空格隔开使用，`--build`，`--target`等。

```
~/Demo_1
    |--CMakeFiles
    |--CMakeCache.txt
    |--cmake_install.cmake
    |--CMakeList.txt
    |--main.cpp
    |--Makefile
```
生成`Makefile`后再执行`make ${MAKEFILE_PATH}`命令即可编译得到`Demo`可执行文件。

运行编译后的可执行文件：
```
$ ./Demo 2 10
2^10 is 1024
```





#### 参考:
1.  [CMake 入门实战 - Hahack](https://www.hahack.com/codes/cmake/)
2.  [CMake简易入门 - nblogs](https://www.cnblogs.com/foundkey/p/10213450.html)
