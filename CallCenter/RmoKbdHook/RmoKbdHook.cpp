// RmoKbdHook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "..\RMO\IPCDEFINES.h"

#pragma data_seg(".KBDHOOKDATA")
__ST_KeyboardHookTag KbdHookTag;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.KBDHOOKDATA,RWS")

//#include <fstream.h>

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
//	fstream fout("c:\\123.txt", ios::out|ios::ate, 0);
//	fout << code << " " << hex << wParam << " " << hex << lParam << "   ";

//	Beep(800,400);
//	if (code>=0)
//		return CallNextHookEx(KbdHookTag.hKbdHook, code, wParam, lParam);
//	if (code==HC_NOREMOVE
//	if (code==HC_ACTION)
	{
	DWORD cbw;
	UINT buf[2];
	HANDLE hMailSlot;
		buf[0]=wParam; buf[1]=lParam;
		hMailSlot = CreateFile(KHTMAILSLOTNAME,
			GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hMailSlot, buf, sizeof(buf), &cbw, NULL);
		CloseHandle(hMailSlot);
//		fout << hMailSlot << " " << endl;
//	fout.close();

		if (wParam==VK_PAUSE || wParam==VK_SCROLL)
		{
			wParam=0; lParam=0;
			return 1;
		};
	};
	return CallNextHookEx(KbdHookTag.hKbdHook, code, wParam, lParam);
};

extern "C" __declspec(dllexport) __ST_KeyboardHookTag* GETKHT(void)
{
	return &KbdHookTag;
};

extern "C" __declspec(dllexport) void HookKbdProc(void)
{
	KbdHookTag.hKbdHook = SetWindowsHookEx(WH_KEYBOARD, 
		KeyboardProc, KbdHookTag.hModule, NULL);
};

extern "C" __declspec(dllexport) void UnHookKbdProc(void)
{
	UnhookWindowsHookEx(KbdHookTag.hKbdHook);
};

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
	KbdHookTag.hModule = (HINSTANCE)hModule;
    return TRUE;
}

