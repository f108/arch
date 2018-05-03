// ServiceGroup.h: interface for the CServiceGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICEGROUP_H__A1C1A57A_18DE_4137_889F_77BF40CFFC6C__INCLUDED_)
#define AFX_SERVICEGROUP_H__A1C1A57A_18DE_4137_889F_77BF40CFFC6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRVCOMDEFINES.h"
#include "TZSSString.h"
#include "TUIList.h"
#include "SystemObject.h"

#include "WSDEFINES.h"     

class CRMOStoredData;

class CServiceGroup  
{
	friend class CServiceGroupList;
public:
	CServiceGroup();
	virtual ~CServiceGroup();

	void SaveTo(TBinaryData *TBD);
	void LoadFrom(TBinaryData *TBD);

	void SaveTo(TSNPData *TND);
	void LoadFrom(TSNPData *TND);
private:
	unsigned __int32 SGID;
	TZSuperShortString SGCaption;
	TZSuperShortString SGDescription;
	DWORD Color;
	bool BlinkBanner;
	int SGSearchMethod;
	TUIList	RMIDOrder;
	bool UseQueue;
	unsigned __int8 QueueType;
	bool UsingQueueByOperatorCount;
	unsigned __int8 OperatorCount;

	unsigned ActiveOperatorCounter;

protected: // run-time data
	TUIList RMOIndexList;
	unsigned LastUsingRMOPos;
};

class CServiceGroupList : protected CSystemObject
{
public:
	CServiceGroupList();
	virtual ~CServiceGroupList();

	void SaveTo(TBinaryData *TBD);
	void LoadFrom(TBinaryData *TBD);

	void SaveSGUIDListTo(TSNPData *TND);
	bool SaveTo(unsigned __int32 SGUID, TSNPData *TND);
	bool LoadFrom(unsigned __int32 SGUID, TSNPData *TND);
	bool SaveInfoForBanner(unsigned __int32 SGUID, TSNPData *TND);

	void RegisterOperator(unsigned index, TUIList &UIL);
	void UnregisterOperator(unsigned index);

	void IncAOCounter(CRMOStoredData *CRMO);
	void DecAOCounter(CRMOStoredData *CRMO);
	void DecAOCounter(unsigned SGUID);

	void AddRMOInServ(unsigned __int32 SGUID);
	void DeleteRMOInServ(unsigned __int32 SGUID);
	unsigned GetActiveSLCountInSG(unsigned __int32 SGUID);
	unsigned GetActiveRMCountInSG(unsigned SGUID, unsigned ActCount);

	int GetRMOIndexForCallServ(TCSUI32DualList &FreeRMOList, unsigned SG);

private:
	TPtrList<CServiceGroup> SGList;
};

#endif // !defined(AFX_SERVICEGROUP_H__A1C1A57A_18DE_4137_889F_77BF40CFFC6C__INCLUDED_)
