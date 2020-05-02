// AutoSearchPpg.cpp : Implementation of the CAutoSearchPropPage property page class.

#include "stdafx.h"
#include "NetFind.h"
#include "AutoSearchPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CAutoSearchPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CAutoSearchPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CAutoSearchPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CAutoSearchPropPage, "NETFIND.AutoSearchPropPage.1",
	0xd44628b7, 0x9282, 0x11d3, 0xb1, 0x9b, 0, 0, 0xe8, 0x77, 0x80, 0xf5)


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchPropPage::CAutoSearchPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CAutoSearchPropPage

BOOL CAutoSearchPropPage::CAutoSearchPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_AUTOSEARCH_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchPropPage::CAutoSearchPropPage - Constructor

CAutoSearchPropPage::CAutoSearchPropPage() :
	COlePropertyPage(IDD, IDS_AUTOSEARCH_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CAutoSearchPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchPropPage::DoDataExchange - Moves data between page and properties

void CAutoSearchPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CAutoSearchPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CAutoSearchPropPage message handlers
