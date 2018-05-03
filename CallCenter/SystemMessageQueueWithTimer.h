// SystemMessageQueueWithTimer.h: interface for the CSystemMessageQueueWithTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMMESSAGEQUEUEWITHTIMER_H__4B6D6B1C_FABA_4FC6_8AA3_95FAD9BFD496__INCLUDED_)
#define AFX_SYSTEMMESSAGEQUEUEWITHTIMER_H__4B6D6B1C_FABA_4FC6_8AA3_95FAD9BFD496__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TUIList.h"

struct st_SCSMQWT
{
	DWORD AlarmTime;
	unsigned __int64 MSG;
	st_SCSMQWT(DWORD _ALARMTIME, unsigned __int64 _MSG) 	{ AlarmTime = _ALARMTIME; MSG = _MSG; };
};

class CSystemMessageQueueWithTimer 
{
public:
	class ENoMessage { };

	CSystemMessageQueueWithTimer();
	virtual ~CSystemMessageQueueWithTimer();

	void Push(DWORD TimeInterval, unsigned __int64 Msg);
	unsigned __int64 Pop(void);

private:
	TPtrList<st_SCSMQWT> MsgList;
	CRITICAL_SECTION CS;
};

#endif // !defined(AFX_SYSTEMMESSAGEQUEUEWITHTIMER_H__4B6D6B1C_FABA_4FC6_8AA3_95FAD9BFD496__INCLUDED_)
