## 关于`int main(int argc,char* argv[ ])`—— C++中`main()`函数的学习
> 刚开始学C++，一直不理解main函数里面的参数到底是什么意思，有什么作用

刚开始学C\+\+的时候，`main()`函数里都是不带参数的，`main()`函数后的括号都是空括号。但是看到别人写的程序里，都是`int main(int argc,char* argv[ ])`这样的形式。

实际上`main()`函数是可以带参数的，这个参数可以认为是`main()`函数的**形式参数**。

> 由于main函数不能被其它函数调用，因此不可能在程序内部取得实际值。那么，在何处把实参值赋予main函数的形参呢? 实际上,main函数的参数值是从操作系统命令行上获得的。当我们要运行一个可执行文件时，键入文件名，再输入实际参数即可把这些实参传送到main的形参中去。

先来看一个计算指数幂的例子，例子程序先定义了一个计算指数幂的函数`power()`，然后在`main()`函数中使用它进行计算：

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
        cout << "Usage: " << argv[0] << "base exponent" <<endl;
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    double result = power(base, exponent);
    cout << base << "^" << exponent << " is " << result <<endl;
    return 0;
}
```
<center><font color=gray>Demo_1.cpp</font></center>

编译后的运行结果：

```
$ ./Demo_1 5 4
5 ^ 4 is 625
$ ./Demo_1 7 3
7 ^ 3 is 343
$ ./Demo_1 2 10
2 ^ 10 is 1024
```

这个例子中我们向`main()`函数传入了两个数字（实参），然后用传入的数计算了指数幂。

C\+\+中规定`main()`函数只能有两个：

- 第一个形参`int argc`表示命令行总参数（传入的实参）个数，因此它必须是整型变量，默认值是1。
- 第二个形参`char *argv[]`用来存放传入的实参，**其中第0项是程序的全名(因此argc的默认值是1)**，是一个字符数组指针，其中共有argc个参数。

> 不知道你注意到没有，这个数组是char型的，那么Demo_1例子中是怎么用它们来计算的呢？  `atof()` `atoi()`

再来看一个小例子，这个例子中我们在命令行向程序传入几个实参，然后再依次打印出`argv[]`中的项：
```cpp
#include <iostream>
 
int main(int argc,char * argv[])
{
	for (int i=0;i<argc;i++)
	{
		std::cout << "argv" << i << " is " << argv[i] << std::endl;
	}
	system("pause");
	return 0;
}
```
<center><font color=gray>Demo_2.cpp</font></center>

编译后的运行结果：
```
$ ./Demo_2 1 2 3
argv0 is ./Demo_2
argv1 is 1
argv2 is 2
argv3 is 3
```



##### 参考：
1. [int main(int argc,char* argv[])详解，以及与int main()有什么区别 - CSDN](https://blog.csdn.net/zhaobinbin2015/article/details/81007737)
2. [int main(int argc,char* argv[])详解 - cnblogs](https://www.cnblogs.com/-Mr-y/p/7985624.html)
3. [C++：int main(int argc,char * argv[]) - CSDN](https://blog.csdn.net/mars_xiaolei/article/details/89399101)
3. [CMake 入门实战 - HaHack](https://www.hahack.com/codes/cmake/)
