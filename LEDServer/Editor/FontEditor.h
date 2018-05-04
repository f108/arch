#if !defined(AFX_FONTEDITOR_H__410372AB_BD35_45C5_B87A_C9589664E680__INCLUDED_)
#define AFX_FONTEDITOR_H__410372AB_BD35_45C5_B87A_C9589664E680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FontEditor.h : header file
//
#include "MatrixView.h"
#include "SymbolEditor.h"

/////////////////////////////////////////////////////////////////////////////
// CFontEditor dialog

extern CString FontFolder;

class CFontEditor : public CDialog
{
// Construction
public:
	CFontEditor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFontEditor)
	enum { IDD = IDD_FONTEDITOR };
	CComboBox	m_FontList;
	CMatrixView CMV;
	//}}AFX_DATA

//	CBitmap FontBitmap;
	CSymbolEditor CSE;
	DWORD HS, VS;
	CString FontName;
	CPoint LBtnDown;
	unsigned char SelectedItem;
	void ReadFontList(void);

	char *EdSymbBuf;
	bool Changed[256];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontEditor)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFontEditor)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnSave();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnButton3();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTEDITOR_H__410372AB_BD35_45C5_B87A_C9589664E680__INCLUDED_)
