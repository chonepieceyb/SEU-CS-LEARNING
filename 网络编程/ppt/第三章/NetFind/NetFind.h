#if !defined(AFX_NETFIND_H__D44628C0_9282_11D3_B19B_0000E87780F5__INCLUDED_)
#define AFX_NETFIND_H__D44628C0_9282_11D3_B19B_0000E87780F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// NetFind.h : main header file for NETFIND.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetFindApp : See NetFind.cpp for implementation.

class CNetFindApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETFIND_H__D44628C0_9282_11D3_B19B_0000E87780F5__INCLUDED)
