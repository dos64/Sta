#include <stdio.h>
extern void hello(void);
int main()
{
    printf("This is main\n");
    hello();
    return 0;
}
/*
 编译 :gcc -L $(pwd) -Wall -o main main.c -lhello
 运行如果出错：./main: error while loading shared libraries: libhello.so: cannot open shared object file: No such file or directory
 可以将编译的库文件加入到系统库文件搜索目录 ln -s /home/code/studyinghard/linux/lib/simple/libhello.so /usr/lib/

 */
