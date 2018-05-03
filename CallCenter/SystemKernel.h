// SystemKernel.h: interface for the CSystemKernel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMKERNEL_H__C456BA91_3811_4428_AB25_A4CA87062A17__INCLUDED_)
#define AFX_SYSTEMKERNEL_H__C456BA91_3811_4428_AB25_A4CA87062A17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TUIList.h"
#include "RMOWorkSet.h"
#include "ServiceGroup.h"
#include "SLWorkSet.h"
#include "ConnectionServer.h"
#include "Thread.h"
#include "SystemObject.h"
#include "SystemMessageQueueWithTimer.h"

struct SYSCOMMAND
{
	unsigned __int64 data;
	inline SYSCOMMAND() { data = 0; };
	inline SYSCOMMAND(unsigned __int64 ui64) { data = ui64; };
	inline void operator=(unsigned __int64 &ui64) { data = ui64; };
	inline SYSCOMMAND(unsigned __int8 Command, unsigned __int8 SubCommand=0, unsigned __int16 data1=NULL, unsigned __int32 data2=NULL) { data = ((unsigned __int64)Command<<(64-8))|((unsigned __int64)SubCommand<<(64-16))|((unsigned __int64)data1<<32)|data2; };
	inline operator unsigned __int64() { return data; };
	inline unsigned __int8 SYSCOMMAND::GetCommand(void) { return unsigned __int8(data>>(64-8)); };
	inline unsigned __int8 SYSCOMMAND::GetSubCommand(void) { return unsigned __int8((data>>(64-16))&0xff); };
	inline unsigned __int16 SYSCOMMAND::GetData1(void) { return unsigned __int16((data>>(32))&0xffff); };
	inline unsigned __int32 SYSCOMMAND::GetData2(void) { return unsigned __int32(data&0xffffffff); };
};

class CSystemKernel : public CThread
{
public:
	CSystemKernel(bool);
	virtual ~CSystemKernel();

	void PostSysMessage(unsigned __int8 Command, unsigned __int8 SubCommand=0, unsigned __int16 data1=NULL, unsigned __int32 data2=NULL);
	void PostSysMessage(SYSCOMMAND &Command);
	void PostSysMessageWI(DWORD Interval, unsigned __int8 Command, unsigned __int8 SubCommand=0, unsigned __int16 data1=NULL, unsigned __int32 data2=NULL);
	void PostSysMessageWI(DWORD Interval, SYSCOMMAND &Command);

private:
	void Execute(void);

	void LoadProfile(void);
	void SaveProfile(void);

	void CheckOprInSG(void);

	bool SendAnswerRequest(unsigned index, unsigned SLNum, unsigned SGNum);
	bool FindCallForRMO(unsigned index);
	bool FindRMOForCall(unsigned SLNum, unsigned SGNum);
	bool EstablishConnection(unsigned index);
	bool BreakConnection(unsigned index);
	bool CancelAnswerRequest(unsigned SLNum);
	bool CancelAnswerRequestAndSetBusyState(unsigned SLNum);
	bool SetBusyState(unsigned index);
	int GetIndexForAnswerRequest(unsigned SLNum);
	void SendQueueState(void);

	CSLWorkSet CSLWS;
	CConnectionServer CCS;

	TCSEVUI64Queue SysMessageQueue;
	TCSUI32DualList RingQueue;
	TCSUI32DualList FreeRmoQueue;
	CSystemMessageQueueWithTimer CTMQ;

	CRMOList RMOList;
	CServiceGroupList SGList;

};

#endif // !defined(AFX_SYSTEMKERNEL_H__C456BA91_3811_4428_AB25_A4CA87062A17__INCLUDED_)
