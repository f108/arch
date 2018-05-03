// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <process.h>

#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DWORD WINAPI __CThread_InternalThreadProc(void *Thread)
//unsigned int __stdcall __CThread_InternalThreadProc(void *Thread)
{
//	cout << "EE1" << endl;
	((CThread *)Thread)->__Execute();
 	return 0;
};

CThread::CThread(bool CreateSuspended)
{
	Terminated = false;
	hTerminateEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//	hThread = (HANDLE) _beginthreadex(NULL, 0, __CThread_InternalThreadProc,
//		this, CreateSuspended?CREATE_SUSPENDED:0, (unsigned int *)&(this->ThreadID));
				
	hThread = CreateThread(NULL, 0, __CThread_InternalThreadProc, this,
            CreateSuspended?CREATE_SUSPENDED:0, &(this->ThreadID)); 
}

CThread::~CThread()
{

} 

void CThread::__Execute(void)
{
//	cout << "EE2" << endl;
//	try {
		Execute();
/*	} catch (...)
	{
		cout << "Exception ThreadID=" << GetCurrentThreadId() << endl;
		cout << "this=" << this << endl;
	};*/
	SetEvent(hTerminateEvent);
//	ExitThread(1);
}

void CThread::Terminate(void)
{
	Terminated = true;
}

DWORD CThread::TerminateAndWait(DWORD tout)
{
	Terminated = true;
	return WaitForSingleObject(hTerminateEvent, tout);
}

void CThread::Kill(void)
{
	if (WaitForSingleObject(hTerminateEvent, 0)!=WAIT_OBJECT_0)
		TerminateThread(hThread, 0);
}

bool CThread::SetPriority(int tp)
{
	return (SetThreadPriority(hThread, tp)==1);
}

void CThread::Resume(void)
{
	ResumeThread(hThread);
}

void CThread::Suspend(void)
{
	SuspendThread(hThread);
}

HANDLE CThread::GetThreadHandle(void)
{
	return hThread;
}
