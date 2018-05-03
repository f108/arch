#if !defined(AFX_MAINFRAME_H__818998FD_C848_421A_9258_E5B9D33D403F__INCLUDED_)
#define AFX_MAINFRAME_H__818998FD_C848_421A_9258_E5B9D33D403F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainFrame window
#define CCCMF_CLASSNAME "CALLCNTMAINFR"

#define WM_HOOKMESSAGE WM_USER+555

static CSize MAINFRAMESIZE(190, 60);

class CMainFrame : public CWnd
{
public:
	static BOOL RegisterWindowClass();
// Construction
public:
	CMainFrame();

// Attributes
public:
	DWORD QUEUESTATE;
	float SZPR;
	POINT ptLBD;
	CRect TextWinRect;
	DWORD TextStyle;
	COLORREF TextColor;
	CString Text;
	bool TextVisible;
	CString SubText;
	bool ALARM;
	bool SubTextVisible;
	CRect SubTextWinRect;
	CRect LeftSubTextWinRect;
	CFont Font, Font2;

	bool GLScrollLock;
	bool ScrollLockOn;
	HANDLE hndKbdDev;
	char SLN[20];

// Operations
private:
	void DrawTextWindow(CDC &dc);
	void DrawLeftSubTextWindow(CDC &dc);
	void DrawSubTextWindow(CDC &dc);
	void DrawFrame(CDC &dc);
	void Resize();
public:
	void Show(void);
	void SetText(const char *str, COLORREF Color, bool Blink=false, DWORD TextStyle=DT_CENTER|DT_VCENTER);
	void SetSubText(const char *str, bool ALARM=false);
	void SetQueueState(int k);

	void SetScrollLock(bool state);
	void SetScrollTimer(void);
	void KillScrollTimer(void);
	void SetSLNum(unsigned k);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
public:
	afx_msg void OnKbdHook(WPARAM, LPARAM);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__818998FD_C848_421A_9258_E5B9D33D403F__INCLUDED_)
