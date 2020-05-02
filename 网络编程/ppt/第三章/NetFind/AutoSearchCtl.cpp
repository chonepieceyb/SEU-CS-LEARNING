// AutoSearchCtl.cpp : Implementation of the CAutoSearchCtrl ActiveX Control class.

#include "stdafx.h"
#include "NetFind.h"
#include "AutoSearchCtl.h"
#include "AutoSearchPpg.h"

//==================
#include "StructDef.h"
//==线程同步信号量
      //
int PingEntry=0;
int SnmpGetEntry=0;
      //
//================
extern "C" __declspec(dllimport) void Insert_A_Record(char* field1,char* field2);
extern "C" __declspec(dllimport) void DevInsert_A_Record(char* field1,
													     char* field2,
													     char* field3,
													     char* field4,
													     char* field5,
													     char* field6,
													     char* field7);
extern "C" __declspec(dllimport) int SnmpGet(Input &Request,Output &Response);
extern "C" __declspec(dllimport) int Delete_All_Record();
//==================
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CAutoSearchCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CAutoSearchCtrl, COleControl)
	//{{AFX_MSG_MAP(CAutoSearchCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_PING_SUCC, OnPingSucc)
	ON_MESSAGE(WM_USER_PING_FAIL, OnPingFail)
	ON_MESSAGE(WM_USER_GET_SUCC, OnGetSucc)
	ON_MESSAGE(WM_USER_GET_FAIL, OnGetFail)

	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CAutoSearchCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CAutoSearchCtrl)
	DISP_FUNCTION(CAutoSearchCtrl, "BeginSearch", BeginSearch, VT_I4, VTS_BSTR VTS_I4)
	DISP_FUNCTION(CAutoSearchCtrl, "PCInfoDelAll", PCInfoDelAll, VT_I4, VTS_NONE)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_APPEARANCE()
	DISP_STOCKPROP_ENABLED()
	DISP_STOCKPROP_FONT()
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_BORDERSTYLE()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CAutoSearchCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CAutoSearchCtrl, COleControl)
	//{{AFX_EVENT_MAP(CAutoSearchCtrl)
	EVENT_CUSTOM("PingFail", FirePingFail, VTS_NONE)
	EVENT_CUSTOM("PingOver", FirePingOver, VTS_I4)
	EVENT_CUSTOM("GetOver", FireGetOver, VTS_I4)
	EVENT_CUSTOM("GetFail", FireGetFail, VTS_I4)
	EVENT_STOCK_CLICK()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CAutoSearchCtrl, 1)
	PROPPAGEID(CAutoSearchPropPage::guid)
END_PROPPAGEIDS(CAutoSearchCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CAutoSearchCtrl, "NETFIND.AutoSearchCtrl.1",
	0xd44628b6, 0x9282, 0x11d3, 0xb1, 0x9b, 0, 0, 0xe8, 0x77, 0x80, 0xf5)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CAutoSearchCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DAutoSearch =
		{ 0xd44628b4, 0x9282, 0x11d3, { 0xb1, 0x9b, 0, 0, 0xe8, 0x77, 0x80, 0xf5 } };
const IID BASED_CODE IID_DAutoSearchEvents =
		{ 0xd44628b5, 0x9282, 0x11d3, { 0xb1, 0x9b, 0, 0, 0xe8, 0x77, 0x80, 0xf5 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwAutoSearchOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CAutoSearchCtrl, IDS_AUTOSEARCH, _dwAutoSearchOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::CAutoSearchCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CAutoSearchCtrl

BOOL CAutoSearchCtrl::CAutoSearchCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_AUTOSEARCH,
			IDB_AUTOSEARCH,
			afxRegApartmentThreading,
			_dwAutoSearchOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::CAutoSearchCtrl - Constructor

CAutoSearchCtrl::CAutoSearchCtrl()
{
	InitializeIIDs(&IID_DAutoSearch, &IID_DAutoSearchEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::~CAutoSearchCtrl - Destructor

CAutoSearchCtrl::~CAutoSearchCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::OnDraw - Drawing function

void CAutoSearchCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DoSuperclassPaint(pdc, rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::DoPropExchange - Persistence support

void CAutoSearchCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::OnResetState - Reset control to default state

void CAutoSearchCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::AboutBox - Display an "About" box to the user

void CAutoSearchCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_AUTOSEARCH);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CAutoSearchCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("BUTTON");
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::IsSubclassedControl - This is a subclassed control

BOOL CAutoSearchCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl::OnOcmCommand - Handle command messages

LRESULT CAutoSearchCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// 线程入口
UINT PingFuc(LPVOID pParam)
{
	//===动态加载DLL函数(显式方式)
	HMODULE hPCInfoDll;
	int(*PingA)(PingInfo* p);
	hPCInfoDll = ::LoadLibrary("PCInfoDll");
	ASSERT(hPCInfoDll != NULL);
	PingA= (int(*)(PingInfo*))::GetProcAddress(hPCInfoDll,"Ping");

	if(PingEntry!=0)//====对Ping模块加锁：PingEntry
	{
		while(PingEntry!=0)
		{ 
			Sleep(10); 
		}
  	    PingEntry=1;
	}
	else
		PingEntry=1;
    PingInfo* Param=(PingInfo*)pParam;
	int pcexist; //Ping函数的返回值
	pcexist=(* PingA)(Param);

	if(pcexist==1)
	{//PING通
		SendMessage(Param->hWnd,WM_USER_PING_SUCC,Param->DevNo,0);
		////////////
		    //对SnmpGet模块加锁：SnmpGetEntry
		if(SnmpGetEntry!=0)
		{
		   while(SnmpGetEntry!=0)
		   	  Sleep(10); 
		   SnmpGetEntry=1;
		}
	    else
		   SnmpGetEntry=1;
		    //
		////////////

	    //====SNMP-Get函数体begin====
	    Input Request;
        Output Response;
		bool IS_SNMP=false;
        UINT k;
		HWND hWnd;
		UINT DevNo;
		
	    Request.pcIp=Param->agent;//在下一Ping线程修改Param->agent前
        hWnd=Param->hWnd;
        DevNo=Param->DevNo;//第几个设备

       	PingEntry=0;//在Ping通情况下解PING代码段的锁

	    Request.pcCommunity="public";
	    Request.uTimeout=500;
	    Request.uRetries=2;
	    Request.uOidCount=6;
	    Request.pcOidType=(char*)malloc(_MAX_PATH);
	    for(k=0;k<=5;k++)
		{
	       Request.apcOid[k]=(char*)malloc(_MAX_PATH);
	       Response.apcValue[k]=(char*)malloc(_MAX_PATH);
	       Response.apcOid[k]=(char*)malloc(_MAX_PATH);
		}
		//系统组的对象
        strcpy(Request.apcOid[0],".1.3.6.1.2.1.1.1.0");//系统描述
	    strcpy(Request.apcOid[1],".1.3.6.1.2.1.1.2.0");//系统OID
	    strcpy(Request.apcOid[2],".1.3.6.1.2.1.1.3.0");//系统启动时间
	    strcpy(Request.apcOid[3],".1.3.6.1.2.1.1.4.0");//系统联系人
	    strcpy(Request.apcOid[4],".1.3.6.1.2.1.1.5.0");//系统名称
	    strcpy(Request.apcOid[5],".1.3.6.1.2.1.1.6.0");//系统位置

        k=SnmpGet(Request,Response);
	    if(k==103)
			IS_SNMP=false;
	    else
			IS_SNMP=true;
		if(IS_SNMP)
		{
			SendMessage(Param->hWnd,WM_USER_GET_SUCC,DevNo,0);
			Insert_A_Record(Request.pcIp,"yes");
			DevInsert_A_Record(  Request.pcIp,
				                 Response.apcValue[0],
							     Response.apcValue[1],
							     Response.apcValue[2],
							     Response.apcValue[3],
							     Response.apcValue[4],
							     Response.apcValue[5]
							   );
		}
		else
		{
			SendMessage(Param->hWnd,WM_USER_GET_FAIL,DevNo,0);
			Insert_A_Record(Request.pcIp,"no");
		}
	   free(Request.pcOidType);
	   for(k=0;k<=5;k++)
	   {
	      free(Request.apcOid[k]);
	      free(Response.apcOid[k]);
	      free(Response.apcValue[k]);
	   }
	   SnmpGetEntry=0;//解SnmpGet模块的锁
       //====SNMP-Get函数体end====
	}
	else
	{
		SendMessage(Param->hWnd,WM_USER_PING_FAIL,0,0);
		PingEntry=0;//在Ping不通情况下解PING代码段的锁
	}
	return 1;
}
/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl message handlers

LRESULT CAutoSearchCtrl::OnPingSucc(WPARAM wParam, LPARAM lParam)
{
	UINT DevNo=LOWORD(wParam);
    FirePingOver(DevNo);
	return 1;
}
LRESULT CAutoSearchCtrl::OnPingFail(WPARAM, LPARAM)
{
	FirePingFail();
	return 1;
}
LRESULT CAutoSearchCtrl::OnGetSucc(WPARAM wParam, LPARAM lParam)
{
	UINT DevNo=LOWORD(wParam);
	FireGetOver(DevNo);
	return 1;
}
LRESULT CAutoSearchCtrl::OnGetFail(WPARAM wParam, LPARAM lParam)
{
	UINT DevNo=LOWORD(wParam);
	FireGetFail(DevNo);
	return 1;
}

long CAutoSearchCtrl::BeginSearch(LPCTSTR Param, long DevNo) 
{
	HWND hWnd;
	hWnd=GetSafeHwnd();//CWnd::GetSafeHwnd()获得该类的窗口句柄

	PingInfo* pinginfo;
	CWinThread* p;

    pinginfo= new PingInfo;
	strcpy(pinginfo->timeout,"5");
    strcpy(pinginfo->ByteCount,"32");
    strcpy(pinginfo->requestcount,"1");

	pinginfo->hWnd=hWnd;
    strcpy(pinginfo->agent,Param);
	pinginfo->DevNo=DevNo;

    p=new CWinThread;
	p=AfxBeginThread(PingFuc,pinginfo);

	return 1;
}

long CAutoSearchCtrl::PCInfoDelAll() 
{
	return Delete_All_Record();
}
