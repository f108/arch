// ConnectionServer.cpp: implementation of the CConnectionServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConnectionServer.h"


#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define PipeName "\\\\.\\pipe\\TlgCallCenter"
#define BUFSIZE 10000
#define PIPE_TIMEOUT 10000

CConnectionServer::CConnectionServer(bool CreateSuspend) : CThread(CreateSuspend)
{
	hEvents[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
//	cout << "CConnectionServer=" << this << "-" << (void*)(((char*)this)+sizeof(*this))<< endl;
}

CConnectionServer::~CConnectionServer()
{
	CloseHandle(hEvents[0]);
}

void CConnectionServer::Execute(void)
{
DWORD Res, i, dwWait, CurWait;
SECURITY_ATTRIBUTES saPipeSecurity;
PSECURITY_DESCRIPTOR pPipeSD = NULL;

	memset((VOID *)&saPipeSecurity, 0, sizeof(SECURITY_ATTRIBUTES));
	if (!(pPipeSD=(PSECURITY_DESCRIPTOR) (malloc(SECURITY_DESCRIPTOR_MIN_LENGTH)))) ;;
	if (!InitializeSecurityDescriptor(pPipeSD, SECURITY_DESCRIPTOR_REVISION)) ;;
	if (!SetSecurityDescriptorDacl(pPipeSD, TRUE, (PACL)NULL, FALSE)) ;;
	saPipeSecurity.nLength    = sizeof (SECURITY_ATTRIBUTES);
	saPipeSecurity.bInheritHandle  = TRUE;
	saPipeSecurity.lpSecurityDescriptor = pPipeSD;

	for (i=0; i<INSTANCESCOUNT; i++)
	{
		for (;;)
		{
			RMS[i].hPipe = CreateNamedPipe(PipeName, PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,
					PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
					INSTANCESCOUNT, BUFSIZE, BUFSIZE, PIPE_TIMEOUT, &saPipeSecurity);
			if (RMS[i].hPipe!=INVALID_HANDLE_VALUE) break;
			Sleep(100);
		};
		hEvents[i+1] = RMS[i].oOverlap.hEvent;
		RMS[i].InstanceNumber = i;
		RMS[i].ConnectToNewClient();
	};

	for (;!Terminated;)
	{
		try
		{
			dwWait = WaitForMultipleObjects(INSTANCESCOUNT+1, hEvents, FALSE, KEEPALIVETIMEOUT/2);

			if (dwWait==WAIT_TIMEOUT)
			{
		//		cout << "Check timeouts" << endl;
		//		for (i=0; i<INSTANCESCOUNT; i++) RMS[i].CheckTimeout();
				continue;
			};

			CurWait = dwWait - WAIT_OBJECT_0 - 1;
			for (;;)
			{
				EnterCriticalSection(&RMS[CurWait].CS);
				RMS[CurWait].ProcessEvent();
				LeaveCriticalSection(&RMS[CurWait].CS);
				if (CurWait==INSTANCESCOUNT-1) break;
				dwWait = WaitForMultipleObjects(INSTANCESCOUNT-CurWait-1, &hEvents[CurWait+1+1], FALSE, 0);
				if (dwWait==WAIT_TIMEOUT) break;
				CurWait += dwWait - WAIT_OBJECT_0+1;
			};
		}
		catch (...)
		{
			FLOG << time << "Exception in CConnectionServer" << endl;
		};
	};
}

void CConnectionServer::ReloadRMOProfile(CRMOStoredData *CRMOSD)
{
	if (CRMOSD==NULL) return;
	for (int i=0; i<INSTANCESCOUNT; i++)
	{
		if (RMS[i].RMOUID==CRMOSD->RMOUID)
		{
			EnterCriticalSection(&RMS[i].CS);
			RMS[i].CopyFrom(CRMOSD);
			LeaveCriticalSection(&RMS[i].CS);
		};
	};
}

void CConnectionServer::LoadRMOProfile(unsigned PipeInstanceNumber, CRMOStoredData *CRMOSD)
{
	if (PipeInstanceNumber>=INSTANCESCOUNT) return;
	if (CRMOSD==NULL) 
	{
		RMS[PipeInstanceNumber].MustBeDisconnected = true;
		RMS[PipeInstanceNumber].SendCommand(RMCMD_DISCONNECTANDSTAYOFFLINE);
		return;
	};
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	RMS[PipeInstanceNumber].CopyFrom(CRMOSD);
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
	CSystemObject::PostSysMessage(SCMD_REGISTEROPERATOR,0, PipeInstanceNumber);
}

TZSuperShortString CConnectionServer::GetPipeInstName(unsigned PipeInstanceNumber)
{
	if (PipeInstanceNumber>=INSTANCESCOUNT) return TZSuperShortString();
TZSuperShortString ret;
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	ret = RMS[PipeInstanceNumber].ComputerName;
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
	return ret;
}

unsigned __int32 CConnectionServer::GetPipeInstRUID(unsigned PipeInstanceNumber)
{
	if (PipeInstanceNumber>=INSTANCESCOUNT) return 0;
unsigned __int32 ret;
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	ret = RMS[PipeInstanceNumber].RMOUID;
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
	return ret;
}

bool CConnectionServer::SendMessage(unsigned PipeInstanceNumber, TSNPData *TND)
{
	if (PipeInstanceNumber>=INSTANCESCOUNT || RMS[PipeInstanceNumber].RMOUID==0)
	{
		delete TND;
		return false;
	};
	RMS[PipeInstanceNumber].SendMessage(TND);
	return true;
}

unsigned __int32 CConnectionServer::GetClientType(unsigned PipeInstanceNumber)
{
	if (PipeInstanceNumber>=INSTANCESCOUNT) return 0;
unsigned __int32 ret;
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	ret = RMS[PipeInstanceNumber].ClientType;
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
	return ret;
}

void CConnectionServer::GetSGList(int PipeInstanceNumber, TUIList *UIL)
{
	if (unsigned(PipeInstanceNumber)>=INSTANCESCOUNT) return;
	(*UIL).Reset();
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	(*UIL) = RMS[PipeInstanceNumber].ServiceGroupsList;
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
}

/*CRMOStoredData *CConnectionServer::GetRMS(unsigned PipeInstanceNumber)
{
	if (PipeInstanceNumber>=INSTANCESCOUNT) return 0;
	return dynamic_cast<CRMOStoredData*> (&RMS[PipeInstanceNumber]);
}*/

void CConnectionServer::SetRMOState(unsigned PipeInstanceNumber, unsigned State)
{
	if (PipeInstanceNumber>=INSTANCESCOUNT) return;
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	if (State<RMO_STATEMASK)
		RMS[PipeInstanceNumber].RMOState = RMS[PipeInstanceNumber].RMOState&~RMO_STATEMASK|State;
	else
		RMS[PipeInstanceNumber].RMOState |= State;
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
}

void CConnectionServer::ClearRMOState(unsigned PipeInstanceNumber, unsigned State)
{
	if (PipeInstanceNumber>=INSTANCESCOUNT) return;
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	if (State>RMO_STATEMASK)
		RMS[PipeInstanceNumber].RMOState &= ~State;
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
}

unsigned CConnectionServer::GetRMOState(unsigned PipeInstanceNumber)
{
unsigned ret;
	if (PipeInstanceNumber>=INSTANCESCOUNT) return 0;
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	ret = RMS[PipeInstanceNumber].RMOState;
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
	return ret;
}

unsigned CConnectionServer::GetRMOSLNum(unsigned PipeInstanceNumber)
{
unsigned ret;
	if (PipeInstanceNumber>=INSTANCESCOUNT) return 0;
	EnterCriticalSection(&RMS[PipeInstanceNumber].CS);
	ret = RMS[PipeInstanceNumber].RMLineNumber;
	LeaveCriticalSection(&RMS[PipeInstanceNumber].CS);
	return ret;
}

unsigned CConnectionServer::GetRMOIndexBySLNum(unsigned SLNum)
{
	for (int i=0; i<INSTANCESCOUNT; i++)
	{
		EnterCriticalSection(&RMS[i].CS);
		if (RMS[i].RMLineNumber==SLNum && (RMS[i].ClientType&RMOA_CATEGORYMASK)==RMOA_OPERATOR)
		{
			LeaveCriticalSection(&RMS[i].CS);
			return i;
		};
		LeaveCriticalSection(&RMS[i].CS);
	};
	throw ERMNotAttached();
}

void CConnectionServer::FillFreeRMOList(TCSUI32DualList *UIDL, unsigned SG)
{
	for (unsigned p=0; p<INSTANCESCOUNT; p++)
	{
		if (RMS[p].ClientType!=RMOA_OPERATOR ||
			RMS[p].RMOState!=RMO_WAITCALL || 
			!RMS[p].ServiceGroupsList.ValueInList(SG)) continue;
		UIDL->Add(p, RMS[p].RMOUID);
	};
}

void CConnectionServer::GetSGListForRMO(unsigned RMOIndex, TUIList *UIL)
{
	if (RMOIndex>=INSTANCESCOUNT) return;
	EnterCriticalSection(&RMS[RMOIndex].CS);
	(*UIL) = RMS[RMOIndex].ServiceGroupsList;
	LeaveCriticalSection(&RMS[RMOIndex].CS);
}

void CConnectionServer::SetCALLAttr(unsigned RMOIndex, unsigned SLNum, unsigned SGID)
{
	if (RMOIndex>=INSTANCESCOUNT) return;
	EnterCriticalSection(&RMS[RMOIndex].CS);
	RMS[RMOIndex].SLSG = SGID;
	RMS[RMOIndex].ConnectToSLNum = SLNum;
	LeaveCriticalSection(&RMS[RMOIndex].CS);
}

void CConnectionServer::GetCALLAttr(unsigned RMOIndex, unsigned *SLNum, unsigned *SGID)
{
	if (RMOIndex>=INSTANCESCOUNT) return;
	EnterCriticalSection(&RMS[RMOIndex].CS);
	(*SGID) = RMS[RMOIndex].SLSG;
	(*SLNum) = RMS[RMOIndex].ConnectToSLNum;
	LeaveCriticalSection(&RMS[RMOIndex].CS);
}

