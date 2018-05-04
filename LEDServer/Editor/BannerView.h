#if !defined(AFX_BANNERVIEW_H__202073FA_048C_4BE5_8131_193079E3B073__INCLUDED_)
#define AFX_BANNERVIEW_H__202073FA_048C_4BE5_8131_193079E3B073__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BannerView.h : header file
//

#include "BitmapView.h"

/////////////////////////////////////////////////////////////////////////////
// CBannerView dialog

class CBannerView : public CDialog
{
// Construction
public:
	CBannerView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBannerView)
	enum { IDD = IDD_DIALOG1 };
	CBitmapView CBV;
	CEdit	m_dd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBannerView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBannerView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANNERVIEW_H__202073FA_048C_4BE5_8131_193079E3B073__INCLUDED_)
