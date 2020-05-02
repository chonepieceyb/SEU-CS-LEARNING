/***********************************************/
/*************** IPv6 Server  ******************/
/***********************************************/
#include "winsock2.h"
#include "iostream.h"
#include "ws2tcpip.h"
#include "tpipv6.h"
#pragma comment(lib,"WS2_32.lib")
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_FAMILY     PF_UNSPEC  
#define DEFAULT_SOCKTYPE   SOCK_STREAM //TCP
#define DEFAULT_PORT       "5001" 
#define BUFFER_SIZE        4

int main(int argc, char **argv)
{
	char Buffer[BUFFER_SIZE];
    int Family = DEFAULT_FAMILY;
    int SocketType = DEFAULT_SOCKTYPE;
    char *Port = DEFAULT_PORT;
    char *Address = NULL;
    int i, NumSocks, RetVal, FromLen, AmountRead;
    SOCKADDR_STORAGE From;
    WSADATA wsaData;
    ADDRINFO Hints, *AddrInfo, *AI;
    SOCKET ServSock[FD_SETSIZE];
    fd_set SockSet;

//加载winsock库，初始化
	if ((RetVal = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
        cout<<"WSAStartup error";
        WSACleanup();
        return -1;
    }

//把本地地址信息赋给AddrInfo
	memset(&Hints, 0, sizeof(Hints));
    Hints.ai_family = Family;
    Hints.ai_socktype = SocketType;
    Hints.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
  	RetVal = getaddrinfo(Address, Port, &Hints, &AddrInfo);
    if (RetVal != 0)
	{
        cout<<"getaddrinfo error";
        WSACleanup();
        return -1;
    }

//对每个返回的地址创建一个套接字，并绑定
	for (i = 0, AI = AddrInfo; AI != NULL; AI = AI->ai_next, i++) 
	{
		if (i == FD_SETSIZE) 
		{
            cout<<"getaddrinfo returned more addresses than we could use.\n";
            break;
        }

		if ((AI->ai_family != PF_INET) && (AI->ai_family != PF_INET6))
		continue;
//创建套接字
        ServSock[i] = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
        if (ServSock[i] == INVALID_SOCKET)
		{
            cout<<"socket error";
            continue;
        }
//bind
		if (bind(ServSock[i], AI->ai_addr, AI->ai_addrlen) == SOCKET_ERROR) 
		{
            cout<<"bind error";
            continue;
        }

//listen
		if (listen(ServSock[i], 2) == SOCKET_ERROR)
		{
             cout<<"listen error";
             continue;
         }
        printf("'Listening' on port %s, protocol %s, protocol family %s\n",
               Port, (SocketType == SOCK_STREAM) ? "TCP" : "UDP",
               (AI->ai_family == PF_INET) ? "PF_INET" : "PF_INET6");
	}

    freeaddrinfo(AddrInfo);
	NumSocks = i;

//
	FD_ZERO(&SockSet);
	while(1)
	{
        FromLen = sizeof(From);
		
		for (i = 0; i < NumSocks; i++)
		{
            if (FD_ISSET(ServSock[i], &SockSet))
                break;
        }
		
		if (i == NumSocks) 
		{
            for (i = 0; i < NumSocks; i++)
                FD_SET(ServSock[i], &SockSet);
            if (select(NumSocks, &SockSet, 0, 0, 0) == SOCKET_ERROR) 
			{
                cout<<"select() fail";
                WSACleanup();
                return -1;
            }
        }//此时SockSet中为可读的套接字组

        for (i = 0; i < NumSocks; i++)
		{
            if (FD_ISSET(ServSock[i], &SockSet)) 
			{
                FD_CLR(ServSock[i], &SockSet);
                break;
            }
        }

        SOCKET ConnSock;
		//accept
		ConnSock = accept(ServSock[i], (LPSOCKADDR)&From, &FromLen);
        if (ConnSock == INVALID_SOCKET)
		{
            cout<<"accept error";
            WSACleanup();
            return -1;
        }
           /*
		    if (getnameinfo((LPSOCKADDR)&From, FromLen, Hostname,
                            sizeof(Hostname), NULL, 0, NI_NUMERICHOST) != 0)
            strcpy(Hostname, "<unknown>");
            printf("\nAccepted connection from %s\n", Hostname);
           */
			
			while (1) 
			{
				AmountRead = recv(ConnSock, Buffer, 4, 0);
             
				if (AmountRead == SOCKET_ERROR) 
				{
					cout<<"receive error";
					closesocket(ConnSock);
					break;
				}
             
				if (AmountRead == 0) 
				{
					cout<<"Client closed connection\n";
					closesocket(ConnSock);
                    break;
				}
			 
				for(int j=0;j<=3;j++)
				{
					printf("%c",(Buffer[j]));
				}
			
			}
    }
	return 0;	
}
