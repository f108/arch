// AddNewFontDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Editor.h"
#include "AddNewFontDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddNewFontDlg dialog


CAddNewFontDlg::CAddNewFontDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddNewFontDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddNewFontDlg)
	m_FontName = _T("");
	m_HS = 0;
	m_VS = 0;
	//}}AFX_DATA_INIT
}


void CAddNewFontDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddNewFontDlg)
	DDX_Text(pDX, IDC_EDIT1, m_FontName);
	DDX_Text(pDX, IDC_EDIT2, m_HS);
	DDX_Text(pDX, IDC_EDIT3, m_VS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddNewFontDlg, CDialog)
	//{{AFX_MSG_MAP(CAddNewFontDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddNewFontDlg message handlers
int CAddNewFontDlg::DoModal(CString &str, DWORD &HS, DWORD &VS)
{
	int res = CDialog::DoModal();
	if (res!=IDOK) return res;
	str = m_FontName;
	HS = m_HS;
	VS = m_VS;
	return res;
};
