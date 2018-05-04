// FrameSet.cpp: implementation of the CFrameSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LEDServer.h"
#include "FrameSet.h"

#include "..\pandef.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrameSet::CFrameSet()
{
	FrameCount=0;
}

CFrameSet::~CFrameSet()
{
}

void CFrameSet::LoadFrom(CPanelImage *CPI, int _FrameCount)
{
	FrameCount = _FrameCount + (CPI->AppendNullFrame?1:0);
	if (FrameCount>64) FrameCount=64;
	memcpy(FrameAttr, CPI->AttrBuf, FrameCount);
	RepeatCount = CPI->RepeatCount;

	for (int i=0; i<FrameCount*16; i++)
	{
		for (int k=0; k<32; k++)
		{
			databuf[64*i+k]=0;
			for (int j=0; j<8; j++)
				databuf[64*i+k] |= (CPI->buf[i*256+k*8+j]%2)<<(8-j-1);
			databuf[64*i+k+32]=0;
			for (j=0; j<8; j++)
				databuf[64*i+k+32] |= (CPI->buf[i*256+k*8+j]/2)<<(8-j-1);
		};
	};
}

char STARTTRASNMIT[]="\x0";
char AA55LABEL[]="\x55\xAA";
char ENDTRANSMIT[]="\x02\x0\x0\x03\x0\x8\x1\x9\x2\x1\x4\x2\x9\x0\x4\x0\x0\x1";

DWORD CFrameSet::SendToPort(const char *PortName, bool &ServiceInProgress)
{
COMMTIMEOUTS CTO;
DCB dcb;
HANDLE hPort;
DWORD CNT;
unsigned char ch;

	CTO.ReadIntervalTimeout = 0;
	CTO.ReadTotalTimeoutMultiplier = 0;
	CTO.ReadTotalTimeoutConstant = 0;
	CTO.WriteTotalTimeoutConstant = 0xc8;
	CTO.WriteTotalTimeoutMultiplier = 0xa;

	hPort = CreateFile(PortName, GENERIC_WRITE, 0, 0, 3, 0, NULL);
	SetCommTimeouts(hPort, &CTO);
	GetCommState(hPort, &dcb);
	dcb.BaudRate = 9600; dcb.ByteSize = 8; dcb.Parity = 3; dcb.StopBits = ONESTOPBIT;
	dcb.fRtsControl = RTS_CONTROL_DISABLE; dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.XonLim = 2048; dcb.XoffLim = 512; dcb.fBinary = 1; dcb.fParity =1; dcb.XonChar=17;
	dcb.XoffChar=19;
	SetCommState(hPort, &dcb); SetupComm(hPort, 5000, 5000);

	dcb.Parity = 3; SetCommState(hPort, &dcb);
	WriteFile(hPort, STARTTRASNMIT, sizeof(STARTTRASNMIT)-1, &CNT, NULL);
	Sleep(50);
	dcb.Parity = 4; SetCommState(hPort, &dcb);
	WriteFile(hPort, AA55LABEL, sizeof(AA55LABEL)-1, &CNT, NULL);
	ch = FrameCount;
	WriteFile(hPort, &ch, 1, &CNT, NULL);
	WriteFile(hPort, FrameAttr, FrameCount, &CNT, NULL);
	for (int i=0; i<FrameCount; i++)
	{
		WriteFile(hPort, &databuf[1024*i], 1024, &CNT, NULL);
		if (!ServiceInProgress) break;
	};

	WriteFile(hPort, ENDTRANSMIT, sizeof(ENDTRANSMIT)-1, &CNT, NULL);
	CloseHandle(hPort);

	return 0;
}

DWORD CFrameSet::GetExpositionTime(void)
{
int ret=0;
int Defect=0;
int len;
	for (int i=0; i<FrameCount; i++)
	{
		switch (FrameAttr[i]&15)
		{
			case 0: case 1: case 7: case 8: len = 32; break;
			case 3: case 2: case 4: case 5: len = 2; Defect=-1000; break;
			case 0xB: len = 1; break;
			case 0xE: len = 1; break;
		};
		switch ((FrameAttr[i]>>6)&3)
		{
			case 0: ret +=  3500*len/8/4; break;
			case 1: ret +=  7000*len/4/8; break;
			case 2: ret += 14000*len/2/16; break;
			case 3: ret += 28000*len/1/32; break;
		};
		switch ((FrameAttr[i]>>4)&3)
		{
			case 0: ret += 0; break;
			case 1: ret += 2000; break;
			case 2: ret += 4000; break;
			case 3: ret += 8000; break;
		};
	};
	return ret*RepeatCount+Defect;
}

DWORD CFrameSet::GetTrasmissionTime(void)
{
	return (1+5+2+12+(1024+1)*FrameCount)*10000/9600;
}
