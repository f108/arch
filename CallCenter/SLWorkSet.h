// SLWorkSet.h: interface for the CSLWorkSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLWORKSET_H__C2AB391E_65EE_4B5B_BFFC_6AF3E83D7D66__INCLUDED_)
#define AFX_SLWORKSET_H__C2AB391E_65EE_4B5B_BFFC_6AF3E83D7D66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRVCOMDEFINES.h"
#include "TZSSString.h"
#include "TUIList.h"
#include "SystemObject.h"
#include "Thread.h"

#define		SL_UNATTACHED	0x00000001

class CSLine
{
	friend class CSLWorkSet;
public:
	CSLine();
	~CSLine();
private:
	// stored data
	unsigned __int32 SLServiceGroup;
	TZSuperShortString SLComment;
	// run-time data
	CRITICAL_SECTION CS;
	unsigned __int32 RTState;
	bool MustBeBlocked;
	bool AlarmBlocking;
};

#define SLCount	12
#define HCB_BUFSIZE 32

class HCharBuffer
{
private:
public:
	char buf[HCB_BUFSIZE];
	int curpos;
	int len;
	DWORD CBR;

public:
	HCharBuffer() { curpos=0; len=0; };

	TZSuperShortString GetCommand(void);
	bool SendCommand(TZSuperShortString &str);

	void *GetBufPtr(void) { return &buf[len]; };
	DWORD GetMaxSize(DWORD k) { return min(HCB_BUFSIZE-len, k); };	
	DWORD *GetLPCBR(void) { return &CBR; };
	void CheckBuffer(void);

};

class CSLWorkSet : public CThread, protected CSystemObject
{
public:
	CSLWorkSet(bool CreateSuspend);
	virtual ~CSLWorkSet();

	void SaveTo(TBinaryData *TBD);
	void LoadFrom(TBinaryData *TBD);
	void SaveTo(TSNPData *TND);
	void LoadFrom(TSNPData *TND);

	unsigned GetSLSG(unsigned index);
	unsigned GetSLState(unsigned index);
	void SetSLState(unsigned index, unsigned State);
	unsigned GetRMState(unsigned index);
	void SetRMState(unsigned index, unsigned State);
	void RequestSLsState(void);
	void RequestRMsState(void);

	void LockAllSL(void);
	void CheckSLCount(unsigned SGUD, unsigned ActSLCount, unsigned FirstSL=-1);

protected:
	void Execute(void);
	void ProcessComCommand(TZSuperShortString &str);

	void OnAlarm(unsigned SLNumber);
	void OnDefault(unsigned SLNumber);

private:
	DWORD InitPort(void);
	TZSuperShortString PortName;
	HANDLE hPort;

	CSLine SLList[SLCount];
	HCharBuffer HCB;
	TCSPtrQueue<TZSuperShortString> OutboundQueue;
};

#endif // !defined(AFX_SLWORKSET_H__C2AB391E_65EE_4B5B_BFFC_6AF3E83D7D66__INCLUDED_)
