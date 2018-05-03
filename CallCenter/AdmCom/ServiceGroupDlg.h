#if !defined(AFX_SERVICEGROUPDLG_H__F97A9B20_9FCF_4992_AADE_F99608614C1A__INCLUDED_)
#define AFX_SERVICEGROUPDLG_H__F97A9B20_9FCF_4992_AADE_F99608614C1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiceGroupDlg.h : header file
//
#include "..\TZSSString.h"
#include "..\TUIList.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceGroupDlg dialog

class CServiceGroupDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CServiceGroupDlg)
// Construction
public:
	CServiceGroupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServiceGroupDlg)
	enum { IDD = IDD_SERVICEGROUPSDLG };
	CEdit	m_CallQueueCntEdit;
	CSpinButtonCtrl	m_QueueCapSpin;
	CStatic	ST9;
	CStatic	ST8;
	CStatic	ST7;
	CStatic	ST6;
	CSpinButtonCtrl	m_Spin;
	CEdit	m_OperCount;
	CButton	m_DONOTUSEQUEUE;
	CButton	m_USEQUEUE;
	CButton	m_BLINK;
	CListBox	m_SGList;
	CComboBox	m_RINGCAT;
	CStatic	ST5;
	CListBox	m_RMOList;
	CStatic	ST4;
	CStatic	ST3;
	CStatic	ST2;
	CStatic	ST1;
	CComboBox	m_CASEMETHOD;
	CEdit	m_DESC;
	CEdit	m_GRName;
	CButton	m_COLOR;
	//}}AFX_DATA

	unsigned __int32 SGID;
	TZSuperShortString SGCaption;
	TZSuperShortString SGDescription;
	unsigned __int32 COLOR;
	bool BlinkBanner;
	int SGSrchMthRngCat;
	TUIList	RMIDOrder;
	bool UseQueue;
	unsigned __int8 QueueType;
	bool UsingQueueByOperatorCount;
	unsigned __int8 OperatorCount;


	void SetSGList(TSNPData *TND);
	void SetSGProfile(TSNPData *TND);
	void Update(void);
	void DialogToMembers(void);
	void MembersToDialog(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceGroupDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServiceGroupDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton2();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnButton4();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICEGROUPDLG_H__F97A9B20_9FCF_4992_AADE_F99608614C1A__INCLUDED_)
