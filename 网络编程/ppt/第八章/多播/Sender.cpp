// MySocketest.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include"winsock2.h"
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#define  MCASTADDR "236.0.0.1"
#define  MCASTPORT  12345
#define BUFSIZE  1024 

int main(int argc, char* argv[])
{
	WSADATA wsd;
    struct sockaddr_in  remote;
	SOCKET sock,sockM;
	TCHAR sendbuf[BUFSIZE];
	int len = sizeof(struct sockaddr_in);
	//初始化WinSock2.2
	if(( WSAStartup(MAKEWORD(2,2),&wsd))!=0){
	   printf("WSAStartup() failed\n");
	   return -1;
	}

	if((sock=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_MULTIPOINT_C_LEAF|WSA_FLAG_MULTIPOINT_D_LEAF|
		WSA_FLAG_OVERLAPPED))==INVALID_SOCKET){
	
	  printf("socket failed with:%d\n",WSAGetLastError());
	  WSACleanup();
	  return -1;
	}
	
	//joining the multicast group
    remote.sin_family =AF_INET;
	remote.sin_port = htons(MCASTPORT);
	remote.sin_addr.s_addr = inet_addr(MCASTADDR);

	/* winsock 2.0*/
	if((sockM = WSAJoinLeaf(sock,(SOCKADDR *)&remote,sizeof(remote),NULL,NULL,NULL,NULL,JL_BOTH))==INVALID_SOCKET){
		printf("WSAJoinLeaf() failed : %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();

		return -1;
	 }
 //发送组播数据，当接收到的数据为"QUIT"时退出。
	while(1){
		printf("SEND : ");
		scanf("%s",sendbuf);
		if (sendto(sockM,(char *)sendbuf,strlen(sendbuf),0,(struct sockaddr *) &remote,sizeof(remote))==SOCKET_ERROR){
			printf("sendto failed with: %d\n", WSAGetLastError());
			closesocket(sockM);
			closesocket(sock);
			WSACleanup();
			return -1;
		}
		if (strcmp(sendbuf,"QUIT")==0)
			break;
		Sleep(500);
	}
	closesocket(sockM);
	closesocket(sock);
	WSACleanup();
	return 0;
}

