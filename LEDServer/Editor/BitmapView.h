#if !defined(AFX_BITMAPVIEW_H__BAEC2A36_5579_46DE_B5A5_2122EE51F66E__INCLUDED_)
#define AFX_BITMAPVIEW_H__BAEC2A36_5579_46DE_B5A5_2122EE51F66E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitmapView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitmapView view

#define CBV_CLASSNAME    _T("BitmapView")  // Window class name

class CBitmapView : public CScrollView
{
	BOOL RegisterWindowClass();

public:
	CBitmapView();           // protected constructor used by dynamic creation
protected:
	DECLARE_DYNCREATE(CBitmapView)

// Attributes
public:
	int Grid_X, Grid_Y;

// Operations
public:
	virtual ~CBitmapView();

	void SetGrid(int dx, int dy);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CBitmapView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPVIEW_H__BAEC2A36_5579_46DE_B5A5_2122EE51F66E__INCLUDED_)
