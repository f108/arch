// HookService.h: interface for the CHookService class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOOKSERVICE_H__3DAA5E93_B1B7_4444_8932_8BB46F9C9090__INCLUDED_)
#define AFX_HOOKSERVICE_H__3DAA5E93_B1B7_4444_8932_8BB46F9C9090__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\IPCDEFINES.h"
#include "..\Thread.h"

class CHookService : public CThread
{
public:
	CHookService();
	virtual ~CHookService();

	bool Init(HWND hWnd);

	void Terminate(void);

protected:
	void Execute(void);

private:
	__ST_KeyboardHookTag *KbdHookTag;
	void (*HookProc)(void);
	void (*UnHookProc)(void);
	HANDLE hMailSlot;
	HINSTANCE hModule;
};

#endif // !defined(AFX_HOOKSERVICE_H__3DAA5E93_B1B7_4444_8932_8BB46F9C9090__INCLUDED_)
