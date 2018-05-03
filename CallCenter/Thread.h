// Thread.h: interface for the CThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__E9CC8041_1960_11D4_92DD_00A02428EF78__INCLUDED_)
#define AFX_THREAD_H__E9CC8041_1960_11D4_92DD_00A02428EF78__INCLUDED_

#ifndef _WINDOWS_
#include <windows.h>
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CThread  
{
public:
	bool SetPriority(int);
	void Resume(void);
	void Suspend(void);

	void Terminate(void);
	DWORD TerminateAndWait(DWORD tout);
	void Kill(void);

	HANDLE GetThreadHandle(void);

	CThread(bool CreateSuspended);
	virtual ~CThread();

protected:
 	bool Terminated;
	DWORD ThreadID;
	virtual void Execute(void) = 0;

private:
	bool TerminatedFlag;
	HANDLE hThread;
	HANDLE hTerminateEvent;
	void __Execute(void);
	friend DWORD WINAPI __CThread_InternalThreadProc(void *); 
	//friend unsigned int __stdcall __CThread_InternalThreadProc(void *Thread);
};

#endif // !defined(AFX_THREAD_H__E9CC8041_1960_11D4_92DD_00A02428EF78__INCLUDED_)
