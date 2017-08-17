#include <sys/ptrace.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    pid=atoi(argv[1]);
   if(0!= ptrace(PTRACE_ATTACH,pid,NULL,NULL))//使用ptrace跟踪进程
   {
       perror("error");
   }
   wait(NULL);
   int data=ptrace(PTRACE_PEEKDATA,pid,(void*)0x8049760,0);//读取i的值
   printf("data=%d\n",data);//打印出来看看
   ptrace(PTRACE_POKEDATA,pid,(void*)0x8049760,256);//把i的值修改成256
    ptrace(PTRACE_DETACH,pid,0,0);//停止跟踪

}
