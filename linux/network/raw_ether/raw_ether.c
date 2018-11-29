#include<string.h>
#include <stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<net/if.h>
#include<time.h>
#include<linux/if_packet.h>

struct data{
    char data[46];
};

int main(int argc,char* argv[])
{
    struct data* packet=malloc(sizeof(struct data));

    struct sockaddr_ll sll;//要发数据链路层数据包，就必须指定发送的网络接口,否则无法发送数据
    int sk = socket(PF_PACKET, SOCK_RAW,0);/*使用pf_packet接口创建套接字*/
    sll.sll_ifindex = if_nametoindex("eth0");/*sll虽然是用来指定目的地址的，但是在这个结构体中sll_ifindex 却指定的是本机发送报文的接口索引*/
    while(1)

    {
    packet->data[13]=0x08;//第13 和14 字节  代表以太网上一层要解析的协议 这里0x0806 是IP协议 当然也可以填充垃圾数据，但是抓包只能是识别不出来的
    packet->data[14]=0x06;
    /*
     对于以太网，数据段大小为46-1500字节，不足46字节的数据将被自动补足到46字节
     */
    sendto(sk, packet, 15, 0, (struct sockaddr*)&sll, 120);//

    sleep(1);//防止发包速率过快 交换机挂了。。断网！
}
return 0;
}
