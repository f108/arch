// SessionList.cpp: implementation of the CSessionList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SessionList.h"

#include "RMOSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSessionList::CSessionList() : CThread(false)
{
	RMOH.Add(CreateEvent(NULL, FALSE, FALSE, NULL));
}

CSessionList::~CSessionList()
{

}

void CSessionList::Execute(void)
{
DWORD Res;

	for (;!Terminated;)
	{
		Res = WaitForMultipleObjects(RMOH.GetCount(), RMOH.GetDataPtr(), FALSE, INFINITE);


	};
};

void CSessionList::Delete(unsigned __int32 index)
{
//	CloseHandle(RMOH[index]);
//	RMOH.Delete(index);
///	RMOS[index-1]->TerminateAndWait(2000);
//	delete RMOS[index-1];
//	RMOS.Delete(index-1);
}
