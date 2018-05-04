#if !defined(AFX_SYMBOLEDITOR_H__05065406_42D6_4209_8AA0_C21C90F31E3F__INCLUDED_)
#define AFX_SYMBOLEDITOR_H__05065406_42D6_4209_8AA0_C21C90F31E3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SymbolEditor.h : header file
//
#include "MatrixView.h"

/////////////////////////////////////////////////////////////////////////////
// CSymbolEditor dialog

class CSymbolEditor : public CDialog
{
// Construction
public:
	CSymbolEditor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSymbolEditor)
	enum { IDD = IDD_SMBEDITOR };
	CEdit	m_Text;
	CMatrixView CMV;
	//}}AFX_DATA

	void SetParam(const char *SmbInfo, int _HS, int _VS, char *buf);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSymbolEditor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSymbolEditor)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYMBOLEDITOR_H__05065406_42D6_4209_8AA0_C21C90F31E3F__INCLUDED_)
