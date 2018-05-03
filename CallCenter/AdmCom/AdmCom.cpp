// AdmCom.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AdmCom.h"
#include "AdmComDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdmComApp

BEGIN_MESSAGE_MAP(CAdmComApp, CWinApp)
	//{{AFX_MSG_MAP(CAdmComApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdmComApp construction

CAdmComApp::CAdmComApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAdmComApp object

CAdmComApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAdmComApp initialization

BOOL CAdmComApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CPS = new CPropertySheet(IDS_DLGCAPTION);


	CSGD = new CServiceGroupDlg();
	CSGD->Construct(IDD_SERVICEGROUPSDLG);
	CRLD = new CRmoListDlg();
	CRLD->Construct(IDD_RMOLISTDLG);
	CSLD = new CSLDLG();
	CSLD->Construct(IDD_SLDLG);

	CPS->AddPage(CSGD);
	CPS->AddPage(CRLD);
	CPS->AddPage(CSLD);
//	CPS->Create();
//	CPS->ModifyStyle(0, WS_SIZEBOX, TRUE);

	CPS->DoModal();

	/*CAdmComDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
*/
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
