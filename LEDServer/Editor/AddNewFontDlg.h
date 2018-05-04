#if !defined(AFX_ADDNEWFONTDLG_H__55A784B0_573E_4BBF_BBF5_2B355D3738CE__INCLUDED_)
#define AFX_ADDNEWFONTDLG_H__55A784B0_573E_4BBF_BBF5_2B355D3738CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddNewFontDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddNewFontDlg dialog

class CAddNewFontDlg : public CDialog
{
// Construction
public:
	CAddNewFontDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddNewFontDlg)
	enum { IDD = IDD_ADDNEWFONT };
	CString	m_FontName;
	int		m_HS;
	int		m_VS;
	//}}AFX_DATA

	int DoModal(CString &str, DWORD &HS, DWORD &VS);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddNewFontDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddNewFontDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDNEWFONTDLG_H__55A784B0_573E_4BBF_BBF5_2B355D3738CE__INCLUDED_)
