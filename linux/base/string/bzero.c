#include <stdio.h>
#include <string.h>
int main()
{
    char *p="abcdefg";
    char a[5];
    int i;
//  bzero(p,sizeof(p));
    printf("bzero function\n");
    printf("-----------------------------------------\n");
    bzero(a,sizeof(a));//初始化数组a里面的元素为0
    for(i=0;i<5;i++)
    {   
        printf("%d\n",a[i]);
    }
    printf("-----------------------------------------\n");

 //bcopy
    printf("bcopy function\n");
    bcopy(p,a,sizeof(a));//逐个复制p指向的内容到数组a中
    for(i=0;i<5;i++)
    {   
        printf("%c\n",a[i]);
    }

    printf("-----------------------------------------\n");
    printf("bcopy function\n");

  //memset
  memset(a,10,sizeof(a));//把数组a 所有的元素修改为10
    for(i=0;i<5;i++)
    {   
        printf("%d\n",a[i]);
    }
}
