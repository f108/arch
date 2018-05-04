// SymbolEditor.cpp : implementation file
//

#include "stdafx.h"
#include "Editor.h"
#include "SymbolEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSymbolEditor dialog


CSymbolEditor::CSymbolEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CSymbolEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSymbolEditor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	CMV.ChangeAttr(CA_NOTIFY_CHANGEIMAGE);
}


void CSymbolEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSymbolEditor)
	DDX_Control(pDX, IDC_EDIT1, m_Text);
	DDX_Control(pDX, IDC_CUSTOM1, CMV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSymbolEditor, CDialog)
	//{{AFX_MSG_MAP(CSymbolEditor)
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSymbolEditor message handlers
void CSymbolEditor::SetParam(const char *SmbInfo, int _HS, int _VS, char *buf)
{
	if (SmbInfo!=NULL) m_Text.SetWindowText(SmbInfo);
	CMV.Init(_HS, _VS, buf);
	if (CMV.IsWindowVisible()) CMV.RedrawWindow();
}

void CSymbolEditor::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow==SW_HIDE) CMV.Init(0, 0, NULL);
	// TODO: Add your message handler code here
	
}

void CSymbolEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (0x30&nFlags)
	{
		GetParent()->SendMessage(WM_MEASUREITEM, 0, (WPARAM)&point);
	};
	
	CDialog::OnLButtonDown(nFlags, point);
}
