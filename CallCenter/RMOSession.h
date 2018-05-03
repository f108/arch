// RMOSession.h: interface for the CRMOSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RMOSESSION_H__00A0BA47_6E1A_473D_9483_8BD6737F3C3B__INCLUDED_)
#define AFX_RMOSESSION_H__00A0BA47_6E1A_473D_9483_8BD6737F3C3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRVCOMDEFINES.h"
#include "TZSSString.h"
#include "TUIList.h"
#include "SystemObject.h"
#include "RMOWorkSet.h"

#define PIO_CONNECT	0x01
#define PIO_READ	0x02
#define PIO_WRITE	0x03
#define PIO_BREAK	0x10

#define KEEPALIVETIMEOUT 500

class CRMOSession : public CSystemObject, public CRMOStoredData
{
	friend class CConnectionServer;
	class EEndOfSession { };
public:
	CRMOSession();
	virtual ~CRMOSession();

private:
	void ProcessEvent(void);
	bool ProcessMessage(TSNPData &TND);
	void CheckTimeout(void);
	void ConnectToNewClient(void);
	void SendCommand(unsigned __int8 Command);
	void SendMessage(TSNPData *TND);

	unsigned __int32 ClientType;
	unsigned ConnectToSLNum;
	unsigned SLSG;
	unsigned RMOState;

	// for pipe communication
	CRITICAL_SECTION CS;
	OVERLAPPED oOverlap;
	HANDLE hPipe;
	unsigned InstanceNumber;
	BOOL fPendingIO;
	DWORD PipeIOState;
	bool WasCanceled;
	bool MustBeDisconnected;
	TSNPData TNDRcv;
	TSNPData *CurrentSendMessage;
	TCSPtrQueue<TSNPData> OutboundList;
	DWORD LastRcvTime;
};

#endif // !defined(AFX_RMOSESSION_H__00A0BA47_6E1A_473D_9483_8BD6737F3C3B__INCLUDED_)
