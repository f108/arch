// ClientNamedPipe.h: interface for the CClientNamedPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTNAMEDPIPE_H__BD01B0E0_1CFF_4096_B714_14B7FD96A93A__INCLUDED_)
#define AFX_CLIENTNAMEDPIPE_H__BD01B0E0_1CFF_4096_B714_14B7FD96A93A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Thread.h"
#include "..\SRVCOMDEFINES.h"

#include "..\TUIList.h"

#define PIO_CONNECT	1
#define PIO_READ	2
#define PIO_WRITE	3
#define PIO_CANCEL	4

class CClientNamedPipe : protected CThread
{
	class IOPipeException { } ;
public:
	CClientNamedPipe();
	virtual ~CClientNamedPipe();

protected:
	void Execute(void);
	void Init(void);
	char PipeName[512];

	HANDLE hPipe;
	OVERLAPPED oOverlap;
	TSNPData TND;
	DWORD PipeIOState;

	void ProcessMessage(TSNPData &TND);
	void ReadMessage(TSNPData &TND);
	
	void SendCommand(unsigned __int8 Command);
	void SendMessage(TSNPData *TND);

	TCSPtrQueue<TSNPData> OutboundList;

};

#endif // !defined(AFX_CLIENTNAMEDPIPE_H__BD01B0E0_1CFF_4096_B714_14B7FD96A93A__INCLUDED_)
