#if !defined(AFX_SLDLG_H__D949BE4A_E14B_4F2F_A3FE_4D4D5944F7C4__INCLUDED_)
#define AFX_SLDLG_H__D949BE4A_E14B_4F2F_A3FE_4D4D5944F7C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SLDLG.h : header file
//

#include "..\TZSSString.h"
#include "..\TUIList.h"

struct SLST
{
	unsigned SG;
	TZSuperShortString Comment;
};

/////////////////////////////////////////////////////////////////////////////
// CSLDLG dialog

class CSLDLG : public CPropertyPage
{
	DECLARE_DYNCREATE(CSLDLG)

// Construction
public:
	CSLDLG();
	~CSLDLG();

// Dialog Data
	//{{AFX_DATA(CSLDLG)
	enum { IDD = IDD_SLDLG };
	CEdit	CE;
	CComboBox	CCB;
//	CListBox	m_List;
	//}}AFX_DATA

	void SendData(void);

SLST SLData[12];

	void DoEditObject(void);
	void SetSLProfile(TSNPData *TND);
	int LINEINDEX;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSLDLG)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSLDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelendokCombo1();
	afx_msg void OnSelendcancelCombo1();
	afx_msg void OnKillfocusEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLDLG_H__D949BE4A_E14B_4F2F_A3FE_4D4D5944F7C4__INCLUDED_)
