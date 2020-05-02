// PollingCtl.cpp : Implementation of the CPollingCtrl ActiveX Control class.

#include "stdafx.h"
#include "NetFind.h"
#include "PollingCtl.h"
#include "PollingPpg.h"
#include "ZyFunc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CPollingCtrl, COleControl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPollingCtrl, COleControl)
	//{{AFX_MSG_MAP(CPollingCtrl)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_POLL_FAIL, OnPollFail)

	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPollingCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CPollingCtrl)
	DISP_FUNCTION(CPollingCtrl, "BeginPoll", BeginPoll, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CPollingCtrl, "StopPolling", StopPolling, VT_EMPTY, VTS_NONE)
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_APPEARANCE()
	DISP_STOCKPROP_BORDERSTYLE()
	DISP_STOCKPROP_ENABLED()
	DISP_STOCKPROP_FONT()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CPollingCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CPollingCtrl, COleControl)
	//{{AFX_EVENT_MAP(CPollingCtrl)
	EVENT_CUSTOM("AbortPoll", FireAbortPoll, VTS_I4)
	EVENT_CUSTOM("PollFail", FirePollFail, VTS_I2)
	EVENT_STOCK_CLICK()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CPollingCtrl, 1)
	PROPPAGEID(CPollingPropPage::guid)
END_PROPPAGEIDS(CPollingCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPollingCtrl, "NETFIND.PollingCtrl.1",
	0xd44628ba, 0x9282, 0x11d3, 0xb1, 0x9b, 0, 0, 0xe8, 0x77, 0x80, 0xf5)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPollingCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPolling =
		{ 0xd44628b8, 0x9282, 0x11d3, { 0xb1, 0x9b, 0, 0, 0xe8, 0x77, 0x80, 0xf5 } };
const IID BASED_CODE IID_DPollingEvents =
		{ 0xd44628b9, 0x9282, 0x11d3, { 0xb1, 0x9b, 0, 0, 0xe8, 0x77, 0x80, 0xf5 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPollingOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPollingCtrl, IDS_POLLING, _dwPollingOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::CPollingCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPollingCtrl

BOOL CPollingCtrl::CPollingCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_POLLING,
			IDB_POLLING,
			afxRegApartmentThreading,
			_dwPollingOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::CPollingCtrl - Constructor

CPollingCtrl::CPollingCtrl()
{
	InitializeIIDs(&IID_DPolling, &IID_DPollingEvents);

	// TODO: Initialize your control's instance data here.

}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::~CPollingCtrl - Destructor

CPollingCtrl::~CPollingCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::OnDraw - Drawing function

void CPollingCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DoSuperclassPaint(pdc, rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::DoPropExchange - Persistence support

void CPollingCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::OnResetState - Reset control to default state

void CPollingCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::AboutBox - Display an "About" box to the user

void CPollingCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_POLLING);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CPollingCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("BUTTON");
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::IsSubclassedControl - This is a subclassed control

BOOL CPollingCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl::OnOcmCommand - Handle command messages

LRESULT CPollingCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
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
// CPollingCtrl message handlers
void CPollingCtrl::BeginPoll() 
{
   int i;

   Read_TimeConfig(TimeSet,TimeSetNo);
   Read_PollingUse(TimeSet,TimeSetNo,IpGroup,Timer);
   for(i=0;i<TimeSetNo;i++)
	  SetTimer(i,Timer[i].TimeSet,NULL);//定义的定时器标志从0到TimeSetNo
}

UINT ThreadPing(LPVOID pParam)
{
	if(Thread_In)
		Sleep(10);
	else
	{
		PingStatus* pingstatus;

		Thread_In=true;
	    PCIP * pcip=(PCIP *)pParam;
	    for (int i=0;i<pcip->IPNO;i++)
		{
/*		    if(Ping(pcip->IP[i])==0)//没有PING通
			{
			    CWinThread* p;
				p=new CWinThread;
				p=AfxBeginThread(Update_PollingUse,pcip->IP[i]);
                
			    SendMessage(pcip->hWnd,WM_USER_POLL_FAIL,pcip->IPNO,0);
			}
*/

		    if(Ping(pcip->IP[i])==0)//没有PING通
			{
  	            pingstatus=new PingStatus;

				strcpy(pingstatus->IP,pcip->IP[i]);
				pingstatus->PingTong=false;
			}
			else
			{
				pingstatus=new PingStatus;
				strcpy(pingstatus->IP,pcip->IP[i]);
				pingstatus->PingTong=true;
			}
		    CWinThread* p;
			p=new CWinThread;
			p=AfxBeginThread(Update_PollingUse,pingstatus);
		    SendMessage(pcip->hWnd,WM_USER_POLL_FAIL,pcip->IPNO,0);
		}
		Thread_In=false;
	}
	return 1;
}

void CPollingCtrl::OnTimer(UINT nIDEvent) 
{
//In_Time全局变量
	if(!In_Time)
	{
		In_Time=true;

	    int i;
		CWinThread* p;
		PCIP *pcip;//{char* IP[100]; int IPNO; HWND hWnd;}传给线程该时间段轮寻的IP组及控件的句柄
		pcip=new PCIP;
		for(i=0;i<Timer[nIDEvent].IpNoForThis;i++)
		{
			pcip->IP[i]=new char[20];
			strcpy(pcip->IP[i],IpGroup[Timer[nIDEvent].Pointer][i]);
		}
		pcip->IPNO=i;
	    hWnd=GetSafeHwnd();//CWnd::GetSafeHwnd()获得该类的窗口句柄
		pcip->hWnd=hWnd;
		p=new CWinThread;
		p=AfxBeginThread(ThreadPing,pcip);
		In_Time=false;
	}
	else
		FireAbortPoll(Timer[nIDEvent].TimeSet);

	COleControl::OnTimer(nIDEvent);
}

void CPollingCtrl::StopPolling() 
{
	for(int i=0;i<TimeSetNo;i++)
		KillTimer(i);
}

LRESULT CPollingCtrl::OnPollFail(WPARAM wParam, LPARAM lParam)
{
    UINT IpNo=LOWORD(wParam);
	
	FirePollFail(IpNo);
	return 1;
}
