// BannerView.cpp : implementation file
//

#include "stdafx.h"
#include "Editor.h"
#include "BannerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBannerView dialog


CBannerView::CBannerView(CWnd* pParent /*=NULL*/)
	: CDialog(CBannerView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBannerView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBannerView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBannerView)
	DDX_Control(pDX, IDC_CUSTOM1, CBV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBannerView, CDialog)
	//{{AFX_MSG_MAP(CBannerView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBannerView message handlers

void CBannerView::OnSize(UINT nType, int cx, int cy) 
{
	if (cy<50) return;

	CDialog::OnSize(nType, cx, cy);

	if (::IsWindow(CBV.m_hWnd))CBV.SetWindowPos(0,0,0,cx,cy,SWP_DRAWFRAME|SWP_NOZORDER);
	
	// TODO: Add your message handler code here
}
