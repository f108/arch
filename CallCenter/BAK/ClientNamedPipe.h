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

#define PIO_CONNECT		0x01
#define PIO_READ		0x02
#define PIO_WRITE		0x03
#define PIO_CANCEL		0x04
#define PIO_SHUTDOWN	0x05
#define PIO_BREAK		0x10

#define PE_CONNECTTOSERVER			0x01
#define PE_CONNECTIONINPROGRESS		0x02
#define PE_STAYOFFLINE				0x03
#define PE_CONNECTED				0x04
#define PE_INIT						0x05
#define PE_INSERV					0x06

class CClientNamedPipe : protected CThread
{
	class EEndOfSession { } ;
	class IOPipeException { } ;
public:
	CClientNamedPipe();
	virtual ~CClientNamedPipe();

	void Stop(void);

	void SendCommand(unsigned __int8 Command);
	void SendMessage(TSNPData *TND);

protected:
	void Execute(void);
	void Init(void);
	char PipeName[512];

	HANDLE hPipe;
	OVERLAPPED oOverlap;
	TSNPData TND;
	DWORD PipeIOState;

	virtual void ProcessMessage(TSNPData &TND);
	virtual unsigned __int32 GetClientType(void);
	virtual void ProcessException(unsigned);

	void ReadMessage(TSNPData &TND);
	
	TCSPtrQueue<TSNPData> OutboundList;

};

#endif // !defined(AFX_CLIENTNAMEDPIPE_H__BD01B0E0_1CFF_4096_B714_14B7FD96A93A__INCLUDED_)
