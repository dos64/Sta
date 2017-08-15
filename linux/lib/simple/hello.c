//link :http://blog.csdn.net/Dearggae/article/details/47612565

#include <stdio.h>
void hello()
{
    printf("Hello girl\n");
}
/* 编译：gcc -c -Wall -Werror -fPIC fso.c
         gcc -shared -o libfso.so fso.o
         -c：只激活预处理、编译和汇编，只输出.o格式的obj文件
         -Wall：生成所有警告信息
         -Werror：将warn视为error并停止编译
         -fpic：编译动态库必须，输出不依赖位置的代码
         -shared：编译动态库必须选项
         -o：生成的动态库名称
         */

