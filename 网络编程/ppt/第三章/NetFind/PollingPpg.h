#if !defined(AFX_POLLINGPPG_H__D44628CF_9282_11D3_B19B_0000E87780F5__INCLUDED_)
#define AFX_POLLINGPPG_H__D44628CF_9282_11D3_B19B_0000E87780F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PollingPpg.h : Declaration of the CPollingPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CPollingPropPage : See PollingPpg.cpp.cpp for implementation.

class CPollingPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPollingPropPage)
	DECLARE_OLECREATE_EX(CPollingPropPage)

// Constructor
public:
	CPollingPropPage();

// Dialog Data
	//{{AFX_DATA(CPollingPropPage)
	enum { IDD = IDD_PROPPAGE_POLLING };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CPollingPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLLINGPPG_H__D44628CF_9282_11D3_B19B_0000E87780F5__INCLUDED)
