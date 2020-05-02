/*
* File name: ARP.c
* 
* Abstract : This file contains the operations of the ARP cache using IOCTL(), including 
*			 get(add/delete) the ARP cache table.
*
* Version  : 1.0	2006/9/3
* Author   : Luyifei
*
*
*
*
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if_arp.h>


void Del_Entry()
{
	int	sfd, rc;
	struct	sockaddr *sa;
	struct	arpreq	 arpreq;
	struct	in_addr  ina;
	struct	sockaddr_in *sin;
	char	ip[] = "172.18.13.32";				/*The IP you want to delete */
	unsigned char *hw_addr = "00:13:D4:CB:1E:B4";/*The mac address  删时不需要*/

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sfd < 0)
	{
		printf("socket error");
		exit(1);
	}
	
	sin = (struct sockaddr_in *) &arpreq.arp_pa;
	memset(sin, 0, sizeof(struct sockaddr_in));
	sin->sin_family = AF_INET;
	ina.s_addr = inet_addr(ip);
	memcpy(&sin->sin_addr, (char *)&ina, sizeof(struct in_addr));
	
	strcpy(arpreq.arp_dev, "eth0");
	
	rc = ioctl(sfd, SIOCDARP, &arpreq);

	if (rc < 0)
	{
		printf("Entry not available in cache");
	}
	else
	{
		printf("entry has been successfully retreiveed\n");
		hw_addr = (unsigned char *) arpreq.arp_ha.sa_data;
		printf("HWAddr found:%x:%x:%x:%x:%x:%x\n",hw_addr[0],hw_addr[1],hw_addr[2],hw_addr[3],hw_addr[4],hw_addr[5]);
	}	
}


int Set_Entry()
{
	int sd;
	struct arpreq arpreq;
	struct sockaddr_in *sin;
	struct in_addr ina;
	char   ip[] = "172.18.13.32";/* "172.18.13.31";*/
	char   eaddr[] = "00:13:D4:CB:1E:B4";/*"00:15:F2:4C:4E:1B";*///00-14-22-42-48-E6
	int    rc;
	u_char *ea;
	
	sd = socket(AF_INET,SOCK_DGRAM,0);
	if (sd < 0)
	{
		perror("socket() error\n");
		exit(1);
	}
	
	sin = (struct sockaddr_in *) &arpreq.arp_pa;
	memset(sin, 0, sizeof(struct sockaddr_in));
	
	sin->sin_family=AF_INET;
	ina.s_addr = inet_addr(ip);		//地址转换，序的不同
	memcpy(&sin->sin_addr, (char *)&ina, sizeof(struct in_addr));
	
	//定义硬件地址指针
	ea =(char*)arpreq.arp_ha.sa_data;
	//对指针所指内容赋值
	if(ether_aton(eaddr, ea))
	{
		printf("\nreturning 1");
		return (1);
	}
	printf("ea = %s",ea);

	arpreq.arp_flags=ATF_PERM;
	strcpy(arpreq.arp_dev, "eth0");

	printf("sa_data = %s",arpreq.arp_ha.sa_data);
	//设置
	rc = ioctl(sd, SIOCSARP, &arpreq);
	if (rc < 0)
	{
		perror("Entry not set...\n");
	}
	else
	{
		printf("\nentry has been successfully set");
	}
	return 0;
}

int Get_Entry()
{
	int sd, i;
	struct arpreq arpreq;
	struct sockaddr_in sin;
	struct in_addr ina;
	char   ip[] = "172.18.13.34";
	unsigned char *hw_addr;
	
	memset(&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("172.18.13.32");
	//初始化
	memset(&arpreq, '\0', sizeof(arpreq));
	//IP地址拷贝
	memcpy(&arpreq.arp_pa, &sin, sizeof(sin));
	//设备名
	memcpy(arpreq.arp_dev, "eth0", sizeof(arpreq.arp_dev));

	if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//获取ARP信息
	if (ioctl(sd, SIOCGARP, (char *)&arpreq) < 0)
	{
		perror("ioctl");
		exit(-1);
	}
	//MAC地址
	hw_addr = (unsigned char *) arpreq.arp_ha.sa_data;
	printf("\nHWAddr found : %x:%x:%x:%x:%x:%x\n", hw_addr[0], hw_addr[1],
		hw_addr[2], hw_addr[3], hw_addr[4], hw_addr[5]);
	return 0;
}


int ether_aton(char *a,char *n)		//a-->n；判断是否为合法MAC地址
{	
	int i, o[6];

	i = sscanf(a, "%x:%x:%x:%x:%x:%x", &o[0], &o[1], &o[2], &o[3], &o[4], &o[5]);

	printf("\n i=%d\n",i);

	printf("%x %x %x %x %x %x",o[0],o[1],o[2],o[3],o[4],o[5]);

	if (i != 6) 
	{
		perror("arp: invalid Ethernet address");
		return (1);
	}

	for (i=0; i<6; i++)
		n[i]=o[i];
	printf("\n");

	for(i=0;i<6;i++)
		printf("%x ",n[i]);
	printf("\n"); 
	return (0); 
}



int main(int argc, char **argv)
{
	int i;
	
	Del_Entry();	

	i = Get_Entry();
	
	return 0;	
}
