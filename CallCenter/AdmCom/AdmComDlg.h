// AdmComDlg.h : header file
//

#if !defined(AFX_ADMCOMDLG_H__18D097BB_FC4C_4533_88FE_8BE55149EB09__INCLUDED_)
#define AFX_ADMCOMDLG_H__18D097BB_FC4C_4533_88FE_8BE55149EB09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAdmComDlg dialog

#include "ServiceGroupDlg.h"

class CAdmComDlg : public CDialog
{
// Construction
public:
	CAdmComDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAdmComDlg)
	enum { IDD = IDD_ADMCOM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdmComDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CAdmComDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADMCOMDLG_H__18D097BB_FC4C_4533_88FE_8BE55149EB09__INCLUDED_)
