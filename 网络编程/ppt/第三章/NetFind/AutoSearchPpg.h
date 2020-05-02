#if !defined(AFX_AUTOSEARCHPPG_H__D44628CA_9282_11D3_B19B_0000E87780F5__INCLUDED_)
#define AFX_AUTOSEARCHPPG_H__D44628CA_9282_11D3_B19B_0000E87780F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// AutoSearchPpg.h : Declaration of the CAutoSearchPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CAutoSearchPropPage : See AutoSearchPpg.cpp.cpp for implementation.

class CAutoSearchPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CAutoSearchPropPage)
	DECLARE_OLECREATE_EX(CAutoSearchPropPage)

// Constructor
public:
	CAutoSearchPropPage();

// Dialog Data
	//{{AFX_DATA(CAutoSearchPropPage)
	enum { IDD = IDD_PROPPAGE_AUTOSEARCH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CAutoSearchPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOSEARCHPPG_H__D44628CA_9282_11D3_B19B_0000E87780F5__INCLUDED)
