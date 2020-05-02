#include <Snmp.h>
#include <mgmtapi.h>
#include <winsock.h>
#include "StructDef.h"

#define DEF_PACKET_SIZE 32
#define MAX_PACKET 1024
#define ICMP_ECHO 8      //ICMP响应请求类型
#define ICMP_ECHOREPLY 0 //ICMP应答类型
///////////////////////////
//1. Read_TimeConfig函数功能:
//        读TimeConfig表
//        返回：TimeSet[TimeSetNo]存放设定了的定时器值
//2. programmer:
//        IAN ( 1999.11.18 )
///////////////////////////
void Read_TimeConfig(int TimeSet[],int & TimeSetNo)
{
	SQLRETURN vReturn;
	SQLHENV hOdbcEnv;
	SQLHDBC hDbConn;
	SQLHSTMT hDbStmt;
	char* SelectStatementTxt;

	SQLCHAR szDSN[10]="DBofPing";
	SQLCHAR szUID[10]="";
	SQLCHAR szAuthStr[]="";
	SQLINTEGER Time;
	SQLINTEGER length[1];
	int i;
    
	
	SelectStatementTxt=(char*)malloc( _MAX_PATH );
    strcpy(SelectStatementTxt, "SELECT * FROM TimeConfig");
	
	vReturn=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hOdbcEnv);

	if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
	{//=====分配环境句柄成功
		vReturn=SQLSetEnvAttr(hOdbcEnv,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,SQL_IS_INTEGER);

	   if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
	   {//=====设置环境句柄成功
		   vReturn=SQLAllocHandle(SQL_HANDLE_DBC,hOdbcEnv,&hDbConn);

	       if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
		   {//=====分配连接句柄成功
			   vReturn=SQLSetConnectAttr(hDbConn,5,(void*)SQL_LOGIN_TIMEOUT,0);

	           if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
			   {//=====设置连接句柄成功
				  vReturn=SQLConnect(hDbConn,(SQLCHAR*)szDSN,
		                        SQL_NTS,(SQLCHAR*)szUID,
				                SQL_NTS,(SQLCHAR*)szAuthStr,
				                SQL_NTS);
	              if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
				  {//=====连接数据库成功
	        	     printf("Connected OK!\n");
                     vReturn = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hDbStmt); 

					 if (vReturn == SQL_SUCCESS || vReturn == SQL_SUCCESS_WITH_INFO) 
					 {
 					    printf("SQLStatement OK!\n");
						vReturn = SQLExecDirect(hDbStmt,(unsigned char *)SelectStatementTxt,SQL_NTS);  
						vReturn =SQLBindCol(hDbStmt,1,SQL_C_ULONG,&Time,sizeof(Time),&length[0]);
                     //
						//
						i=0;
						vReturn=SQLFetch(hDbStmt);
						while (vReturn==SQL_ROW_SUCCESS)
						{
							TimeSet[i]=Time;
							vReturn=SQLFetch(hDbStmt);
							i++;
						}
						TimeSetNo=i;
						//
                     //
						if(vReturn!=SQL_SUCCESS)
						{
							SQLCHAR SqlState[6];
							SQLINTEGER NativeError;
							SQLCHAR ErrMsg[SQL_MAX_MESSAGE_LENGTH];
							i=1;
							printf("Error in SQLINSERT:%d \n",vReturn);
							while(SQLGetDiagRec(SQL_HANDLE_DBC,hDbConn,i,SqlState,
								               &NativeError,ErrMsg,sizeof(ErrMsg),NULL)
						 	     !=SQL_NO_DATA)
							    printf("Diag:%d,SQLSTATE:%s NativeError:%d ErrMsg:%s\n",
								        i++,SqlState,NativeError,ErrMsg);
						}
					 }
				  }
				  else
				  {
		              SQLCHAR sqlState[6];
		              SQLINTEGER NativeError;
		              SQLCHAR ErrMsg[SQL_MAX_MESSAGE_LENGTH];
		              i=1;
		              printf("Error in SQL connect:%d",vReturn);
                      while(SQLGetDiagRec(SQL_HANDLE_DBC,hDbConn,i,sqlState,
			                &NativeError,ErrMsg,sizeof(ErrMsg),NULL)
							!=SQL_NO_DATA)
                          printf("Dialog:%d,sqlstate:%s,NativeError:%d,ErrMsg:%s\n",i++,sqlState,NativeError,ErrMsg);
				  }
			   }
		   }
	   }
	   }
	   vReturn=SQLDisconnect(hDbConn);
	   if(hDbConn!=SQL_NULL_HANDLE)
		  SQLFreeHandle(SQL_HANDLE_DBC,hDbConn);
	   if(hOdbcEnv!=SQL_NULL_HANDLE)
		  SQLFreeHandle(SQL_HANDLE_ENV,hOdbcEnv);
	   free(SelectStatementTxt);

}

////////////////////////
// Read_PollingUse函数功能：
//           参数输入：TimeSet[TimeSetNo]
//           参数输出：定时器结构
//                     Timer{	int TimeSet;   设定的定时器值
//                              int IpNoForThis;该定时器下的IP数
//                     	        int Pointer;    IP二维数组的一维号
//                           }                           
//                     轮询IP的二维数组char* IpGroup[Pointer][] 
////////////////////////
                               
void Read_PollingUse(int TimeSet[],int & TimeSetNo,char* IpGroup[20][100],TM * Timer)
{
	SQLRETURN vReturn;
	SQLHENV hOdbcEnv;
	SQLHDBC hDbConn;
	SQLHSTMT hDbStmt;
	char* SelectStatementTxt;

	SQLCHAR szDSN[10]="DBofPing";
	SQLCHAR szUID[10]="";
	SQLCHAR szAuthStr[]="";
    SQLCHAR IP[20];
    long length[1];
    int i;

	SelectStatementTxt=(char*)malloc( _MAX_PATH );
    
	vReturn=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hOdbcEnv);

	if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
	{//=====分配环境句柄成功
		vReturn=SQLSetEnvAttr(hOdbcEnv,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,SQL_IS_INTEGER);

	   if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
	   {//=====设置环境句柄成功
		   vReturn=SQLAllocHandle(SQL_HANDLE_DBC,hOdbcEnv,&hDbConn);

	       if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
		   {//=====分配连接句柄成功
			   vReturn=SQLSetConnectAttr(hDbConn,5,(void*)SQL_LOGIN_TIMEOUT,0);

	           if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
			   {//=====设置连接句柄成功
				  vReturn=SQLConnect(hDbConn,(SQLCHAR*)szDSN,
		                        SQL_NTS,(SQLCHAR*)szUID,
				                SQL_NTS,(SQLCHAR*)szAuthStr,
				                SQL_NTS);
	              if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
				  {//=====连接数据库成功
	        	     printf("Connected OK!\n");
                     vReturn = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hDbStmt); 

					 if (vReturn == SQL_SUCCESS || vReturn == SQL_SUCCESS_WITH_INFO) 
					 {
 					    printf("SQLStatement OK!\n");
						//
						for(i=0;i<TimeSetNo;i++)
						{   
							vReturn=SQLFreeStmt(hDbStmt,SQL_RESET_PARAMS);
 						    vReturn = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hDbStmt); 
							char buff[50];
							strcpy(SelectStatementTxt, "SELECT IpAddr FROM PollingUse WHERE PollPeriod=");
							_itoa(TimeSet[i],buff,10);
							strcat(SelectStatementTxt,buff);
							vReturn = SQLExecDirect(hDbStmt,(unsigned char *)SelectStatementTxt,SQL_NTS);  
						    vReturn =SQLBindCol(hDbStmt,1,SQL_C_CHAR,IP,sizeof(IP),&length[0]);
						    Timer[i].TimeSet=TimeSet[i];
							Timer[i].Pointer=i;

							int j=0;
						    vReturn=SQLFetch(hDbStmt);
						    while (vReturn==SQL_ROW_SUCCESS)
							{
							   IpGroup[i][j]=new char[20];
							   strcpy(IpGroup[i][j],(const char *)IP);//
							   vReturn=SQLFetch(hDbStmt);
							   j++;
							}
							Timer[i].IpNoForThis=j;
						}
						//
						if(vReturn!=SQL_SUCCESS)
						{
							SQLCHAR SqlState[6];
							SQLINTEGER NativeError;
							SQLCHAR ErrMsg[SQL_MAX_MESSAGE_LENGTH];
							int i=1;
							printf("Error in SQLINSERT:%d \n",vReturn);
							while(SQLGetDiagRec(SQL_HANDLE_DBC,hDbConn,i,SqlState,
								               &NativeError,ErrMsg,sizeof(ErrMsg),NULL)
						 	     !=SQL_NO_DATA)
							    printf("Diag:%d,SQLSTATE:%s NativeError:%d ErrMsg:%s\n",
								        i++,SqlState,NativeError,ErrMsg);
						}
					 }
				  }
				  else
				  {
		              SQLCHAR sqlState[6];
		              SQLINTEGER NativeError;
		              SQLCHAR ErrMsg[SQL_MAX_MESSAGE_LENGTH];
		              int i=1;
		              printf("Error in SQL connect:%d",vReturn);
                      while(SQLGetDiagRec(SQL_HANDLE_DBC,hDbConn,i,sqlState,
			                &NativeError,ErrMsg,sizeof(ErrMsg),NULL)
							!=SQL_NO_DATA)
                          printf("Dialog:%d,sqlstate:%s,NativeError:%d,ErrMsg:%s\n",i++,sqlState,NativeError,ErrMsg);
				  }
			   }
		   }
	   }
	   }
	   vReturn=SQLDisconnect(hDbConn);
	   if(hDbConn!=SQL_NULL_HANDLE)
		  SQLFreeHandle(SQL_HANDLE_DBC,hDbConn);
	   if(hOdbcEnv!=SQL_NULL_HANDLE)
		  SQLFreeHandle(SQL_HANDLE_ENV,hOdbcEnv);
	   free(SelectStatementTxt);
////==================
}
////////////////////////////
///Update_PollingUse函数功能：
//				更新PollingUse表的DevStatus字段
////////////////////////////
bool In_UpdateDB=false;
UINT Update_PollingUse(LPVOID pParam)
{
	if(In_UpdateDB)
		Sleep(10);
	else
	{
		In_UpdateDB=true;
//	    SQLCHAR* IP=(SQLCHAR*)pParam;
		PingStatus* pingstatus=(PingStatus*)pParam;

	    SQLRETURN vReturn;
	    SQLHENV hOdbcEnv;
	    SQLHDBC hDbConn;
	    SQLHSTMT hDbStmt;
	    char* SelectStatementTxt;

	    SQLCHAR szDSN[10]="DBofPing";
	    SQLCHAR szUID[10]="";
	    SQLCHAR szAuthStr[]="";
        long length[1];
	    long DevStatus;
	    char buff[20];
    
	    SelectStatementTxt=(char*)malloc( _MAX_PATH );
    
	    vReturn=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hOdbcEnv);

	if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
	{//=====分配环境句柄成功
		vReturn=SQLSetEnvAttr(hOdbcEnv,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,SQL_IS_INTEGER);

	   if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
	   {//=====设置环境句柄成功
		   vReturn=SQLAllocHandle(SQL_HANDLE_DBC,hOdbcEnv,&hDbConn);

	       if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
		   {//=====分配连接句柄成功
			   vReturn=SQLSetConnectAttr(hDbConn,5,(void*)SQL_LOGIN_TIMEOUT,0);

	           if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
			   {//=====设置连接句柄成功
				  vReturn=SQLConnect(hDbConn,(SQLCHAR*)szDSN,
		                        SQL_NTS,(SQLCHAR*)szUID,
				                SQL_NTS,(SQLCHAR*)szAuthStr,
				                SQL_NTS);
	              if(vReturn==SQL_SUCCESS||vReturn==SQL_SUCCESS_WITH_INFO)
				  {//=====连接数据库成功
	        	     printf("Connected OK!\n");
                     vReturn = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hDbStmt); 

					 if (vReturn == SQL_SUCCESS || vReturn == SQL_SUCCESS_WITH_INFO) 
					 {
 					    printf("SQLStatement OK!\n");
						//
						if(pingstatus->PingTong==false)
						{
						strcpy(SelectStatementTxt, "Select DevStatus FROM PollingUse WHERE IpAddr='");
						strcat(SelectStatementTxt,(const char*)pingstatus->IP);
						strcat(SelectStatementTxt,"'");
						vReturn = SQLExecDirect(hDbStmt,(unsigned char *)SelectStatementTxt,SQL_NTS);  
						vReturn =SQLBindCol(hDbStmt,1,SQL_C_ULONG,&DevStatus,sizeof(DevStatus),&length[0]);
				
						vReturn=SQLFetch(hDbStmt);
						DevStatus++;

						vReturn=SQLFreeStmt(hDbStmt,SQL_RESET_PARAMS);
					    vReturn = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hDbStmt); 
						strcpy(SelectStatementTxt, "UPDATE PollingUse SET DevStatus=");
                        _itoa(DevStatus,buff,10);
						strcat(SelectStatementTxt,buff);
						strcat(SelectStatementTxt," WHERE IpAddr='");
						strcat(SelectStatementTxt,(const char*)pingstatus->IP);
						strcat(SelectStatementTxt,"'");

                        vReturn = SQLExecDirect(hDbStmt,(unsigned char *)SelectStatementTxt,SQL_NTS);  
						}
						else
						{
						strcpy(SelectStatementTxt, "UPDATE PollingUse SET DevStatus=0 WHERE IpAddr='");
                    	strcat(SelectStatementTxt,(const char*)pingstatus->IP);
						strcat(SelectStatementTxt,"'");

                        vReturn = SQLExecDirect(hDbStmt,(unsigned char *)SelectStatementTxt,SQL_NTS);  
						}
						//
						if(vReturn!=SQL_SUCCESS)
						{
							SQLCHAR SqlState[6];
							SQLINTEGER NativeError;
							SQLCHAR ErrMsg[SQL_MAX_MESSAGE_LENGTH];
							int i=1;
							printf("Error in SQLINSERT:%d \n",vReturn);
							while(SQLGetDiagRec(SQL_HANDLE_DBC,hDbConn,i,SqlState,
								               &NativeError,ErrMsg,sizeof(ErrMsg),NULL)
						 	     !=SQL_NO_DATA)
							    printf("Diag:%d,SQLSTATE:%s NativeError:%d ErrMsg:%s\n",
								        i++,SqlState,NativeError,ErrMsg);
						}
					 }
				  }
				  else
				  {
		              SQLCHAR sqlState[6];
		              SQLINTEGER NativeError;
		              SQLCHAR ErrMsg[SQL_MAX_MESSAGE_LENGTH];
		              int i=1;
		              printf("Error in SQL connect:%d",vReturn);
                      while(SQLGetDiagRec(SQL_HANDLE_DBC,hDbConn,i,sqlState,
			                &NativeError,ErrMsg,sizeof(ErrMsg),NULL)
							!=SQL_NO_DATA)
                          printf("Dialog:%d,sqlstate:%s,NativeError:%d,ErrMsg:%s\n",i++,sqlState,NativeError,ErrMsg);
				  }
			   }
		   }
	   }
	   }
	   vReturn=SQLDisconnect(hDbConn);
	   if(hDbConn!=SQL_NULL_HANDLE)
		  SQLFreeHandle(SQL_HANDLE_DBC,hDbConn);
	   if(hOdbcEnv!=SQL_NULL_HANDLE)
		  SQLFreeHandle(SQL_HANDLE_ENV,hOdbcEnv);
	   free(SelectStatementTxt);
	   In_UpdateDB=false;
	   }
////==================
	   return 1;
}
////////////////////////////
///Ping 代码
//Ping的参数:
//     timeout=5;Bytecount=32;requestcount=2
///*IAN*
////////////////////////////
int Ping(char* IP)
{
	//===返回1：PC存在；返回0：PC不存在
   WSADATA       wsaData;
   SOCKET        sockRaw;
   sockaddr_in   dest;
   sockaddr_in   from;
   char *        dest_ip;
   int           fromlen = sizeof(from);
   hostent *     hp;
   int           bread;
   int           datasize;
   int           reqcnt;
   unsigned int  addr=0;
   USHORT        seq_no = 0;
   char *        icmp_data;
   char *        recvbuf;
   char          timeout[10];
   int           bwrote;
//==decode_resp函数体用的变量
   IpHeader *iphdr;
   IcmpHeader *icmphdr;
   unsigned short iphdrlen;
//==fill_icmp_data函数体用的变量
   IcmpHeader *icmp_hdr;
   char *datapart;//指向数据部分的指针
//==checksum函数体用的变量
   int wDataLength;
   USHORT *lpwIcmpData;
   unsigned long cksum;
   bool PC_EXIST;//标识指定IP是否ping通

/*-----Function Body-------*/
    PC_EXIST=false;//标识指定IP是否ping通

    reqcnt=2;
	strcpy(timeout,"5");

    if (WSAStartup(MAKEWORD(2,1),&wsaData) != 0)
	{
       AfxMessageBox("WSAStartup failed");//GetLastError()
	   return 0;
    }
    sockRaw = socket (AF_INET,SOCK_RAW,IPPROTO_ICMP);
   
    if (sockRaw == INVALID_SOCKET) 
    {
 	   AfxMessageBox("WSASocket() failed");
	   return 0;
	}
    bread = setsockopt(sockRaw,SOL_SOCKET,SO_RCVTIMEO,timeout,sizeof(timeout));
    if(bread == SOCKET_ERROR) 
    {
   	   AfxMessageBox("failed to set recv timeout");
	   return 0;
    }
    bread = setsockopt(sockRaw,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(timeout));
    if(bread == SOCKET_ERROR) 
    {
   	   AfxMessageBox("failed to set send timeout");//WSAGetLastError()
	   return 0;
	}
    memset(&dest,0,sizeof(dest));     //将dest设置为全0
    addr = inet_addr(IP);   //用IP地址的形式
    if(addr==INADDR_NONE)
    {
       hp = gethostbyname(IP);
	   if(!hp)
	   {
  	      memcpy(&(dest.sin_addr),hp->h_addr,hp->h_length);
		  dest.sin_family = hp->h_addrtype;
	   }
	   else
	   {
          AfxMessageBox("Unable to resolve agent address");
		  return 0;
	   }
	}
    else
    {
	   dest.sin_addr.s_addr = addr;
       dest.sin_family = AF_INET;
	}   
    dest_ip = inet_ntoa(dest.sin_addr);//char * dest_ip;
    datasize = 32;
 
    if (datasize<=0) 
 	  datasize = DEF_PACKET_SIZE;
   	
    datasize += sizeof(IcmpHeader); //ICMP包的总长 
    icmp_data = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(MAX_PACKET));
    recvbuf   = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(MAX_PACKET));

    if (!icmp_data) 
    {
 	   AfxMessageBox("HeapAlloc failed");//GetLastError()
	   return 0;
    }
 
    memset(icmp_data,0,MAX_PACKET);

    //====fill_icmp_data函数体begin====fill_icmp_data(icmp_data,datasize);
    icmp_hdr = (IcmpHeader*)icmp_data;
    icmp_hdr->i_type = ICMP_ECHO;
    icmp_hdr->i_code = 0;
    icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
    icmp_hdr->i_cksum = 0;
    datapart = icmp_data + sizeof(IcmpHeader);
    memset(datapart,'E', datasize - sizeof(IcmpHeader));//填充数据部分的值为E
    //====fill_icmp_data函数体end=============

	//开始Ping
    for(int i=0;i<reqcnt;i++) 
	{
 	   ((IcmpHeader*)icmp_data)->i_cksum = 0;
 	   ((IcmpHeader*)icmp_data)->timestamp = GetTickCount();

       //====checksum函数体begin====((IcmpHeader*)icmp_data)->i_cksum = checksum(icmp_data, datasize);

       wDataLength=datasize;
       lpwIcmpData=(USHORT*)icmp_data;
       cksum=0L;
       while(wDataLength >1) 
	   {
	       cksum+=*lpwIcmpData++;
	       wDataLength -=sizeof(USHORT);//以16bits为单位，相邻字求和(16位bits流)
	   }
       if(wDataLength==1) 
   	      cksum += *(UCHAR*)lpwIcmpData;
       cksum = (cksum >> 16) + (cksum & 0xffff);
       cksum += (cksum >>16);
       ((IcmpHeader*)icmp_data)->i_cksum =(USHORT)(~cksum);

      //====checksum函数体end====

	   bwrote = sendto(sockRaw,icmp_data,datasize,0,(struct sockaddr*)&dest,sizeof(dest));//NO_FLAGS--0
       if (bwrote == SOCKET_ERROR)
	      continue;
	   bread = recvfrom(sockRaw,recvbuf,MAX_PACKET,0,(struct sockaddr*)&from,&fromlen);
 	   if (bread == SOCKET_ERROR)
	   {
 	      if (WSAGetLastError() == WSAETIMEDOUT) 
 		      continue;
		  continue;
	   }
       else
	   {
      //====decode_resp函数体begin==decode_resp(recvbuf,bread,&from);

	      iphdr = (IpHeader *)recvbuf;
	      iphdrlen = iphdr->h_len * 4 ; // number of 32-bit words *4 = bytes
	      icmphdr = (IcmpHeader*)(recvbuf + iphdrlen);
	      if (icmphdr->i_type != ICMP_ECHOREPLY) 
			  continue;
	      if(icmphdr->i_id != (USHORT)GetCurrentProcessId()) 
			 break;
 		  PC_EXIST=true;
	      break;
      //====decode_resp函数体end====	
	   }
	}
	//ping结束
    if(PC_EXIST==true)
	{
		closesocket(sockRaw);
		return 1;
	}
	else
	{
		closesocket(sockRaw);
		return 0;
	}
}
