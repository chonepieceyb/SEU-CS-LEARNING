////////////////////////////////////////////////////////////////
// VCKBASE Online Journal
//
// getip1.cpp
//
// 本程序报告本机上每一块网卡的IP地址:
//
// 提示：要在环境变量中正确指定wsock32.lib库的路径;
//
// Make sure your INCLUDE and LIB environment variables are set up properly;
// you can run vcvars32.bat
//
#include <winsock.h>
#include <wsipx.h>
#include <wsnwlink.h>
#include <stdio.h>

int main()
{
	// 初始化 Windows sockets API. 要求版本为 version 1.1
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData)) {
		printf("WSAStartup failed %s\n", WSAGetLastError());
		return -1;
	}

	// 获得主机名.
	char hostname[256];
	int res = gethostname(hostname, sizeof(hostname));
	if (res != 0) {
		printf("Error: %u\n", WSAGetLastError());
		return -1;
	}
	printf("hostname=%s\n", hostname);

	// 根据主机名获取主机信息. 
	hostent* pHostent = gethostbyname(hostname);
	if (pHostent==NULL) {
		printf("Error: %u\n", WSAGetLastError());
		return -1;
	}

	// 解析返回的hostent信息
	hostent& he = *pHostent;
	printf("name=%s\naliases=%s\naddrtype=%d\nlength=%d\n",	he.h_name, he.h_aliases, he.h_addrtype, he.h_length);

	sockaddr_in sa;
	for (int nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) {
		memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
		printf("Address: %s\n", inet_ntoa(sa.sin_addr));		//解析返回的hostent信息display as string
	}
	
	//尝试gethostbyaddr()函数
	struct sockaddr_in LocalHostAddr;//服务主机地址 
	HOSTENT* pResult;

	LocalHostAddr.sin_family=AF_INET; 
	LocalHostAddr.sin_port=htons(u_short(21)); 
	//先获得IP，在通过IP获得hostname
	for (nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) {
		memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
		LocalHostAddr.sin_addr.s_addr=inet_addr(inet_ntoa(sa.sin_addr)); 
		pResult=gethostbyaddr((const char *) & (LocalHostAddr.sin_addr.s_addr),4,AF_INET); 

		printf("Host Name: %s\n", pResult->h_name);		//解析返回的hostent信息display as string
	}
	struct servent * sptr;
	sptr=getservbyname("domain", "udp");
	printf("Test getservbyname: %s\n",sptr->s_aliases);

	sptr=getservbyport(htons(53), "udp");
	printf("Test getservbyport: %s\n",sptr->s_aliases);

	
	// 终止 Windows sockets API
	WSACleanup();

	return 0;
}