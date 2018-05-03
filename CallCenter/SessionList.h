// SessionList.h: interface for the CSessionList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SESSIONLIST_H__FA74DCE1_CFFB_42F9_BD61_C1E1D9611487__INCLUDED_)
#define AFX_SESSIONLIST_H__FA74DCE1_CFFB_42F9_BD61_C1E1D9611487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TUIList.h"
#include "Thread.h"

class CRMOSession;

class CSessionList : protected CThread
{
public:
	CSessionList();
	virtual ~CSessionList();


private:
	void Execute(void);

	void Delete(unsigned __int32 index);

	CRITICAL_SECTION CS;
	TPtrList<CRMOSession> RMOS;
	TUI32ObjList<HANDLE> RMOH;

};

#endif // !defined(AFX_SESSIONLIST_H__FA74DCE1_CFFB_42F9_BD61_C1E1D9611487__INCLUDED_)
