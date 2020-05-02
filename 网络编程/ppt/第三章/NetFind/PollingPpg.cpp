// PollingPpg.cpp : Implementation of the CPollingPropPage property page class.

#include "stdafx.h"
#include "NetFind.h"
#include "PollingPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPollingPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPollingPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CPollingPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPollingPropPage, "NETFIND.PollingPropPage.1",
	0xd44628bb, 0x9282, 0x11d3, 0xb1, 0x9b, 0, 0, 0xe8, 0x77, 0x80, 0xf5)


/////////////////////////////////////////////////////////////////////////////
// CPollingPropPage::CPollingPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPollingPropPage

BOOL CPollingPropPage::CPollingPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_POLLING_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CPollingPropPage::CPollingPropPage - Constructor

CPollingPropPage::CPollingPropPage() :
	COlePropertyPage(IDD, IDS_POLLING_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CPollingPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CPollingPropPage::DoDataExchange - Moves data between page and properties

void CPollingPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CPollingPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CPollingPropPage message handlers
