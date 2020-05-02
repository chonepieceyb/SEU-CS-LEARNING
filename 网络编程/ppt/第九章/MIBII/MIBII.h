#ifdef MIBII_EXPORTS
#define MIBII_API __declspec(dllexport)
#else
#define MIBII_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <windows.h>

#define RETRIES		3			//连接尝试次数
// Buffers and pipe symbolic constants.
#define TIME_OUT			0		//设定超时时间
#define LINE_LEN			80		//设定行长度
#define NAME_SIZE			25		//设定管道名长度
#define BYTES_READ			1000	//
#define IN_BUF_SIZE			1000
#define BYTES_WRITE			1000
#define OUT_BUF_SIZE		1000
#define MAX_PIPE_INSTANCES	100

typedef struct MIBIIPortTablePointer{
	unsigned int ifIndex;	//端口索引
	unsigned int ifSpeed;	//端口操作方式
	unsigned int ifOperStatus;	//端口操作状态
	unsigned int ifInOctets;	//ATM信令操作状态
	unsigned int ifInUcastPkts;
	unsigned int ifInNUcastPkts;
	unsigned int ifInDiscards;
	unsigned int ifInErrors;
	unsigned int ifOutOctets;
	unsigned int ifOutUcastPkts;
	unsigned int ifOutNUcastPkts;
	unsigned int ifOutDiscards;
	unsigned int ifOutErrors;
	unsigned int ifOutQLen;
	struct MIBIIPortTablePointer * pNext;
}MIBIIPortTable;

typedef struct {
	int IfNumber;
	MIBIIPortTable TableParam;
}AgentParam;

typedef struct ResultPortPointer{
	double ttl;				//端口吞吐率
	double lyl;				//端口连线利用率
	double srdql;			//输入丢弃率
	double scdql;			//输出丢弃率
	double srcwl;			//输入错误率
	double sccwl;			//输出错误率
	struct ResultPortPointer * pNext;
}ResultParam;	//结果参数类型

typedef struct{
	SQLDOUBLE	lylValve;		//连线利用率的阀值
	SQLDOUBLE	srdqlValve;		//输入丢弃率的阀值
	SQLDOUBLE	scdqlValve;		//输出丢弃率的阀值
	SQLDOUBLE	srcwlValve;		//输入错误率的阀值
	SQLDOUBLE	sccwlValve;		//输出错误率的阀值
}ParamValve;	//阀值参数类型

typedef struct{
	SQLINTEGER	TimeOut;		//ATM端口连线利用率的阀值
	SQLINTEGER	TimeSpace;		//ATM进端口的信元丢弃率的阀值
	SQLCHAR 	Community[50];	//ATM出端口的信元丢弃率的阀值
}OperParam;		//阀值参数类型

typedef struct{
	int		gzPort;				//出错端口
	int		gzID;				//出错ID
}FaultUnit;

MIBII_API int Begin_Collect( char * strIP, char * strLocalIP, int *Flag );

int ProvideAlarm();
