#if !defined(AFX_POLLINGCTL_H__D44628CD_9282_11D3_B19B_0000E87780F5__INCLUDED_)
#define AFX_POLLINGCTL_H__D44628CD_9282_11D3_B19B_0000E87780F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PollingCtl.h : Declaration of the CPollingCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CPollingCtrl : See PollingCtl.cpp for implementation.
#define MAX_DEVICENUMBER_TO_POLLING 100           //一次轮询开始允许的设备最大数100
#define ALLOW_DEFINED_TIMENUMBER_FOR_POLLING 20    //允许定义的定时器的个数20
typedef struct
{
	long TimeSet;
	int Pointer;
	int IpNoForThis;
}TM;
typedef struct
{
	char *IP[MAX_DEVICENUMBER_TO_POLLING];
	int   IPNO;
	HWND  hWnd;
}PCIP;

bool In_Time=false;
bool Thread_In=false;

#define WM_USER_POLL_FAIL (WM_USER + 5)

class CPollingCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPollingCtrl)

// Constructor
public:
	CPollingCtrl();
    
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPollingCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CPollingCtrl();

	DECLARE_OLECREATE_EX(CPollingCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB  (CPollingCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS (CPollingCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE  (CPollingCtrl)	  // Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CPollingCtrl)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CPollingCtrl)
	afx_msg void BeginPoll();
	afx_msg void StopPolling();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CPollingCtrl)
	void FireAbortPoll(long PollPeriod)
		{FireEvent(eventidAbortPoll,EVENT_PARAM(VTS_I4), PollPeriod);}
	void FirePollFail(short IPNO)
		{FireEvent(eventidPollFail,EVENT_PARAM(VTS_I2), IPNO);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CPollingCtrl)
	dispidBeginPoll = 1L,
	dispidStopPolling = 2L,
	eventidAbortPoll = 1L,
	eventidPollFail = 2L,
	//}}AFX_DISP_ID
	};
public:
   int TimeSetNo;
   int TimeSet[ALLOW_DEFINED_TIMENUMBER_FOR_POLLING];
   char* IpGroup[ALLOW_DEFINED_TIMENUMBER_FOR_POLLING][MAX_DEVICENUMBER_TO_POLLING];
   TM Timer[ALLOW_DEFINED_TIMENUMBER_FOR_POLLING];
   HWND hWnd;

public:
	LRESULT OnPollFail(WPARAM wParam, LPARAM lParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLLINGCTL_H__D44628CD_9282_11D3_B19B_0000E87780F5__INCLUDED)
