// RMODlg.h : header file
//

#if !defined(AFX_RMODLG_H__E0E39561_E5F1_497B_A004_9908618A24A2__INCLUDED_)
#define AFX_RMODLG_H__E0E39561_E5F1_497B_A004_9908618A24A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRMODlg dialog

class CRMODlg : public CDialog
{
// Construction
public:
	CRMODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRMODlg)
	enum { IDD = IDD_RMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRMODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMODLG_H__E0E39561_E5F1_497B_A004_9908618A24A2__INCLUDED_)
