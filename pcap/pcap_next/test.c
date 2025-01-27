#include <stdio.h>
#include <pcap.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <time.h>

#define DEV_1 "p3p1"
/*the printer running when packet have captured*/
void printer()
{
	printf("A packet is captured!\n");
	return;
}

int main(int argc, char **argv)
{
	int i;
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* descr;      /*you can man it*/
	const u_char *packet;
	struct pcap_pkthdr hdr;     /* pcap.h */
	struct ether_header *eptr;  /* net/ethernet.h */

	u_char *ptr; /* printing out hardware header info */

	/* grab a device to peak into… */
	dev = pcap_lookupdev(errbuf);

	if(dev == NULL)
	{
		printf("%s\n",errbuf);
		exit(1);
	}

	printf("DEV: %s\n",dev);

	/* open the device for sniffing.

	pcap_t *pcap_open_live(char *device,int snaplen, int prmisc,int to_ms,
	char *ebuf)

	snaplen - maximum size of packets to capture in bytes
	promisc - set card in promiscuous mode?
	to_ms   - time to wait for packets in miliseconds before read
	times out
	errbuf  - if something happens, place error string here

	Note if you change "prmisc" param to anything other than zero, you will
	get all packets your device sees, whether they are intendeed for you or
	not!! Be sure you know the rules of the network you are running on
	before you set your card in promiscuous mode!!     */

	//打开捕获设备DEV_1， 所有的捕获  混杂模式  无限等待  出错buffer
	descr = pcap_open_live(DEV_1,65535,1, 0,errbuf);

	if(descr == NULL)
	{
		printf("pcap_open_live(): %s\n",errbuf);
		exit(1);
	}

	/*
	grab a packet from descr (yay!)
	u_char *pcap_next(pcap_t *p,struct pcap_pkthdr *h)
	so just pass in the descriptor we got from
	our call to pcap_open_live and an allocated
	struct pcap_pkthdr                                 */

	packet = pcap_next(descr,&hdr);
	/*一直在这里等待， 用firefox打开网页也无效， 最终发现pcap_open_live打开的设备不对，
	centos 7中， pcap_lookupdev得到的设备是virbr0，一个虚拟网卡。 执行ifconfig -a，查看
	所有设备
[root@localhost pcap_next]# ifconfig -a
lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 0  (Local Loopback)
        RX packets 44  bytes 3630 (3.5 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 44  bytes 3630 (3.5 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

p3p1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.220.207  netmask 255.255.255.0  broadcast 192.168.220.255
        inet6 fe80::d6be:d9ff:fee3:30d  prefixlen 64  scopeid 0x20<link>
        ether d4:be:d9:e3:03:0d  txqueuelen 1000  (Ethernet)
        RX packets 3056624  bytes 482746856 (460.3 MiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 2011521  bytes 1744715130 (1.6 GiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

virbr0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        inet 192.168.122.1  netmask 255.255.255.0  broadcast 192.168.122.255
        ether 52:54:00:47:f4:78  txqueuelen 0  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

virbr0-nic: flags=4098<BROADCAST,MULTICAST>  mtu 1500
        ether 52:54:00:47:f4:78  txqueuelen 500  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

[root@localhost pcap_next]# ifconfig
lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 0  (Local Loopback)
        RX packets 44  bytes 3630 (3.5 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 44  bytes 3630 (3.5 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

p3p1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.220.207  netmask 255.255.255.0  broadcast 192.168.220.255
        inet6 fe80::d6be:d9ff:fee3:30d  prefixlen 64  scopeid 0x20<link>
        ether d4:be:d9:e3:03:0d  txqueuelen 1000  (Ethernet)
        RX packets 3059227  bytes 482993839 (460.6 MiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 2015782  bytes 1748798030 (1.6 GiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

virbr0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        inet 192.168.122.1  netmask 255.255.255.0  broadcast 192.168.122.255
        ether 52:54:00:47:f4:78  txqueuelen 0  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

		p3p1才是本机真实设备名
	*/

	if(packet == NULL)
	{/* dinna work *sob* */
		printf("Didn’t grab packet\n");
		exit(1);
	}

	/*  struct pcap_pkthdr {
	struct timeval ts;   time stamp
	bpf_u_int32 caplen;  length of portion present
	bpf_u_int32;         lebgth this packet (off wire)
	}
	*/

	printf("Grabbed packet of length %d\n",hdr.len);
	printf("Recieved at ….. %s\n",ctime((const time_t*)&hdr.ts.tv_sec));
	printf("Ethernet address length is %d\n",ETHER_HDR_LEN);

	/* lets start with the ether header… */
	eptr = (struct ether_header *) packet;

	/* Do a couple of checks to see what packet type we have..*/
	if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
	{
		printf("Ethernet type hex:%x dec:%d is an IP packet\n",
		ntohs(eptr->ether_type),
		ntohs(eptr->ether_type));
	}
	else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
	{
		printf("Ethernet type hex:%x dec:%d is an ARP packet\n",
		ntohs(eptr->ether_type),
		ntohs(eptr->ether_type));
	}
	else
	{
		printf("Ethernet type %x not IP", ntohs(eptr->ether_type));
		exit(1);
	}

	/* THANK YOU RICHARD STEVENS!!! RIP*/
	ptr = eptr->ether_dhost;
	i = ETHER_ADDR_LEN;
	printf(" Destination Address:  ");
	do
	{
		printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
	}while(-i>0);

	printf("\n");

	ptr = eptr->ether_shost;
	i = ETHER_ADDR_LEN;
	printf(" Source Address:  ");
	do
	{
		printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
	}while(-i>0);
	printf("\n");

	return 0;
}


/*
[root@localhost pcap_next]# ./test 
DEV: virbr0
Grabbed packet of length 1514
Recieved at ….. Wed Jan  6 01:10:25 2016

Ethernet address length is 14
Ethernet type hex:800 dec:2048 is an IP packet
Destination Address:   d4
Source Address:   d4

*/
