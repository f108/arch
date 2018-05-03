// RMOClientPipe.cpp: implementation of the CRMOClientPipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RMO.h"
#include "RMOClientPipe.h"
#include "..\WSDEFINES.h"

#include "..\TZSSString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRMOClientPipe::CRMOClientPipe(CRMOApp *p)
{
	Parent = p;
}

CRMOClientPipe::~CRMOClientPipe()
{

}

unsigned __int32 CRMOClientPipe::GetClientType(void)
{
	return RMOA_OPERATOR;
}

void CRMOClientPipe::ProcessException(unsigned k)
{
	switch (k)
	{
		case PE_CONNECTTOSERVER:
			Parent->SetText("", 0);
			Parent->SetSubText("Поиск сервера");
			break;
		case PE_CONNECTIONINPROGRESS:
			Parent->SetSubText("Вход в систему");
			break;
		case PE_STAYOFFLINE:
			Parent->SetSubText("Соединение отвергнуто");
			break;
		case PE_CONNECTED:
			Parent->SetSubText("Подключились");
			break;
		case PE_INIT:
			Parent->SetSubText("Инициализация");
			break;
		case PE_INSERV:
			Parent->SetSubText("В обслуживании");
			break;
	};
}

void CRMOClientPipe::ProcessMessage(TSNPData &TND)
{
unsigned __int8 Command;
TZSuperShortString str;
unsigned __int32 ui32;
bool k;

	TND >> Command;

	switch (Command)
	{
		case RMCMD_SETBUSYSTATE:
			Parent->SetText("BUSY", 0xBBBBBB);
			Parent->SetSubText("РМО занято");
			Parent->KillScrollTimer();
			return;
		case RMCMD_SETINSERVSTATE:
			Parent->SetText("", 0);
			Parent->SetSubText("В обслуживании");
			Parent->KillScrollTimer();
			return;
		case RMCMD_SHOWRINGBANNER:
			Parent->SetText("ВЫЗОВ", 0x0000FF, true);
			Parent->SetScrollTimer();
			return;
		case RMCMD_SHOWCALLBANNER:
			TND >> str >> ui32 >> k;
			Parent->SetText(str.c_str(), ui32, k);
			Parent->KillScrollTimer();
			return;
		case RMCMD_SETALARMSTATE:
			Parent->SetText("АВАРИЯ", 0x0000FF, true);
			Parent->SetSubText("Обрыв линии");
			Parent->KillScrollTimer();
			return;
		case RMCMD_SETRMOSLNUM:
			TND >> ui32;
			Parent->SetSLNum(ui32);
			return;
		case RMCMD_SETQUEUESTATE:
			TND >> ui32;
			Parent->SetQueueState(ui32);
		default:
			break;
	};
	TND.ResetPos();
	CClientNamedPipe::ProcessMessage(TND);
}

