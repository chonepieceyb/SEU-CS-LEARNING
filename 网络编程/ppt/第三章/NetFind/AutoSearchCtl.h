#if !defined(AFX_AUTOSEARCHCTL_H__D44628C8_9282_11D3_B19B_0000E87780F5__INCLUDED_)
#define AFX_AUTOSEARCHCTL_H__D44628C8_9282_11D3_B19B_0000E87780F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// AutoSearchCtl.h : Declaration of the CAutoSearchCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CAutoSearchCtrl : See AutoSearchCtl.cpp for implementation.
#define WM_USER_PING_SUCC (WM_USER + 1)
#define WM_USER_PING_FAIL (WM_USER + 2)
#define WM_USER_GET_SUCC  (WM_USER + 3)
#define WM_USER_GET_FAIL  (WM_USER + 4)
class CAutoSearchCtrl : public COleControl
{
	DECLARE_DYNCREATE(CAutoSearchCtrl)

// Constructor
public:
	CAutoSearchCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoSearchCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CAutoSearchCtrl();

	DECLARE_OLECREATE_EX(CAutoSearchCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CAutoSearchCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CAutoSearchCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CAutoSearchCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CAutoSearchCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CAutoSearchCtrl)
	afx_msg long BeginSearch(LPCTSTR Param, long DevNo);
	afx_msg long PCInfoDelAll();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CAutoSearchCtrl)
	void FirePingFail()
		{FireEvent(eventidPingFail,EVENT_PARAM(VTS_NONE));}
	void FirePingOver(long DevNo)
		{FireEvent(eventidPingOver,EVENT_PARAM(VTS_I4), DevNo);}
	void FireGetOver(long DevNo)
		{FireEvent(eventidGetOver,EVENT_PARAM(VTS_I4), DevNo);}
	void FireGetFail(long DevNo)
		{FireEvent(eventidGetFail,EVENT_PARAM(VTS_I4), DevNo);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CAutoSearchCtrl)
	dispidBeginSearch = 1L,
	dispidPCInfoDelAll = 2L,
	eventidPingFail = 1L,
	eventidPingOver = 2L,
	eventidGetOver = 3L,
	eventidGetFail = 4L,
	//}}AFX_DISP_ID
	};
	LRESULT OnPingSucc(WPARAM wParam, LPARAM lParam);
	LRESULT OnPingFail(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetSucc(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetFail(WPARAM wParam, LPARAM lParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOSEARCHCTL_H__D44628C8_9282_11D3_B19B_0000E87780F5__INCLUDED)
