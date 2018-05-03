// RMO.h : main header file for the RMO application
//

#if !defined(AFX_RMO_H__4EB3D3BF_C279_4EA9_9B97_0E569E84A487__INCLUDED_)
#define AFX_RMO_H__4EB3D3BF_C279_4EA9_9B97_0E569E84A487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRMOApp:
// See RMO.cpp for the implementation of this class
//

class CHookService;
class CRMOClientPipe;
class CMainFrame;

class CRMOApp : public CWinApp
{
public:
	CRMOApp();
	bool bDoingBackgroundProcessing;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	CHookService *CHS;
	CRMOClientPipe *CRCP;
	CMainFrame *CMF;

	void SetText(const char *str, COLORREF Color, bool Blink=false, DWORD TextStyle=DT_CENTER|DT_VCENTER);
	void SetSubText(const char *str, bool ALARM=false);
	void SetQueueState(unsigned k);
	void SetScrollTimer(void);
	void KillScrollTimer(void);
	void SetSLNum(unsigned k);

	DWORD ThreadID;

// Implementation

	//{{AFX_MSG(CRMOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CRMOApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMO_H__4EB3D3BF_C279_4EA9_9B97_0E569E84A487__INCLUDED_)
