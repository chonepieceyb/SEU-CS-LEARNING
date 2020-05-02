/***********************************************/
/*************** IPv6 Client  ******************/
/***********************************************/
#include "winsock2.h"
#include "iostream.h"
#include "ws2tcpip.h" 
#include "tpipv6.h"
#pragma comment(lib,"WS2_32.lib") 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_SERVER     "172.18.13.33"
#define DEFAULT_FAMILY     PF_UNSPEC
#define DEFAULT_SOCKTYPE   SOCK_STREAM
#define DEFAULT_PORT       "5001"
#define DEFAULT_EXTRA      0 

#define BUFFER_SIZE        4

int main(int argc, char **argv)
{
	char AddrName[NI_MAXHOST];
    char *Server = DEFAULT_SERVER;
    int Family = DEFAULT_FAMILY;
    int SocketType = DEFAULT_SOCKTYPE;
    char *Port = DEFAULT_PORT;
    int RetVal, AddrLen;
    int ExtraBytes = DEFAULT_EXTRA;
    unsigned int Iteration, MaxIterations = 1;
    BOOL RunForever = FALSE;
    WSADATA wsaData;
    ADDRINFO Hints, *AddrInfo, *AI;
    SOCKET ConnSocket;
    struct sockaddr_storage Addr;
    char Buffer[4]={'a','b','c','d'};


	if ((RetVal = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) 
	{
        cout<<"WSAStartup error";
        WSACleanup();
        return -1;
    }

	//把本地地址信息赋给类型为Addrinfo的变量
	memset(&Hints, 0, sizeof(Hints));
    Hints.ai_family = Family;
    Hints.ai_socktype = SocketType;
    RetVal = getaddrinfo(Server, Port, &Hints, &AddrInfo);
    if (RetVal != 0) 
	{
        cout<<"getaddinfo() fail";
        WSACleanup();
        return -1;
    }

	 for (AI = AddrInfo; AI != NULL; AI = AI->ai_next) 
	 {

        //Open a socket with the correct address family for this address.
        ConnSocket = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
		cout<<"AI->ai_family:"<<AI->ai_family<<"  AI->ai_socktype:"<<AI->ai_socktype<<"   AI->ai_protocol:"<<AI->ai_protocol<<endl;
        if (ConnSocket == INVALID_SOCKET) 
		{
            cout<<"socket error";
            continue;
        }

		if (connect(ConnSocket, AI->ai_addr, AI->ai_addrlen) != SOCKET_ERROR)
			break;

  
		closesocket(ConnSocket);
	 }

	    if (AI == NULL) 
		{
        fprintf(stderr, "Fatal error: unable to connect to the server.\n");
        WSACleanup();
        return -1;
		}
/*        //一些帮助信息
        AddrLen = sizeof(Addr);
      if (getpeername(ConnSocket, (LPSOCKADDR)&Addr, &AddrLen) == SOCKET_ERROR) 
	  {
       cout<<"getpeername() fail ";
	  } 
	  else 
	  {
        if (getnameinfo((LPSOCKADDR)&Addr, AddrLen, AddrName,
                        sizeof(AddrName), NULL, 0, NI_NUMERICHOST) != 0)
            strcpy(AddrName, "<unknown>");
        printf("Connected to %s, port %d, protocol %s, protocol family %s\n",
               AddrName, ntohs(SS_PORT(&Addr)),
               (AI->ai_socktype == SOCK_STREAM) ? "TCP" : "UDP",
               (AI->ai_family == PF_INET) ? "PF_INET" : "PF_INET6");
	  }
	 
	    freeaddrinfo(AddrInfo);	
		AddrLen = sizeof(Addr);
    if (getsockname(ConnSocket, (LPSOCKADDR)&Addr, &AddrLen) == SOCKET_ERROR) 
	{
        cout<<"getsockname() fail ";
    } 
	else 
	{
        if (getnameinfo((LPSOCKADDR)&Addr, AddrLen, AddrName,
                        sizeof(AddrName), NULL, 0, NI_NUMERICHOST) != 0)
            strcpy(AddrName, "<unknown>");
        printf("Using local address %s, port %d\n",
               AddrName, ntohs(SS_PORT(&Addr)));
	}
*/
	for (Iteration = 0; RunForever || Iteration < MaxIterations; Iteration++) 
	{

		RetVal = send(ConnSocket, Buffer, 4, 0);
        if (RetVal == SOCKET_ERROR)
		{
            cout<<"send error";
            WSACleanup();
            return -1;
        }
         memset(Buffer, 0, sizeof(Buffer));
	}	
	 
	shutdown(ConnSocket, SD_SEND);
	closesocket(ConnSocket);
    WSACleanup();
    return 0;
}
