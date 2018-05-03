// ConnectionServer.h: interface for the CConnectionServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTIONSERVER_H__22651388_5DC3_4CAC_8452_E1075C60AE51__INCLUDED_)
#define AFX_CONNECTIONSERVER_H__22651388_5DC3_4CAC_8452_E1075C60AE51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "TUIList.h"
#include "TZSSString.h"

#include "RMOSession.h"

#define INSTANCESCOUNT 16

class CConnectionServer : public CThread, protected CSystemObject
{
public:
	class ERMNotAttached { };
	class EBadIndex { };

	CConnectionServer(bool);
	virtual ~CConnectionServer();

	void Execute(void);

	void ReloadRMOProfile(CRMOStoredData *CRMOSD);
	void LoadRMOProfile(unsigned PipeInstanceNumber, CRMOStoredData *CRMOSD);
	TZSuperShortString GetPipeInstName(unsigned PipeInstanceNumber);
	unsigned __int32 GetPipeInstRUID(unsigned PipeInstanceNumber);
	unsigned __int32 GetClientType(unsigned PipeInstanceNumber);
	void GetSGList(int index, TUIList *UIL);

	bool SendMessage(unsigned PipeInstanceNumber, TSNPData *TND);

	void FillFreeRMOList(TCSUI32DualList *UIDL, unsigned SG);
	void GetSGListForRMO(unsigned RMOIndex, TUIList *UIL);
	void SetRMOState(unsigned index, unsigned State);
	void ClearRMOState(unsigned index, unsigned State);
	unsigned GetRMOState(unsigned index);
	unsigned GetRMOSLNum(unsigned index);
//	CRMOStoredData *GetRMS(unsigned k);
	unsigned GetRMOIndexBySLNum(unsigned SLNum);

	void SetCALLAttr(unsigned RMOIndex, unsigned SLNum, unsigned SGID);
	void GetCALLAttr(unsigned RMOIndex, unsigned *SLNum, unsigned *SGID);

	int GetCount(void) { return INSTANCESCOUNT; };
//	CRMOSession &operator[](unsigned index) { if (index>=INSTANCESCOUNT) throw EBadIndex(); return RMS[index]; };

private:

//	SetSessionProfile(int index);

	HANDLE hEvents[INSTANCESCOUNT+1];
	CRMOSession RMS[INSTANCESCOUNT];
};

#endif // !defined(AFX_CONNECTIONSERVER_H__22651388_5DC3_4CAC_8452_E1075C60AE51__INCLUDED_)
