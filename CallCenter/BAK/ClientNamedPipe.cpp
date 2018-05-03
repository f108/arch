// ClientNamedPipe.cpp: implementation of the CClientNamedPipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClientNamedPipe.h"

#include "..\TZSSString.h"

#include <iostream.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientNamedPipe::CClientNamedPipe() : CThread(true)
{
	strcpy(PipeName, "\\\\MPL\\pipe\\TlgCallCenter");//\\\\GERMES\\pipe\\Pager\\DataBaseAccess");
	memset(&oOverlap, 0, sizeof(oOverlap));
	oOverlap.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	hPipe = INVALID_HANDLE_VALUE;
	this->Resume();
}

CClientNamedPipe::~CClientNamedPipe()
{
	CloseHandle(hPipe);
	CancelIo(hPipe);
}

void CClientNamedPipe::Stop(void)
{
	PipeIOState = PIO_SHUTDOWN;
	SetEvent(oOverlap.hEvent);
	Sleep(500);
}

void CClientNamedPipe::Execute(void)
{
DWORD CBR, cbw, res, LastError, RES, cbAvail, TempRes;
TSNPData TND;
TSNPData *CurrentSendMessage=NULL;
void *buf;
	
	for (;!Terminated;)
	{
		try
		{
			res = WaitForSingleObject(oOverlap.hEvent, 10000);
//			cout << "Post WaitForSO" << endl;
			if (res==WAIT_OBJECT_0)
			{
				if (PipeIOState==PIO_SHUTDOWN) throw EEndOfSession();
				if ((PipeIOState&PIO_BREAK)!=0) CancelIo(hPipe);

				SetLastError(0);
				RES = GetOverlappedResult(hPipe, &oOverlap, &CBR, FALSE);
				LastError = GetLastError();

				if (LastError==ERROR_FILE_NOT_FOUND) throw IOPipeException();
				if ((LastError==ERROR_BROKEN_PIPE || LastError==ERROR_PIPE_NOT_CONNECTED)
					&& PipeIOState!=PIO_CONNECT && RES==0) throw IOPipeException(); 

				if (RES==1 && LastError!=ERROR_OPERATION_ABORTED)
				{
					switch (PipeIOState)
					{
						case PIO_SHUTDOWN:
							throw EEndOfSession();
							break;
						case PIO_CONNECT:
						case PIO_CONNECT|PIO_BREAK:
							break;
						case PIO_WRITE:
						case PIO_WRITE|PIO_BREAK:
							cout << "PIO_WRITE" << endl;
							delete CurrentSendMessage;
							CurrentSendMessage = NULL;
//							cout << "PIO_WRITE" << endl;
							break;
						case PIO_READ:
						case PIO_READ|PIO_BREAK:
							cout << "PIO_READ" << endl;
							TND.AdjustSize(CBR);
							cout << "PIO_READ #1" << endl;
							ProcessMessage(TND);
							cout << "PIO_READ #2" << endl;
							TND.Reset();
//							cout << "PIO_READ" << endl;
							break;
					};
				};
				if (CurrentSendMessage==NULL && !OutboundList.IsEmpty())
					CurrentSendMessage = OutboundList.Pop();

				if (!PeekNamedPipe(hPipe, NULL, 0, NULL, &cbAvail, NULL))
				{
					throw IOPipeException();
				};

				if (CurrentSendMessage!=NULL && cbAvail==0)
				{
					buf = *CurrentSendMessage;
					TempRes = WriteFile(hPipe, buf, CurrentSendMessage->GetSize(), &TempRes, &oOverlap);
					FlushFileBuffers(hPipe);
					PipeIOState = PIO_WRITE;
//					cout << "Do write with codes " << TempRes << " " << GetLastError() << endl;
					continue;
				};

				if (TND.GetSize()==0)
				{
					TempRes = ReadFile(hPipe, TND, NPMAXMESSAGESIZE, &TempRes, &oOverlap);
//					cout << "Do read with codes " << TempRes << " " << GetLastError() << endl;
					PipeIOState = PIO_READ;
					continue;
				};
			};
		}
		catch (EEndOfSession)
		{
			DisconnectNamedPipe(hPipe);
			break;
		}
		catch (IOPipeException)
		{
			ProcessException(PE_CONNECTTOSERVER);
			Sleep(500);
			Init();
		};
	}; // for (;!terminated;)
}

void CClientNamedPipe::Init(void)
{
	cout << "INIT" << endl;
	CancelIo(hPipe);
	CloseHandle(hPipe);
	if (!WaitNamedPipe(PipeName, 5000)) 
	{
		SetLastError(ERROR_FILE_NOT_FOUND);
		hPipe=INVALID_HANDLE_VALUE;
		return;
	};
	hPipe = CreateFile(PipeName, GENERIC_WRITE | GENERIC_READ,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED|FILE_FLAG_NO_BUFFERING, NULL);
	if (hPipe==INVALID_HANDLE_VALUE) 
	{
		cout << hPipe << " " << dec << GetLastError() << endl;
		SetLastError(ERROR_FILE_NOT_FOUND);
		return;
	};

DWORD dwMode = PIPE_READMODE_MESSAGE|PIPE_WAIT;
	dwMode = SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);
	PipeIOState = PIO_CONNECT;
	cout << "PreProc Exception"<< endl;
	ProcessException(PE_CONNECTIONINPROGRESS);
	cout << "PostProc Exception"<< endl;
}

void CClientNamedPipe::SendCommand(unsigned __int8 Command)
{
TSNPData *TND = new TSNPData;
	(*TND) << Command;
	SendMessage(TND);
}

void CClientNamedPipe::SendMessage(TSNPData *TND)
{
	OutboundList.Push(TND);
	if ((PipeIOState&PIO_READ)!=0) 
	{
		PipeIOState |= PIO_BREAK;
		SetEvent(oOverlap.hEvent);
	};
}

unsigned __int32 CClientNamedPipe::GetClientType(void) 
{ 
	return 0; 
};

void CClientNamedPipe::ProcessException(unsigned) 
{ 
};

void CClientNamedPipe::ProcessMessage(TSNPData &TND)
{
unsigned __int8 Command;
//TSNPData *TND2;
TZSuperShortString str;

	TND >> Command;

	switch (Command)
	{
		case RMCMD_SRVKEEPALIVE:
			SendCommand(RMCMD_SRVKEEPALIVE);
			break;
		case RMCMD_WHOAREYOU:
			DWORD MaxLen; MaxLen=MAX_COMPUTERNAME_LENGTH; char buf[MAX_COMPUTERNAME_LENGTH+1];
			GetComputerName(buf, &MaxLen); str = buf;
			TSNPData *TND2;
			TND2 = new TSNPData;
			(*TND2) << RMCMD_MYNAME << str << GetClientType();
			SendMessage(TND2);
			ProcessException(PE_INIT);
			break;
		case RMCMD_DISCONNECTANDSTAYOFFLINE:
//			cout << "DISCONNECTED BY SERVER" << endl;
			ProcessException(PE_STAYOFFLINE);
			Terminated = true;
			break;
	};
}
