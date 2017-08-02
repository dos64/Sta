#include <stdio.h>
#include <pthread.h>

//线程1

void thread_1(void)
{
    int i=0;
    for(i=0;i<10;i++)
    {
        printf("This is pthread_1\n");
        if(i==5)
        {
            pthread_exit(0);
        }
    }
}

//线程2
void thread_2(void)
{
    int i=0;
    for(i=0;i<10;i++)
    {
        printf("This is pthread_2\n");
    }
    pthread_exit(0);
}

int main()
{
    pthread_t t1,t2;
    int i,ret;
    //创建线程 1 
    ret=pthread_create(&t1,NULL,(void*)thread_1,NULL);
    if(ret!=0)
    {
        printf("Create thread error\n");
        return -1;
    }
//创建线程 2 
    ret=pthread_create(&t2,NULL,(void*)thread_2,NULL);
    if(ret!=0)
    {
        printf("Create thread error\n");
    }
//等待线程结束
      pthread_join(t1,NULL);
      pthread_join(t2,NULL);
      return 0;
}
