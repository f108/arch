// SLWorkSet.cpp: implementation of the CSLWorkSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SLWorkSet.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSLine::CSLine()
{
	InitializeCriticalSection(&CS);
	SLServiceGroup = SL_UNATTACHED;
	RTState = CCS_BLOCKED;
	MustBeBlocked = false;
	AlarmBlocking = false;
}

CSLine::~CSLine()
{
	DeleteCriticalSection(&CS);
}

//####################################################################

void HCharBuffer::CheckBuffer(void)
{
	len += CBR; CBR=0;
	if (len==0) return;
int HMI=0;
int HEQ=0;
	for (unsigned k=0; k<len;)
	{
		if (buf[k]=='-') HMI++;
		if (buf[k]=='=') HEQ++;

		if ((k!=0 && buf[k]=='-' && (HMI==0 || (HMI==1 && HEQ==0) || (HMI==1 && HEQ>0))) ||
			(k!=0 && HMI==0 && HEQ!=0))
		{
			memcpy(&buf[0], &buf[k], len-k);
			len-=k; k=0;
			HEQ=0; HMI=0;
			continue;
		};
		k++;
	};
	if (HMI==0) len=0;
	return;
};

TZSuperShortString HCharBuffer::GetCommand(void)
{
	if (len==0 || buf[0]!='-') return TZSuperShortString();
unsigned int k;
	for (k=1; k<len; k++)
	{
		if (buf[k]=='=')
		{
		TZSuperShortString ret;
			ret = TZSuperShortString(&buf[0], k+1);
			memcpy(&buf[0], &buf[k+1], len-k);
			len-= k+1;
			return ret;
		};
	};
	return TZSuperShortString();
};


//####################################################################

CSLWorkSet::CSLWorkSet(bool CreateSuspend) : CThread(CreateSuspend)
{
	hPort=INVALID_HANDLE_VALUE;
	PortName = "\\\\.\\COM28";
}

CSLWorkSet::~CSLWorkSet()
{

}

void CSLWorkSet::SaveTo(TBinaryData *TBD)
{
	for (int i=0; i<SLCount; i++)
		(*TBD) << SLList[i].SLServiceGroup << SLList[i].SLComment;
}

void CSLWorkSet::LoadFrom(TBinaryData *TBD)
{
	for (int i=0; i<SLCount; i++)
		(*TBD) >> SLList[i].SLServiceGroup >> SLList[i].SLComment;
}

void CSLWorkSet::SaveTo(TSNPData *TND)
{
	for (int i=0; i<SLCount; i++)
		(*TND) << SLList[i].SLServiceGroup << SLList[i].SLComment;
}

void CSLWorkSet::LoadFrom(TSNPData *TND)
{
unsigned __int32 k;
	(*TND) >> k;
	if (k<0 || k>=SLCount) return;
	(*TND) >> SLList[k].SLServiceGroup >> SLList[k].SLComment;
	PostSysMessage(SCMD_SAVEPROFILE);
}

//====================================================================================================
unsigned CSLWorkSet::GetSLSG(unsigned index)
{
	if (index>=SLCount) return 0;
unsigned ret;
	EnterCriticalSection(&SLList[index].CS);
	ret = SLList[index].SLServiceGroup;
	LeaveCriticalSection(&SLList[index].CS);
	return ret;
}

unsigned CSLWorkSet::GetSLState(unsigned index)
{
	if (index>=SLCount) return 0;
unsigned ret;
	EnterCriticalSection(&SLList[index].CS);
	ret = SLList[index].RTState;
	LeaveCriticalSection(&SLList[index].CS);
	return ret;
}

void CSLWorkSet::SetSLState(unsigned index, unsigned State)
{
	if (index>=SLCount) return;
char buf[30];
	sprintf(buf, "-KK%X%X%X%X=", index, index, State, State);
	OutboundQueue.Push(new TZSuperShortString(buf));
}

unsigned CSLWorkSet::GetRMState(unsigned index)
{
	return 0;
}

void CSLWorkSet::SetRMState(unsigned index, unsigned State)
{
	if (index>=SLCount) return;
char buf[30];
	sprintf(buf, "-RR%X%X%X%X=", index, index, State, State);
	OutboundQueue.Push(new TZSuperShortString(buf));
}
//====================================================================================================

void CSLWorkSet::RequestSLsState(void)
{
	OutboundQueue.Push(new TZSuperShortString("-SS22="));
	OutboundQueue.Push(new TZSuperShortString("-SS33="));
}

void CSLWorkSet::RequestRMsState(void)
{
	OutboundQueue.Push(new TZSuperShortString("-SS11="));
//	RequestSLsState();
}

//====================================================================================================
void CSLWorkSet::OnAlarm(unsigned SLNumber)
{
	if (SLList[SLNumber].MustBeBlocked==false)
	{
	int i;
		for (i=SLNumber+1; i<SLCount; i++)
		{
			if (SLList[i].SLServiceGroup==SLList[SLNumber].SLServiceGroup &&
				SLList[i].MustBeBlocked==true && SLList[i].AlarmBlocking==false)
			{
				SLList[i].MustBeBlocked = false;
				if (SLList[i].RTState==CCS_BLOCKED)
					SetSLState(i, CCS_SLSETTODEFAULT);
				return;
			};
		};
		for (i=0; i<SLNumber; i++)
		{
			if (SLList[i].SLServiceGroup==SLList[SLNumber].SLServiceGroup &&
				SLList[i].MustBeBlocked==true && SLList[i].AlarmBlocking==false)
			{
				SLList[i].MustBeBlocked = false;
				if (SLList[i].RTState==CCS_BLOCKED)
					SetSLState(i, CCS_SLSETTODEFAULT);
				return;
			};
		};
	};
}

void CSLWorkSet::OnDefault(unsigned SLNumber)
{
	PostSysMessage(SCMD_CHECKSLCOUNT, 0, SLNumber, SLList[SLNumber].SLServiceGroup);
}

void CSLWorkSet::CheckSLCount(unsigned SGUID, unsigned ActSLCount, unsigned FirstSL)
{
__int32 TAC=0, i;
	for (i=0; i<SLCount; i++)
		if (SLList[i].SLServiceGroup==SGUID && SLList[i].RTState!=CCS_BLOCKED &&
			SLList[i].RTState!=CCS_ALARM2 && SLList[i].MustBeBlocked!=true) TAC++;
	FLOG << time << "CHECK SL: " << SGUID << " " << ActSLCount << " " << TAC << endl;

	if (TAC>=ActSLCount) // блокируем лишние линии
	{
		for (i=SLCount-1; i>=0; i--)
		{
			if (TAC<=ActSLCount) return;
			if (SLList[i].SLServiceGroup==SGUID && SLList[i].RTState!=CCS_BLOCKED &&
				SLList[i].RTState!=CCS_ALARM2 && SLList[i].MustBeBlocked!=true)
			{
				SLList[i].MustBeBlocked = true;
				TAC--;
			};

			if (SLList[i].SLServiceGroup==SGUID && ActSLCount==0 && SLList[i].RTState!=CCS_ALARM2)
			{
				SLList[i].MustBeBlocked = true;
				SetSLState(i, CCS_SLBLOCK);
			};
		};
		return;
	} 
	else
	{
		for (i=0; i<SLCount; i++) // разблокируем заблокированные рабочие линии
		{
			if (TAC>=ActSLCount) return;
			if (SLList[i].SLServiceGroup==SGUID && 
				(SLList[i].RTState==CCS_BLOCKED || SLList[i].RTState==CCS_DEFAULT) &&
				SLList[i].MustBeBlocked==true)
			{
				SLList[i].MustBeBlocked=false;
				SetSLState(i, CCS_SLSETTODEFAULT);
				TAC++;
			};
		};
	};
}

void CSLWorkSet::LockAllSL(void)
{
unsigned k=SL_UNATTACHED;

	for (int i=0; i<12; i++) 
	{
		SetSLState(i, CCS_SLSETTODEFAULT);
			SLList[i].MustBeBlocked = true;
	};
}

//=======================================================================
void CSLWorkSet::Execute(void)
{
	FLOG << time << "Start CSLWorkSet" << endl;

COMSTAT CS;
TZSuperShortString str;
TZSuperShortString *outstr;
DWORD cbw;

	InitPort();

	LockAllSL();
	for (int i=0; i<15; i++) SetSLState(i, 0xf);
	RequestSLsState();
	RequestRMsState();

	CS.cbInQue = 0;
	HCB.GetMaxSize(CS.cbInQue);

	for (;!Terminated;)
	{
//		cout << "aa" << HCB.GetMaxSize(CS.cbInQue) << endl;
		try
		{
			ReadFile(hPort, HCB.GetBufPtr(), HCB.GetMaxSize(100), HCB.GetLPCBR(), NULL);
			for (;;)
			{
				HCB.CheckBuffer();
				str = HCB.GetCommand();
				if (str.length()!=0)
				{
					ProcessComCommand(str);
				} else break;
			};
			if (!OutboundQueue.IsEmpty())
			{
				outstr = OutboundQueue.Pop();
//					FLOG << "PortOut: " << outstr->c_str() << endl;
				WriteFile(hPort, outstr->c_str(), outstr->length(), &cbw, NULL);
				delete outstr;
			};
		}
		catch (...)
		{
			FLOG << time << "Exception in SLWorkSet" << endl;
		};
	};
}

void CSLWorkSet::ProcessComCommand(TZSuperShortString &str)
{
unsigned PTNum, PTState;
//	FLOG << "PortIn : " << str.c_str() << endl;

	if (str[1]=='T' && str[2]=='L')
	{
		PTNum = (str[4]>='0'&&str[4]<='9')?str[4]-0x30:((str[4]>='a'&&str[4]<='f')?(unsigned char)str[4]-97+10:0);
		PTState = (str[6]>='0'&&str[6]<='9')?str[6]-0x30:((str[6]>='a'&&str[6]<='f')?(unsigned char)str[6]-97+10:0);
		if (PTNum>=SLCount) return;

		if (PTState!=CCS_ALARM2)
			SLList[PTNum].AlarmBlocking = false;
		switch (PTState)
		{
			case CCS_RING:
				FLOG << time << "RING on line " << PTNum << " " << PTState<< endl;
//				if (SLList[PTNum].RTState!=CCS_RING)
				PostSysMessage(SCMD_ADDRINGINQUEUE, 0, PTNum, SLList[PTNum].SLServiceGroup);
				SLList[PTNum].RTState = CCS_RING;
				break;
			case CCS_CALLINPROGRESS:
			case CCS_COMBUSY:
				break;
			case CCS_BLOCKED:
				SLList[PTNum].MustBeBlocked = false;
			case CCS_ALARM:
				break;
			case CCS_ALARM2:
//				SLList[PTNum].AlarmBlocking = true;
				PostSysMessage(SCMD_CHECKSLCOUNT, 0, PTNum, SLList[PTNum].SLServiceGroup);
//				SetSLState(PTNum, CCS_SLBLOCK);
				break;
			case CCS_DEFAULT:
				if (SLList[PTNum].RTState==CCS_ALARM2) PostSysMessage(SCMD_CHECKSLCOUNT, 0, PTNum, SLList[PTNum].SLServiceGroup);
				if (SLList[PTNum].MustBeBlocked==true) SetSLState(PTNum, CCS_SLBLOCK);
			case CCS_HOLD:
				PostSysMessage(SCMD_DELETERINGINQUEUE, 0, PTNum);
				break;
		};
		SLList[PTNum].RTState = PTState;
	} else if (str[1]=='R' && str[2]=='M')
	{
		PTNum = (str[4]>='0'&&str[4]<='9')?str[4]-0x30:((str[4]>='a'&&str[4]<='f')?(unsigned char)str[4]-97+10:0);
		PTState = (str[6]>='0'&&str[6]<='9')?str[6]-0x30:((str[6]>='a'&&str[6]<='f')?(unsigned char)str[6]-97+10:0);
		switch (PTState)
		{
			case CCS_RMALARM:
				PostSysMessage(SCMD_RMOALARM, 0, PTNum);
				break;
			case CCS_RMINUSE:
				PostSysMessage(SCMD_SETRMOINSERV, 0, PTNum);
				break;
		};
	} else if (str[1]=='S' && str[2]=='R')
	{
		for (int i=0; i<SLCount; i++)
			if (str[i+4]=='0') PostSysMessage(SCMD_RMOALARM, 0, i);
	} else if (str[1]=='S' && str[2]=='T')
	{
//		FLOG << "SLState::" << str.c_str() << endl;
		FLOG << time << "SLST-AMSC [";
		for (int i=0; i<SLCount; i++) 
		{
			FLOG << SLList[i].AlarmBlocking << SLList[i].MustBeBlocked << str[i+4] << "x";
			if (i!=SLCount-1) FLOG << ".";
			SLList[i].RTState = (str[i+4]>='0'&&str[i+4]<='9')?str[i+4]-0x30:((str[i+4]>='a'&&str[i+4]<='f')?(unsigned char)str[i+4]-97+10:0);
			if (SLList[i].RTState==CCS_DEFAULT && SLList[i].MustBeBlocked)
				SetSLState(i, CCS_SLBLOCK);
		};
		FLOG << "]" << endl;

	};
}

DWORD CSLWorkSet::InitPort(void)
{
	if (hPort!=INVALID_HANDLE_VALUE) CloseHandle(hPort);
	hPort = CreateFile(PortName.c_str(), GENERIC_READ | GENERIC_WRITE,
				0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPort==INVALID_HANDLE_VALUE) return GetLastError();

DCB dcb;
	memset(&dcb,0,sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);
	GetCommState(hPort, &dcb);
	dcb.BaudRate = CBR_9600;
	dcb.ByteSize = 8;
	dcb.Parity   = EVENPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fInX = dcb.fOutX = FALSE;
	dcb.fAbortOnError =FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = DTR_CONTROL_DISABLE;
	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;
	if (!SetCommState(hPort,&dcb)) return GetLastError();

COMMTIMEOUTS com_t_out;
	com_t_out.ReadIntervalTimeout = 1;
	com_t_out.ReadTotalTimeoutMultiplier = 3;
	com_t_out.ReadTotalTimeoutConstant = 1;
	com_t_out.WriteTotalTimeoutMultiplier = 10;
	com_t_out.WriteTotalTimeoutConstant = 200;
	if (!SetCommTimeouts(hPort, &com_t_out)) return GetLastError();
	if (!SetupComm(hPort, 512, 512)) return GetLastError();
	return ERROR_SUCCESS;
}
