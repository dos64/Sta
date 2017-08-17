#include <stdio.h>
#include <sys/ptrace.h>
int main()
{
    static int i;//静态全局变量，每次运行地址不变
    int abc=9527;//临时变量，地址不固定 但是依然有办法修改。用内存扫描工具 scanmem
    printf("pid %d\n",getpid());
    printf("i=%x    abc=%x\n",&i,&abc);
    for(i=0;i<10000;i++)
    {
        printf("i =   %d   abc =  %d\n",i,abc);//让i每10秒自增一次，然后我们用另一个程序对 修改i的值
    sleep(10);
    }
}
