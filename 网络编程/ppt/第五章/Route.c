/*
* File name: Route.c
* Abstract : get the routing table, add the routing table, 
*            delete the routing table.
* 
* Edition  : 1.0
* Data     : 2006/9/5
*
*
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <resolv.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <linux/route.h>
#include <arpa/nameser.h>

#define _PATH_PROCNET_ROUTE	"/proc/net/route"

#ifdef SIOCADDRTOLD
#define mask_in_addr(x) (((struct sockaddr_in *)&((x).rt_genmask))->sin_addr.s_addr)
#define full_mask(x) (x)
#else
#define mask_in_addr(x) ((x).rt_genmask)
#define full_mask(x) (((struct sockaddr_in *)&(x))->sin_addr.s_addr)
#endif


int resolve(char *name, struct sockaddr *sap)
{
	struct hostent *hp;
	struct netent  *np;
	struct sockaddr_in *sin;

	sin = (struct sockaddr_in *) sap;
	sin->sin_family = AF_INET;
	sin->sin_port = 0;

	/* Default is special, meaning 0.0.0.0. */
	if (!strcmp(name, "default")) 
	{
		sin->sin_addr.s_addr = INADDR_ANY;
		return (1);
	}
	/* Try the NETWORKS database to see if this is a known network. */
	if ((np = getnetbyname(name)) != (struct netent *) NULL) 
	{
		printf("getnetbyname resolve successful!\n");
		sin->sin_addr.s_addr = htonl(np->n_net);
		strcpy(name, np->n_name);
		return (1);
	}
	
	/*printf("Name hp->n_name: %c\n", np->n_name);*/
	
	if ((hp = gethostbyname(name)) == (struct hostent *) NULL) 
	{
		printf("gethostbyname  error!%c\n", hp->h_name);
		errno = h_errno;
		return (-1);
	}
	memcpy((char *) &sin->sin_addr, (char *) hp->h_addr_list[0], hp->h_length);
	strcpy(name, hp->h_name);
	
	printf("sin->sin_addr:%c\n", (char *)&sin->sin_addr);
/*
 * assume it's a network if the least significate byte is 0,
 * as that's not a valid host address.
 */
	return ((ntohl(sin->sin_addr.s_addr) & 0xff) == 0);
	
}


/*add a routing to the route table
* return 0 if success.
*/
int addRoute(char *route)
{
	struct rtentry rt;
	struct sockaddr *addr;
	struct sockaddr_in *in_addr;
	struct in_addr a;
	struct sockaddr_in *addrp;
	//struct sockaddr mask;
	//char   netmask[128] = "default";
	char   mask[4] = {255,255,255,255};
	char   gateway[4] = {172,18,13,4};
	int s;
	
	printf("In the Addroute!\n");
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
        if (s < 0)
        {
                printf("Socket error!");
                return (-1);
        }	

	memset((char *) &rt, 0, sizeof(struct rtentry));
	/*if ((resolve(route, &rt.rt_dst)) < 0) 
	{
		printf("Route is error!");
		return (-1);
	}*/
	
	a.s_addr = inet_addr(route);
	printf("12344444:%s\n", inet_ntoa(a.s_addr));
	//定义一个增加表项的指针（目的地址），并将route的值赋之
	addrp = (struct sockaddr_in *) &rt.rt_dst;
	memset(addrp, 0, sizeof(struct sockaddr_in));
	addrp->sin_family = AF_INET;
	addrp->sin_port = 0;
	memcpy(&addrp->sin_addr.s_addr, (char *) &a, sizeof(struct in_addr));
	
	//addrp->sin_addr.s_addr = inet_addr("172.18.13.33");
	printf("--------------:%s\n", inet_ntoa(addrp->sin_addr));
	/*s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		printf("Socket error!");
		return (-1);
	}*/

	
	

	/*addrp->sin_family = AF_INET;
	addrp->sin_port = 0;
	addrp->sin_len = sizeof(*addrp);
	addrp->sin_addr = in_addr->sin_addr;
	memcpy(&rt.rt_dst, addrp, sizeof(*addrp));
	memcpy(&addrp->sin_addr.s_addr, mask, 4);
	memcpy(&rt.rt_genmask, addrp, sizeof(*addrp));*/

	/*if ((resolve(netmask, &mask)) < 0) 
	{
		printf("netmask error!");
		return (-1);
	}
	rt.rt_genmask = full_mask(mask);*/
	//rt.rt_genmask = ((struct sockaddr_in *) &(mask)->sin_addr.s_addr;
	printf("1\n");
	/*if (resolve(gateway, &rt.rt_gateway) < 0)
	{
		printf("gateway error!");
		return -1;
	}*/
	printf("2\n");
	
	//memset(in_addr, 0, sizeof(struct sockaddr_in));
	in_addr = (struct sockaddr_in *) &rt.rt_dst;
	memset(in_addr, 0, sizeof(struct sockaddr_in));
	in_addr->sin_family = AF_INET;
	in_addr->sin_port = 0;
	//目的地址的子网掩码
	memcpy(&in_addr->sin_addr.s_addr, mask, 4);
	memcpy(&rt.rt_genmask, in_addr, sizeof(*in_addr));	
	//通往目的地址的网关
	memcpy(&in_addr->sin_addr.s_addr, gateway, 4);
	memcpy(&rt.rt_gateway, in_addr, sizeof(*in_addr));
	
	printf("3\n");
	rt.rt_dev = "eth0";
	rt.rt_flags = (RTF_UP | RTF_GATEWAY);

	rt.rt_metric = 0;

	if (ioctl(s, SIOCADDRT, &rt))
	{
		if (errno != EEXIST)
		{
			close(s);
			return -1;
		}
	}
	
	printf("Ioctl success!\n");
	close(s);
	return 0;
}

/*get the whole entry of the routing tables*/
void getWholeRoute()
{
	char *buf, *next, *lim;
   	int fd;
   	int r;
	register struct rt_msghdr *rtm;
   	struct rt_giarg gi_arg, *gp;
   
   	fd = open(_PATH_ROUTE, O_RDONLY);
   	if (fd < 0)
   		printf("open error!\n");
   
   	gi_arg.gi_op = KINFO_RT_DUMP;
   	gi_arg.gi_where = (caddr_t)0;
   	gi_arg.gi_size = 0;
   	gi_arg.gi_arg = 0;
   	r = ioctl(fd, RTSTR_GETROUTE, &gi_arg);
   	if (r < 0)
   		printf("IOCTL error!\n");

   	/* gi_size includes sizeof(gi_arg) */
   	if ((buf = malloc(gi_arg.gi_size)) == 0)
   		printf("malloc memory error!\n00");
   	gp = (struct rt_giarg *)buf;
   	gp->gi_size = gi_arg.gi_size;
   	gp->gi_op = KINFO_RT_DUMP;
   	gp->gi_where = (caddr_t)buf;
   	gp->gi_arg = 0;

   	r = ioctl(fd, RTSTR_GETROUTE, buf);
   	if (r < 0)
   		printf("get route tables error!\n");
   	lim = buf + gp->gi_size;
   	buf += sizeof(gi_arg);
   	for (next = buf; next < lim; next += rtm->rtm_msglen) 
	{
   		rtm = (struct rt_msghdr *)next;
   		printf("v: %d type: 0x%x flags: 0x%x addrs: 0x%x pid: %d seq: %d\n",
				rtm->rtm_version, rtm->rtm_type, rtm->rtm_flags,
				rtm->rtm_addrs, rtm->rtm_pid, rtm->rtm_seq);
   	}
}




int main(int argc, char **argv)
{
	int   i;
	char s[] = "172.18.13.33";
	struct rtentry t;
	
	printf("1212\n");
	/*i = resolve(s, &t.rt_dst);
	if (i < 0)
	{
		printf("error!\n");
	}	

	printf("out put the i =%d", i);	

	return (i);*/
	i = addRoute(s);
	if (i < 0)
	{
		printf("AddRoute error!\n");
	}
	
	return (i);
}	





