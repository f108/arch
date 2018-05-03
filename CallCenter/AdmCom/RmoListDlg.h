#if !defined(AFX_RMOLISTDLG_H__7D7B8DD0_C6D9_4B0A_9C84_8CAAD1CC6D7B__INCLUDED_)
#define AFX_RMOLISTDLG_H__7D7B8DD0_C6D9_4B0A_9C84_8CAAD1CC6D7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RmoListDlg.h : header file
//
#include "..\TZSSString.h"
#include "..\TUIList.h"
/////////////////////////////////////////////////////////////////////////////
// CRmoListDlg dialog

class CRmoListDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CRmoListDlg)

// Construction
public:
	CRmoListDlg();
	~CRmoListDlg();

// Dialog Data
	//{{AFX_DATA(CRmoListDlg)
	enum { IDD = IDD_RMOLISTDLG };
	CListBox	m_FSGList;
	CStatic	ST5;
	CStatic	ST4;
	CStatic	ST3;
	CStatic	ST2;
	CStatic	ST1;
	CEdit	m_Desc;
	CButton	m_ChangeSGList;
	CListBox	m_SGList;
	CComboBox	m_LNumber;
	CButton	m_DIS;
	CButton	m_COMMCNG;
	CButton	m_SRGPCNG;
	CButton	m_USERCNG;
	CComboBox	m_Category;
	CEdit	m_ComputerName;
	CListBox	m_RMOList;
	//}}AFX_DATA

	void SetRmoList(TSNPData *TND);
	void SetRmoProfile(TSNPData *TND);
	void Update(void);

private:
	unsigned __int32 RMOUID;
	unsigned __int32 Attr;
	unsigned __int8 RMLineNumber;
	TZSuperShortString ComputerName;
	TUIList UIL;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRmoListDlg)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRmoListDlg)
	afx_msg void OnSelchangeList1();
	afx_msg void OnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButton1();
	afx_msg void SetModifyKey();
	afx_msg void OnButton4();
	afx_msg void OnDblclkList3();
	afx_msg void OnButton3();
	afx_msg void OnKillfocusList3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMOLISTDLG_H__7D7B8DD0_C6D9_4B0A_9C84_8CAAD1CC6D7B__INCLUDED_)
