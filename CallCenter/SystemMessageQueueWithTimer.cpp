// SystemMessageQueueWithTimer.cpp: implementation of the CSystemMessageQueueWithTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemMessageQueueWithTimer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemMessageQueueWithTimer::CSystemMessageQueueWithTimer()
{
	InitializeCriticalSection(&CS);
}

CSystemMessageQueueWithTimer::~CSystemMessageQueueWithTimer()
{
	DeleteCriticalSection(&CS);
}

void CSystemMessageQueueWithTimer::Push(DWORD TimeInterval, unsigned __int64 Msg)
{
	EnterCriticalSection(&CS);
	MsgList.Add(new st_SCSMQWT(GetTickCount()+TimeInterval, Msg));
	LeaveCriticalSection(&CS);
}

unsigned __int64 CSystemMessageQueueWithTimer::Pop(void)
{
	if (MsgList.GetCount() == 0) return 0;// throw ENoMessage();
unsigned __int64 Ret=0;
	EnterCriticalSection(&CS);
	DWORD TC = GetTickCount();
	for (int i=0; i<MsgList.GetCount(); i++)
	{
		if (__int64(MsgList[i]->AlarmTime)-TC<0)
		{
			Ret = MsgList[i]->MSG;
			MsgList.Delete(i);
			break;
		};
	};
	LeaveCriticalSection(&CS);
	if (Ret!=0) return Ret;
	return 0;//throw ENoMessage();
}
