// HookService.cpp: implementation of the CHookService class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RMO.h"
#include "MainFrame.h"
#include "HookService.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHookService::CHookService() : CThread(true)
{
//	Init(NULL);
}

CHookService::~CHookService()
{
	UnHookProc();
	Sleep(200);
	FreeLibrary(hModule);
	CloseHandle(hMailSlot);
}

void CHookService::Terminate(void)
{
	Terminated = true;
DWORD cbw;
UINT buf[2];
HANDLE hMailSlot;
	buf[0]=0; buf[1]=0;
	hMailSlot = CreateFile(KHTMAILSLOTNAME,
		GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hMailSlot, buf, sizeof(buf), &cbw, NULL);
	CloseHandle(hMailSlot);
	TerminateAndWait(200);
}

//#include <fstream.h>

void CHookService::Execute(void)
{
WPARAM buf[2];
DWORD cbr;
	for (;!Terminated;)
	{
		if (!ReadFile(hMailSlot, (LPVOID)buf, 2*sizeof(WPARAM), &cbr, NULL)) break;
//	fstream fout("c:\\456.txt", ios::out|ios::ate, 0);
//	fout << hex << buf[0] << " " << hex << buf[1] << "   ";
		::PostThreadMessage(theApp.ThreadID, WM_USER+555, buf[0], buf[1]);
//		::SendMessage(theApp.CMF->m_hWnd, WM_USER+555, buf[0], buf[1]);
//	fout.close();

///		::PostMessage(KbdHookTag->MainFrame, WM_USER+555, buf[0], buf[1]);
		Sleep(5);
	//	Beep(500,400);
	};
//	Beep(2000,300);
}

bool CHookService::Init(HWND hWnd)
{
	__ST_KeyboardHookTag* (*GETKHT)(void);
	hModule = LoadLibrary("RmoKbdHook.dll");
	GETKHT = (__ST_KeyboardHookTag* (*)(void))GetProcAddress(hModule, "GETKHT");
	KbdHookTag = GETKHT();
	KbdHookTag->MainFrame = hWnd;
	hMailSlot = CreateMailslot(KHTMAILSLOTNAME, 8, MAILSLOT_WAIT_FOREVER, 0);
	HookProc = (void(*)(void))GetProcAddress(hModule, "HookKbdProc");
	UnHookProc = (void(*)(void))GetProcAddress(hModule, "UnHookKbdProc");
	HookProc();
	Resume();
	return true;
}
