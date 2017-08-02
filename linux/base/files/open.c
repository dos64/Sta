#include <stdio.h>
#include <fcntl.h>
int main(void)
{
    int fd;
    if((fd=open("./test.txt",O_RDWR|O_APPEND|O_EXCL))<0)
    {
        perror("open error\n");
    }
    close(fd);
    return 0;
}
