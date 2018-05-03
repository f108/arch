// ClientNamedPipe.cpp: implementation of the CClientNamedPipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RMO.h"
#include "ClientNamedPipe.h"

#include "..\TZSSString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientNamedPipe::CClientNamedPipe() : CThread(false)
{
	strcpy(PipeName, "\\\\.\\pipe\\TlgCallCenter");//\\\\GERMES\\pipe\\Pager\\DataBaseAccess");
	memset(&oOverlap, 0, sizeof(oOverlap));
	oOverlap.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	hPipe = INVALID_HANDLE_VALUE;
}

CClientNamedPipe::~CClientNamedPipe()
{

}

void CClientNamedPipe::Execute(void)
{
DWORD CBR, cbw, res, LastError, RES, cbAvail, TempRes;
TSNPData TND;
TSNPData *CurrentSendMessage=NULL;
	
	for (;!Terminated;)
	{
		try
		{
			res = WaitForSingleObject(oOverlap.hEvent, 10000);
			if (res==WAIT_OBJECT_0)
			{
				RES = GetOverlappedResult(hPipe, &oOverlap, &CBR, FALSE);
				LastError = GetLastError();
				switch (LastError)
				{
					case ERROR_SUCCESS:
					case ERROR_OPERATION_ABORTED:
					case ERROR_IO_INCOMPLETE:
					case ERROR_IO_PENDING:
						break;

					default:
						throw IOPipeException();
						break;
				}; // switch(LastError)

				if (RES==1)
				{
					switch (PipeIOState)
					{
						case PIO_CONNECT:
							break;
						case PIO_WRITE:
							delete CurrentSendMessage;
							CurrentSendMessage = NULL;
							break;
						case PIO_READ:
							TND.AdjustSize(CBR);
							ProcessMessage(TND);
							TND.Reset();
							break;
					};
				};
				if (CurrentSendMessage==NULL && !OutboundList.IsEmpty())
					CurrentSendMessage = OutboundList.Pop();

				if (!PeekNamedPipe(hPipe, NULL, 0, NULL, &cbAvail, NULL))
					throw IOPipeException();

				if (CurrentSendMessage!=NULL && cbAvail==0 && LastError!=ERROR_IO_PENDING)
				{
					TempRes = WriteFile(hPipe, *CurrentSendMessage, CurrentSendMessage->GetSize(), &TempRes, &oOverlap);
					PipeIOState = PIO_WRITE;
					continue;
				};

				if (TND.GetSize()==0 && LastError!=ERROR_IO_PENDING)
				{
					TempRes = ReadFile(hPipe, TND, NPMAXMESSAGESIZE, &TempRes, &oOverlap);
					PipeIOState = PIO_READ;
					continue;
				};
			};
		}
		catch (IOPipeException)
		{
			Init();
			Sleep(200);
		};
	}; // for (;!terminated;)
}
void CClientNamedPipe::Init(void)
{
	CloseHandle(hPipe);
	hPipe = CreateFile(PipeName, GENERIC_WRITE | GENERIC_READ,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (hPipe==INVALID_HANDLE_VALUE) return;
DWORD dwMode = PIPE_READMODE_MESSAGE;
	SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);
	PipeIOState = PIO_CONNECT;
}

void CClientNamedPipe::SendCommand(unsigned __int8 Command)
{
}

void CClientNamedPipe::SendMessage(TSNPData *TND)
{
	OutboundList.Push(TND);
}

void CClientNamedPipe::ProcessMessage(TSNPData &TND)
{
unsigned __int8 Command;

	TND >> Command;

	switch (Command)
	{
		case RMCMD_WHOAREYOU:
			DWORD MaxLen; MaxLen=MAX_COMPUTERNAME_LENGTH; char buf[MAX_COMPUTERNAME_LENGTH+1]; TZSuperShortString str;
			GetComputerName(buf, &MaxLen); str = buf;
			TSNPData *TND2 = new TSNPData;
			(*TND2) << RMCMD_MYNAME << str;
			SendMessage(TND2);
			break;
	};
}
