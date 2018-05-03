// RMO.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RMO.h"
#include "RMODlg.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "HookService.h"
#include "RMOClientPipe.h"

/////////////////////////////////////////////////////////////////////////////
// CRMOApp

BEGIN_MESSAGE_MAP(CRMOApp, CWinApp)
	//{{AFX_MSG_MAP(CRMOApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMOApp construction

CRMOApp::CRMOApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRMOApp object

CRMOApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRMOApp initialization
void CRMOApp::SetText(const char *str, COLORREF Color, bool Blink, DWORD TextStyle)
{
	CMF->SetText(str, Color, Blink, TextStyle);
}

void CRMOApp::SetSubText(const char *str, bool ALARM)
{
	CMF->SetSubText(str, ALARM);
}

void CRMOApp::SetScrollTimer(void)
{
	CMF->SetScrollTimer();
}

void CRMOApp::KillScrollTimer(void)
{
	CMF->KillScrollTimer();
}

void CRMOApp::SetSLNum(unsigned k)
{
	CMF->SetSLNum(k);
}

void CRMOApp::SetQueueState(unsigned k)
{
	CMF->SetQueueState(k);
}

//#include <fstream.h>

BOOL CRMOApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//CHookService CHS;

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	ThreadID = ::GetCurrentThreadId();
	CHS = new CHookService;
	CMF = new CMainFrame;
	CRCP = new CRMOClientPipe(this);

	CMF->Show();
	CMF->SetText("", COLORREF(0xFF0000));
/*//	CMF->SetText("ВЫЗОВ", COLORREF(0x0000FF), true);
//	CMF.SetText("НОРМ", COLORREF(0x666666));
//	CMF->SetSubText("В обслуживании");
//	CMF.SetSubText("Нет связи с сервером", true);
*/
	CHS->Init(CMF->m_hWnd);

MSG msg;
LONG lIdle = 0;
	bDoingBackgroundProcessing=true;


	while ( bDoingBackgroundProcessing ) 
	{ 
		while (PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) 
		{
//			fstream fout("c:\\789.txt", ios::out|ios::ate, 0);
//			fout << hex << msg.message << " " << msg.lParam << " " << msg.wParam << endl;

			if (!PumpMessage() || msg.message==WM_QUIT)
			{
				bDoingBackgroundProcessing = false;
				break; 
			};

			switch (msg.message)
			{
				case WM_HOOKMESSAGE:
					CMF->OnKbdHook(msg.wParam, msg.lParam);
					break;
		//		case WM_SIZE:
		//			CMF->SendMessage(WM_SIZE, 0, 0x00300030);
		//			break;
			};
		} 
		while (AfxGetApp()->OnIdle(lIdle++)) {};
		Sleep(10);
	};
	

//	Beep(1000, 500);

	CHS->Terminate();
	delete CHS;

	CRCP->Stop();
	delete CRCP;

//	CMF->DestroyWindow();
	delete CMF;

	ExitInstance();
	return FALSE;
}
