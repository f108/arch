// Panel.cpp: implementation of the CPanel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LEDServer.h"
#include "Panel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPanel::CPanel()
{

}

CPanel::~CPanel()
{

}


void CPanel::Run(void)
{
char buf2[50000];
char FileName[512];
DWORD lpw;

//	strcpy(FileName, Path);
///	strcat(FileName, "123");
HANDLE hFile = CreateFile(FileName, GENERIC_READ, 0,0, OPEN_EXISTING,0, 0);

	ReadFile(hFile, buf2, 1047, &lpw, NULL);

	PanelOut(buf2, 1047);

};


void CPanel::PanelOut(char *buf, int BufLen)
{
COMMTIMEOUTS CTO;
DCB dcb;
HANDLE hPort;
DWORD CNT;

	CTO.ReadIntervalTimeout = 0;
	CTO.ReadTotalTimeoutMultiplier = 0;
	CTO.ReadTotalTimeoutConstant = 0;
	CTO.WriteTotalTimeoutConstant = 0xc8;
	CTO.WriteTotalTimeoutMultiplier = 0xa;

//	hPort = CreateFile(PortName, GENERIC_WRITE, 0, 0, 3, 0, NULL);
	SetCommTimeouts(hPort, &CTO);
	GetCommState(hPort, &dcb);
	dcb.BaudRate = 9600;
	dcb.ByteSize = 8;
	dcb.Parity = 3;
	dcb.StopBits = ONESTOPBIT;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.XonLim = 2048;
	dcb.XoffLim = 512;
	dcb.fBinary = 1;
	dcb.fParity =1;
	dcb.XonChar=17;
	dcb.XoffChar=19;

	SetCommState(hPort, &dcb);
	SetupComm(hPort, 5000, 5000);

	dcb.Parity = 3;
	SetCommState(hPort, &dcb);
	WriteFile(hPort, &buf[0], 1, &CNT, NULL);
	Sleep(500);
	dcb.Parity = 4;
	SetCommState(hPort, &dcb);

	WriteFile(hPort, &buf[1], BufLen-1, &CNT, NULL);

	CloseHandle(hPort);

};
