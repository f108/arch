// RMOWorkSet.h: interface for the CRMOWorkSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RMOWORKSET_H__029EB29C_0EA7_4E21_B64A_D1593164CC10__INCLUDED_)
#define AFX_RMOWORKSET_H__029EB29C_0EA7_4E21_B64A_D1593164CC10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRVCOMDEFINES.h"
#include "WSDEFINES.h"
#include "TZSSString.h"
#include "TUIList.h"
#include "SystemObject.h"

#define		RMO_BUSY					0x00000001
#define		RMO_WAITCALL				0x00000002
#define		RMO_ALARM					0x00000004
#define		RMO_INUSE					0x00000010
#define		RMO_CONNECTIONINPROGRESS	0x00000020
#define		RMO_STATEMASK				0x000000FF
//#define		RMO_SUPERVISOR				0x00010000
#define		RMO_REQBUSYSTATE			0x00000100

class TBinaryData;

class CRMOStoredData
{
public:
	unsigned __int32 RMOUID;
	TZSuperShortString ComputerName;
	unsigned __int32 Attr;
	TUIList ServiceGroupsList;
	unsigned __int8 RMLineNumber;

	CRMOStoredData();
	void Reset(void);
	void CopyFrom(CRMOStoredData *CRMOSD);
};

class CRMO : protected CRMOStoredData
{
	friend class CRMOList;
public:
	CRMO();
	virtual ~CRMO();

	void SaveTo(TBinaryData *TBD);
	void LoadFrom(TBinaryData *TBD);

	void SaveTo(TSNPData *TND);
	void LoadFrom(TSNPData *TND);
};

class CRMOList : protected CSystemObject
{
	friend class CSystemKernel;
public:
	CRMOList();
	virtual ~CRMOList();

private:
	void SaveTo(TBinaryData *TBD);
	void LoadFrom(TBinaryData *TBD);

	void SaveRMUIDListTo(TSNPData *TND);
	bool SaveTo(unsigned __int32 RMOUID, TSNPData *TND);
	bool LoadFrom(unsigned __int32 RMOUID, TSNPData *TND);

	CRMOStoredData *GetRMODataByUID(unsigned __int32 RUID);
	CRMOStoredData *GetRMODataByName(TZSuperShortString &str);
	CRMOStoredData *GetRMODataByNameAndType(TZSuperShortString &str, unsigned __int32 Type);
	unsigned __int32 GetUserAttr(unsigned __int32 RUID);
	void CreateDefaultStartUpProfile(void);

	TPtrList<CRMO> RMOList;
};

#define RMOCount 12

#endif // !defined(AFX_RMOWORKSET_H__029EB29C_0EA7_4E21_B64A_D1593164CC10__INCLUDED_)
