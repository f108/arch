// AdmCom.h : main header file for the ADMCOM application
//

#if !defined(AFX_ADMCOM_H__F95BE23D_C419_452B_A191_6C16D52BF438__INCLUDED_)
#define AFX_ADMCOM_H__F95BE23D_C419_452B_A191_6C16D52BF438__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "..\SRVCOMDEFINES.h"

#include "ServiceGroupDlg.h"
#include "RmoListDlg.h"
#include "SLDLG.h"

#include "AdmClientPipe.h"

/////////////////////////////////////////////////////////////////////////////
// CAdmComApp:
// See AdmCom.cpp for the implementation of this class
//

class CAdmComApp : public CWinApp
{
public:
	CAdmComApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdmComApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	CPropertySheet *CPS;

	CServiceGroupDlg *CSGD;
	CRmoListDlg *CRLD;
	CSLDLG *CSLD;

	CAdmClientPipe CACP;

// Implementation

	//{{AFX_MSG(CAdmComApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CAdmComApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADMCOM_H__F95BE23D_C419_452B_A191_6C16D52BF438__INCLUDED_)
