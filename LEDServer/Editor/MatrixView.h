#if !defined(AFX_MATRIXVIEW_H__3E0BABAC_6E04_44B7_9E17_1E39ACF12820__INCLUDED_)
#define AFX_MATRIXVIEW_H__3E0BABAC_6E04_44B7_9E17_1E39ACF12820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatrixView.h : header file
//

#define CA_NOTIFY_MOUSEMESSAGE 1
#define CA_NOTIFY_CUSTDRAW     2
#define CA_NOTIFY_CHANGEIMAGE  4

/////////////////////////////////////////////////////////////////////////////
// CMatrixView window
#define CMV_CLASSNAME    _T("MatrixView")  // Window class name

struct SCustMVDrawItem
{
	CDC *dc;
	int x, y;
	int xs, ys;
};

class CMatrixView : public CWnd
{
	BOOL RegisterWindowClass();
// Construction
public:
	CMatrixView();

// Attributes
public:

	int HS, VS;
	char *buf;
	char PrevColor;
	DWORD CustAttr;

// Operations
public:

	void ChangeAttr(DWORD _Attr) {CustAttr=_Attr;};
	void Init(int _HS, int _VS, char *_buf);
	void WhereMouse(CPoint mpxl, CPoint *mcl);
	void RedrawItem(int x, int y);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatrixView)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMatrixView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMatrixView)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATRIXVIEW_H__3E0BABAC_6E04_44B7_9E17_1E39ACF12820__INCLUDED_)
