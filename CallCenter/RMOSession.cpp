// RMOSession.cpp: implementation of the CRMOSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RMOSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRMOSession::CRMOSession()// : CThread(true)
{
	InitializeCriticalSection(&CS);
	memset(&oOverlap, 0, sizeof(OVERLAPPED));
	oOverlap.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	PipeIOState = PIO_CONNECT;
	WasCanceled = false;
	CurrentSendMessage = NULL;
	ConnectToSLNum = -1;
//	cout << "CRMOSession=" << this << "-" << (void*)(((char*)this)+sizeof(*this))<< endl;
}

CRMOSession::~CRMOSession()
{
	OutboundList.Reset();
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	CloseHandle(oOverlap.hEvent);
	DeleteCriticalSection(&CS);
}

void CRMOSession::ConnectToNewClient(void)
{
	ConnectToSLNum = -1;
	MustBeDisconnected = false;
	WasCanceled = false;
	fPendingIO = FALSE;
	delete CurrentSendMessage;
	CurrentSendMessage = NULL;
	OutboundList.Reset();
	CRMOStoredData::Reset();
		
BOOL fConnected;
DWORD LastError;

	fConnected = ConnectNamedPipe(hPipe, &oOverlap);
	LastError = GetLastError();
 
	if (fConnected) 
	{
//		FLOG << "Error on ConnectNamedPipe " << LastError << endl;
	};
 
   switch (LastError) 
   { 
      case ERROR_IO_PENDING: 
         fPendingIO = TRUE; 
         break; 
 
      case ERROR_PIPE_CONNECTED: 
         if (SetEvent(oOverlap.hEvent)) 
            break; 
 
		default: 
		{
//			FLOG << "Error on ConnectNamedPipe (in switch)" << LastError << endl;
		};
   } 
	PipeIOState = fPendingIO ? PIO_CONNECT : PIO_READ;
}

void CRMOSession::CheckTimeout(void)
{
	if (PipeIOState!=PIO_CONNECT && LastRcvTime+KEEPALIVETIMEOUT/2<=GetTickCount())
		SendCommand(RMCMD_SRVKEEPALIVE);
	if (LastRcvTime+KEEPALIVETIMEOUT<GetTickCount())
	{
		DisconnectNamedPipe(hPipe);
		ConnectToNewClient();
	};
};

void CRMOSession::ProcessEvent(void)
{
DWORD RES, LastError, CBR;

	if ((PipeIOState&PIO_BREAK)!=0) CancelIo(hPipe);
	SetLastError(0);
	RES = GetOverlappedResult(hPipe, &oOverlap, &CBR, FALSE);
	LastError = GetLastError();
	try
	{
		switch (LastError)
		{
			case ERROR_BROKEN_PIPE:
			case ERROR_PIPE_NOT_CONNECTED:
				throw EEndOfSession();
				break;
			case ERROR_OPERATION_ABORTED:
				break;

			default:
				switch (PipeIOState)
				{
					case PIO_WRITE|PIO_BREAK:
					case PIO_WRITE:
						delete CurrentSendMessage;
						CurrentSendMessage = NULL;
						break;
					case PIO_READ|PIO_BREAK:
//						FLOG << RES << " " << LastError << " " << CBR << endl;
					case PIO_READ:
						TNDRcv.AdjustSize(CBR);
						ProcessMessage(TNDRcv);
						TNDRcv.Reset();
						LastRcvTime = GetTickCount();
						break;
					case PIO_CONNECT|PIO_BREAK:
					case PIO_CONNECT:
						LastRcvTime = GetTickCount();
						SendCommand(RMCMD_WHOAREYOU);
						break;
					case PIO_BREAK:
						break;
				};
		}; // switch(LastError)


		if (CurrentSendMessage==NULL && !OutboundList.IsEmpty())
			CurrentSendMessage = OutboundList.Pop();

		if (CurrentSendMessage!=NULL)// && cbAvail==0)
		{
			WriteFile(hPipe, *CurrentSendMessage, CurrentSendMessage->GetSize(), &RES, &oOverlap);
			PipeIOState = PIO_WRITE;
			return;
		};
		if (MustBeDisconnected) throw EEndOfSession();
		if (TNDRcv.GetSize()==0)
		{
			ReadFile(hPipe, TNDRcv, NPMAXMESSAGESIZE, &RES, &oOverlap);
			PipeIOState = PIO_READ;
			return;
		};
	}
	catch (EEndOfSession)
	{
		PostSysMessage(SCMD_UNREGISTEROPERATOR, 0, InstanceNumber);
/*		if ((ClientType&RMOA_CATEGORYMASK)==RMOA_OPERATOR && 
			(RMOState&RMO_STATEMASK)!=RMO_ALARM &&
			(RMOState&RMO_STATEMASK)!=RMO_BUSY)
		{
			for (int i=0; i<ServiceGroupsList.GetSize(); i++)
				PostSysMessage(SCMD_DECACTOPTINSG, 0, ServiceGroupsList[i]);
		};*/
		FLOG << time << "Error on pipe " << InstanceNumber << " " << RES << " " << LastError<< endl;
		DisconnectNamedPipe(hPipe);
		ConnectToNewClient();
	};
};

bool CRMOSession::ProcessMessage(TSNPData &TND)
{
unsigned __int8 Command;
TSNPData *TND2;
unsigned __int32 ui32, ui32_2;

	TND >> Command;
	switch (Command)
	{
		case RMCMD_SRVKEEPALIVE:
//			FLOG << "Check timeout" << endl;
			break;
		case RMCMD_REQUESTBUSYSTATE:
			PostSysMessage(SCMD_USERPRESSSCROLL, 0, InstanceNumber);
			FLOG << time << "INST# " << InstanceNumber << " Pressed Scroll Lock" << endl;
			break;
		case RMCMD_ANSWERKEYPRESSED:
			PostSysMessage(SCMD_USERPRESSPAUSE, 0, InstanceNumber);
			FLOG << time << "INST# " << InstanceNumber << " Break pressed" << endl;
			break;
		case RMCMD_MYNAME:
			TND >> ComputerName >> ClientType;
			PostSysMessage(SCMD_LOADPIPEINSTRMOPROFILE, 0, InstanceNumber);
			FLOG << time << "Connection request from " << ComputerName.c_str() << endl;
			break;
	//---------------------------------------------------------------------------------------------
		case RMCMD_GETUIDUSERLIST:
			PostSysMessage(SCMD_USERSPROFILEACCESS, Command, InstanceNumber);
			break;
		case RMCMD_GETUSERPROFILE:
		case RMCMD_SETUSERPROFILE:
			TND2 = new TSNPData;
			TND2->CopyUnreadDataFrom(&TND);
			PostSysMessage(SCMD_USERSPROFILEACCESS, Command, InstanceNumber, (unsigned)TND2);
			break;
	//---------------------------------------------------------------------------------------------
		case RMCMD_GETUIDSERGRPLIST:
			PostSysMessage(SCMD_SERVGPROFILEACCESS, Command, InstanceNumber);
			break;
		case RMCMD_GETSERGRPPROFILE:
		case RMCMD_SETSERGRPPROFILE:
			TND2 = new TSNPData;
			TND2->CopyUnreadDataFrom(&TND);
			PostSysMessage(SCMD_SERVGPROFILEACCESS, Command, InstanceNumber, (unsigned)TND2);
			break;
	//---------------------------------------------------------------------------------------------
		case RMCMD_GETSLLIST:
			PostSysMessage(SCMD_SLPPROFILEACCESS, Command, InstanceNumber);
			break;
		case RMCMD_SETSLPROFILE:
			TND2 = new TSNPData;
			TND2->CopyUnreadDataFrom(&TND);
			PostSysMessage(SCMD_SLPPROFILEACCESS, Command, InstanceNumber, (unsigned)TND2);
			break;
	//---------------------------------------------------------------------------------------------
		default:
			break;
	};
	return true;
}

void CRMOSession::SendCommand(unsigned __int8 Command)
{
	TSNPData *TND = new TSNPData;
	(*TND) << Command;
	SendMessage(TND);
}

void CRMOSession::SendMessage(TSNPData *TND)
{
	OutboundList.Push(TND);
	if ((PipeIOState&PIO_READ)!=0) 
	{
		PipeIOState |= PIO_BREAK;
		SetEvent(oOverlap.hEvent);
	};
}


//	TND >> ui32 >> ui32_2;
//			(*TND2) << RMCMD_MYNAME << ui32 << (ui32_2+1);
//			SendMessage(TND2);
