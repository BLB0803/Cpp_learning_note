# CMake入门学习笔记
> CMake is great. don't waste time on other C++ build tools, seriously.
### 1.  CMake是什么？
`CMake`是一款工程构建工具，类似的工具还有`autotool`，`qmake`，`Scons`等等。

具体见：
[为什么选用cmake](https://www.jianshu.com/p/835f777c9183)

随着功能的不断增加和复杂，我们写的C++程序也不可能再像`Helloworld.cpp`那样只有一个源文件了，整个程序工程中，会有很多的源文件与库文件，如何将他们组合，编译成可执行的程序，就是CMake作为工程构建工具的作用：它需要告诉计算机，整个复杂工程的文件之间有怎么样的关系。

这个过程通过一个叫`CMakeList.txt`的文件来进行。

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
> 原文C语言Demo源码出自[《CMake入门实战》源码 - github, wzpan](https://github.com/wzpan/cmake-demo)，本文改写为C++，[代码地址 - github](https://github.com/BLB0803/Cpp_learning_note)。
- 在`Linux`平台使用`CMake`生成`Makefile`并编译的流程：
1.  编写`CMake`配置文件`CMakeList.txt`
2.  执行命令`cmake ${CMAKELIST_PATH}`生成`Makefile`，`${CMAKELIST_PATH}`是`CMakeList.txt`所在的目录。
3.  执行命令`make`进行编译。

#### 2.1.   单个源文件的例子
##### 2.1.1.    编写CMakeList.txt
以下面的[`Demo_1` - github](https://github.com/BLB0803/Cpp_learning_note/tree/master/Demo_1)的实例来学习程序为例子，项目中的一个源文件`main.cpp`如下：
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
<center><font color=gray>~/Demo_1/main.cpp</font></center>

首先编写`CMakeList.txt`，并保存在与`main.cpp`文件同一个目录下：
```
~/Demo_1
    |
    +--main.cpp
    +--CMakeList.txt
```
一个最基本的`CMakeList.txt`是这样的，在这个例子中，我们只需要告诉计算机，我们要使用`main.cpp`文件，来编译一个名为`Demo`的可执行文件：
```
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo_1)

# 指定生成目标
add_executable(Demo main.cpp)
```
<center><font color=gray>~/Demo_1/CMakeList.txt</font></center>

`CMake`中，`#`后面的内容为注释，**命令不区分大小写**，参数之间用空格分隔，基本格式为：
```cmake
commandName(arg1 arg2 ...)
```

上面的`CMakeList.txt`中的三个命令：

- `cmake_minmum_required()`用来指定所需的`CMake`的最低版本。
- `project()`中的参数表示项目名称。
- `add_excutable()`中有两个参数`Demo`和`main.cc`，意思是将`main.cc`源文件编译成一个名为`Demo`的可执行文件。

##### 2.1.2.    编译和运行 [Demo_1 - github](https://github.com/BLB0803/Cpp_learning_note/tree/master/Demo_1)

在编写完`CMakeList.txt`之后，执行`cmake ${CMAKELIST_PATH}`：
```bash
shi@shi-Z370M-S01:~/Demo_1$ cmake .
-- Configuring done
-- Generating done
-- Build files have been written to: /home/shi/Demo_1
```


会在按照文件中的配置和参数，在当前目录生成编译所需要的一系列文件，其中包含`Makefile`文件。
- `cmake`命令是可以附带各种参数的，在命令后用空格隔开使用，`--build`，`--target`等。

```
~/Demo_1
    |
    +--CMakeFiles
    +--CMakeCache.txt
    +--cmake_install.cmake
    +--CMakeList.txt
    +--main.cpp
    +--Makefile
```
生成`Makefile`后再执行`make ${MAKEFILE_PATH}`命令即可编译得到`Demo`可执行文件。
```bash
shi@shi-Z370M-S01:~/Demo_1$ make
Scanning dependencies of target Demo
[ 50%] Building CXX object CMakeFiles/Demo.dir/main.cpp.o
[100%] Linking CXX executable Demo
[100%] Built target Demo
```

运行编译后的可执行文件：
```bash
shi@shi-Z370M-S01:~/Demo_1$ ./Demo 2 10
2^10 is 1024
```
#### 2.2.   多个源文件的例子
##### 2.2.1.    同目录下多个源文件 [Demo_2 - github](https://github.com/BLB0803/Cpp_learning_note/tree/master/Demo_2)
在实际编程过程中，如果有多个源文件，比如将`Demo_1.cpp`中的power函数单独写进一个`mathfunctions.cpp`源文件中：
```cpp
/*
 * power - Calculate the power of number.
 * @param base: Base value.
 * @param exponent: Exponent value.
 *
 * @return base raised to the power exponent.
 */

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
```
<center><font color=gray>~/Demo_2/mathfunctions.cpp</font></center>

然后在main函数中引用`MathFunctions.cpp`的`power`函数来进行计算：
```cpp
#ifndef POWER_H
#define POWER_H

extern double power(double base, int exponent);

#endif
```
<center><font color=gray>~/Demo_2/mathfunctions.h</font></center>

```
#include <iostream>

//  import power function
#include "MathFunctions.h" 

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
    //printf("%g ^ %d is %g\n", base, exponent, result);
    cout << base << "^" << exponent << " is " << result <<endl;
    return 0;
}
```
<center><font color=gray>~/Demo_2/main.cpp</font></center>

令工程变成如下结构：
```
~/Demo_2
    |
    +--CMakeList.txt
    +--main.cpp
    +--MathFunctions.cpp
    +--MathFunctions.h
```
这时我们只需要在`CMakeList.txt`中的`add_executable()`命令上添加新参数，变成这样就可以了：
```
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo_1)

# 指定生成目标
add_executable(Demo "main.cpp" "MathFunctions.cpp")
```
这里我们通过`CMake`告诉了计算机，我们要使用主文件`main.cpp`和函数文件`MathFunctions.cpp`来生成可执行程序`Demo`。

但是在源文件数量较多的时候，在`add_executable()`命令上添加新参数就会变得很麻烦，这时候我们可以使用`aux_source_directory()`命令：
```
aux_source_directory(<dir> <variable>)
```
这个命令会查找`<dir>`参数的目录下所有的源文件，然后将结果存进`<variable>`变量中，因此可以修改`CMakeList.txt`如下：

```
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo_1)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})
```
编译运行一下：
```bash
shi@shi-Z370M-S01:~/Demo_2$ cmake .
-- The C compiler identification is GNU 7.4.0
-- The CXX compiler identification is GNU 7.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/shi/Demo_2
shi@shi-Z370M-S01:~/Demo_2$ make
Scanning dependencies of target Demo
[ 33%] Building CXX object CMakeFiles/Demo.dir/MathFunctions.cpp.o
[ 66%] Building CXX object CMakeFiles/Demo.dir/main.cpp.o
[100%] Linking CXX executable Demo
[100%] Built target Demo
shi@shi-Z370M-S01:~/Demo_2$ ./Demo 2 10
2^10 is 1024
```
##### 2.2.2 多个目录和多个源文件 [Demo_3 - github](https://github.com/BLB0803/Cpp_learning_note/tree/master/Demo_3)
接下来我们将`MathFunctions.cpp`和`MathFunctions.h`文件移动到math目录下：
```
~/Demo_3
    |
    +--CMakeList.txt
    +--main.cpp
    +--math/
        |
        +--CMakeList.txt
        +--MathFunctions.cpp
        +--MathFunctions.h
```
这时候项目工程分成了主程序和库文件两个部分，这时候需要我们分别在**根目录**`~/Demo_3`和**库目录**`~/Demo_3/math/`各编写一个`CMakeList.txt`文件，将库目录`~/Demo_3/math/`里的文件编译成静态库再由根目录主程序`main.cpp`中的`main()`函数调用。

库目录`~/Demo_3/math/`下的`CMakeList.txt`：

```cmake
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS变量
aux_source_directory(. DIR_LIB_SRCS)

add_library(MathFunctions ${DIR_LIB_SRCS})
```
<center><font color=gray>~/Demo_3/math/CMakeList.txt</font></center>

之前我们使用`add_executable()`命令，编译生成可执行文件，在这个库目录的`CMakeList.txt`文件中，我们使用了`add_library()`函数，来将库目录中的文件编译为**静态连接库**。

这样我们先告诉了计算机，我们需要用库文件`math`目录下的源文件，组成一个名为`MathFunctions`的库(library)。

之后我们回到根目录`~/Demo_3/`中，修改根目录的`CMakeList.txt`文件如下：
```cmake
# CMake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project(Demo_3)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
# aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(math)

# 指定生成目标
add_executable(Demo main.cpp)

# 添加链接库
target_link_libraries(Demo MathFunctions)
```
<center><font color=gray>~/Demo_3/CMakeList.txt</font></center>

在根目录新的`CMakeList.txt`中，我们使用`add_subdirectory()`命令，将库目录`/math`添加为一个辅助目录（subdirectory），告诉计算机我们将要用到这个目录下的文件或者库。

之后我们使用`target_link_libraries()`命令，将库目录`/math`下，已经在上一个`CMakeList.txt`中定义好的库`MathFunctions`与我们想要生成的可执行文件`Demo`相连接。

- 不要忘记修改主目录下`main.cpp`的头文件引用：
```cpp
// #include "MathFunctions.h"  old

#include "math/MathFunctions.h"  // new
```

编译并运行一下：
```bash
shi@shi-Z370M-S01:~/Demo_3$ cmake .
-- The C compiler identification is GNU 7.4.0
-- The CXX compiler identification is GNU 7.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/shi/Demo_3
shi@shi-Z370M-S01:~/Demo_3$ make 
[ 50%] Built target MathFunctions
Scanning dependencies of target Demo
[ 75%] Building CXX object CMakeFiles/Demo.dir/main.cpp.o
[100%] Linking CXX executable Demo
[100%] Built target Demo
shi@shi-Z370M-S01:~/Demo_3$ ./Demo 2 10
2^10 is 1024
```

##### 2.2.3.    自定义编译选项
`CMake`可以自定义编译选项，从而可以允许我们根据用户的环境和需求，选择最合适的编译方案，比如可以将上一节的我们自己写的`MathFunctions`库设置为一个可选的库，从而可以自由选择编译时是使用我们自己创建的库，还是调用标准库中的数学函数。

为此我们需要在**顶层**的`CMakeLists.txt`中添加选项。

首先需要在其中添加：
```
# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
```
`configure_file()`命令用来加入一个配置头文件`config.h`，这个文件将由`CMake`从`config.h.in`生成，通过这个机制，我们可以预定义一些参数和变量来控制代码生成。
然后再添加：
```
# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
       "Use provided math implementation" ON)
# 是否加入 MathFunctions 库
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/math")
  add_subdirectory (math)  
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)
```
`option()`命令中，我们定义了一个名为`USE_MYMATH`变量，并设置其默认值为`ON`。
随后的`if()`根据`USE_MYMATH`变量的值来决定我们是否使用自己编写的`MathFunctions`库。如果是，则添加头文件目录`${PROJECT_SOURCE_DIR}/math`，子目录`math`，并将可选库地址存于`EXTRA_LIBS`。

完整的`CMakeList.txt`如下：
```cmake
# CMake最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project(Demo_4)

# 加入一个配置头文件，用于处理CMake对源码的设置
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 是否使用自己的MathFunctions库
option(USE_MYMATH
       "Use provided math implementation"
	ON
  )

# 是否加入MathFunctions库
if (USE_MYMATH)
  # 添加头文件路径
  include_directories("${PROJECT_SOURCE_DIR}/math")
  # 添加math子目录
  add_subdirectory(math)
  # 收集可选库地址存于EXTRA_LIBS
  set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})

# 添加链接库
target_link_libraries(Demo ${EXTRA_LIBS})
```
这时我们需要生成的可执行文件`Demo`是由`DIR_SRCS`目录中的源文件生成，并与`EXTRA_LIBS`目录下的库进行连接。

配置文件`config.h`并不需要我们直接编写，我们需要编写一个`config.h.in`文件，来让`CMake`自动生成`config,h`，内容如下：

```
#cmakedefine USE_MYMATH
```
工程目录结构如下：

```
~/Demo_4
    |
    +--CMakeList.txt
    +--main.cpp
    +--config.h.in
    +--math/
        |
        +--CMakeList.txt
        +--MathFunctions.cpp
        +--MathFunctions.h
```

之后我们需要修改我们的源文件`main.cpp`，我们需要引用新的配置头文件`config.h`，让其根据`USE_MYMATH`的预定义值来选择调用`MathFunctions`库还是标准库。

修改后的`main.cpp`文件：
```cpp
#include <iostream>
// #include "math/MathFunctions.h"
#include "config.h"

#ifdef USE_MYMATH
    #include "math/MathFunctions.h"
#else
    #include<math.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3){
        cout << "Usage: " << argv[0] << "base exponent" <<endl;
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);

#ifdef USE_MYMATH
    cout << "Using our own math lib. "<<endl;
    double result = power(base, exponent);
#else
    cout << "Using standard math lib. "<<endl;
    double result = pow(base, exponent);
#endif
    cout << base << "^" << exponent << " is " << result <<endl;
    return 0;
}

```
编译一下：
```
shi@shi-Z370M-S01:~/Demo_4$ cmake .
-- The C compiler identification is GNU 7.4.0
-- The CXX compiler identification is GNU 7.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/shi/Demo_4
shi@shi-Z370M-S01:~/Demo_4$ make
Scanning dependencies of target MathFunctions
[ 25%] Building CXX object math/CMakeFiles/MathFunctions.dir/MathFunctions.cpp.o
[ 50%] Linking CXX static library libMathFunctions.a
[ 50%] Built target MathFunctions
Scanning dependencies of target Demo
[ 75%] Building CXX object CMakeFiles/Demo.dir/main.cpp.o
[100%] Linking CXX executable Demo
[100%] Built target Demo
shi@shi-Z370M-S01:~/Demo_4$ ./Demo 2 10
Using standard math lib. 
2^10 is 1024
```
这里出现了一个问题，用默认的`cmake`命令编译之后，执行可执行文件`Demo`时发现，并没有引用我们自己编写的库，而是引用了标准库。

之后检查所有文件没有发现问题，安装带gui的`CMake`后，执行`ccmake`命令，在gui中显示`USE_MYMATH`正常的被配置为`ON`，执行编译后运行：
```
shi@shi-Z370M-S01:~/Demo_4$ ./Demo 2 10
Using our own math lib. 
2^10 is 1024
```
结果正常调用了自己编写的库，目前原因未知。（2019.10.21）


#### 参考:
1.  [CMake 入门实战 - Hahack.com](https://www.hahack.com/codes/cmake/)
2.  [CMake简易入门 - cnblogs](https://www.cnblogs.com/foundkey/p/10213450.html)
