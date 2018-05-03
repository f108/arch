// RMOWorkSet.cpp: implementation of the CRMOWorkSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RMOWorkSet.h"

#include "TBinaryData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRMOStoredData::CRMOStoredData()
{
	Reset();
}

void CRMOStoredData::Reset(void)
{
	RMOUID=0;
	ComputerName="";
	Attr=0;
//	ServiceGroupsList.Reset();
	RMLineNumber=-1;
}

void CRMOStoredData::CopyFrom(CRMOStoredData *CRMOSD)
{
	RMOUID=CRMOSD->RMOUID;
	ComputerName=CRMOSD->ComputerName;
	Attr=CRMOSD->Attr;
	ServiceGroupsList=CRMOSD->ServiceGroupsList;
	RMLineNumber=CRMOSD->RMLineNumber;
}

//==========================================================================================
CRMO::CRMO()
{
}

CRMO::~CRMO()
{

}

void CRMO::SaveTo(TBinaryData *TBD)
{
	(*TBD) << RMOUID << ComputerName << Attr << ServiceGroupsList << RMLineNumber;
}

void CRMO::LoadFrom(TBinaryData *TBD)
{
	(*TBD) >> RMOUID >> ComputerName >> Attr >> ServiceGroupsList >> RMLineNumber;
}

void CRMO::SaveTo(TSNPData *TND)
{
	(*TND) << RMOUID << ComputerName << Attr << ServiceGroupsList << RMLineNumber;
}

void CRMO::LoadFrom(TSNPData *TND)
{
	(*TND) >> RMOUID >> ComputerName >> Attr >> ServiceGroupsList >> RMLineNumber;
}

//==========================================================================================
CRMOList::CRMOList()
{
}

CRMOList::~CRMOList()
{
}

void CRMOList::SaveTo(TBinaryData *TBD)
{
	(*TBD) << RMOList.GetCount();
	for (unsigned i=0; i<RMOList.GetCount(); i++)
	{
		RMOList[i]->SaveTo(TBD);
	};
}

void CRMOList::LoadFrom(TBinaryData *TBD)
{
	RMOList.Reset();
unsigned __int32 Size;
CRMO *RMO;
	(*TBD) >> Size;
	for (unsigned i=0; i<Size; i++)
	{
		RMO = new CRMO;
		RMO->LoadFrom(TBD);
		RMOList.Add(RMO);
	};
}

void CRMOList::SaveRMUIDListTo(TSNPData *TND)
{
	(*TND) << RMOList.GetCount();
	for (unsigned i=0; i<RMOList.GetCount(); i++)
		(*TND) << RMOList[i]->RMOUID << RMOList[i]->ComputerName << RMOList[i]->Attr;
}

bool CRMOList::SaveTo(unsigned __int32 RMOUID, TSNPData *TND)
{
unsigned pos;
	for (pos=0; pos<RMOList.GetCount(); pos++)
		if (RMOList[pos]->RMOUID==RMOUID)
		{
			RMOList[pos]->SaveTo(TND);
			return true;
		};
	return false;
}

bool CRMOList::LoadFrom(unsigned __int32 RMOUID, TSNPData *TND)
{
	if (RMOUID!=0xFFFFFFFF)
	{
	unsigned pos;
		for (pos=0; pos<RMOList.GetCount(); pos++)
			if (RMOList[pos]->RMOUID==RMOUID) break;
		RMOList[pos]->LoadFrom(TND);
		PostSysMessage(SCMD_SAVEPROFILE);
		PostSysMessage(SCMD_RELOADRMOPROFILE, 0, 0, RMOUID);
		return true;
	};

unsigned __int32 NUID = 10;
bool NUIDMustBeChange=false;
	for (;;)
	{
		for (unsigned i=0; i<RMOList.GetCount(); i++)
			if (RMOList[i]->RMOUID==NUID) 
			{
				NUIDMustBeChange = true;
				break;
			};
		if (NUIDMustBeChange==false) break;
		NUID++;
		NUIDMustBeChange = false;
	};

CRMO *RMO = new CRMO;
	RMO->LoadFrom(TND);
	RMO->RMOUID = NUID;
	RMOList.Add(RMO);
	PostSysMessage(SCMD_SAVEPROFILE);
	PostSysMessage(SCMD_RELOADRMOPROFILE, 0, 0, RMOUID);
	return true;
}

CRMOStoredData *CRMOList::GetRMODataByUID(unsigned __int32 RMOUID)
{
	for (unsigned pos=0; pos<RMOList.GetCount(); pos++)
		if (RMOList[pos]->RMOUID==RMOUID)
		{
			return dynamic_cast<CRMOStoredData*>(RMOList[pos]);
		};
	return NULL;
}

CRMOStoredData *CRMOList::GetRMODataByName(TZSuperShortString &str)
{
	for (unsigned pos=0; pos<RMOList.GetCount(); pos++)
		if (RMOList[pos]->ComputerName==str)
		{
			return dynamic_cast<CRMOStoredData*>(RMOList[pos]);
		};
	return NULL;
}

CRMOStoredData *CRMOList::GetRMODataByNameAndType(TZSuperShortString &str, unsigned __int32 Type)
{
	for (unsigned pos=0; pos<RMOList.GetCount(); pos++)
		if (RMOList[pos]->ComputerName==str && ((RMOList[pos]->Attr&RMOA_CATEGORYMASK)==Type))
		{
			return dynamic_cast<CRMOStoredData*>(RMOList[pos]);
		};
	return NULL;
}

unsigned __int32 CRMOList::GetUserAttr(unsigned __int32 RUID)
{
	for (unsigned pos=0; pos<RMOList.GetCount(); pos++)
		if (RMOList[pos]->RMOUID==RUID)
		{
			return RMOList[pos]->Attr;
		};
	return 0;
}

void CRMOList::CreateDefaultStartUpProfile(void)
{
CRMO *RMO = new CRMO;
	RMO->ComputerName = "MPL";
	RMO->Attr = RMOA_ADMINISTRATOR|RMOA_CANCHNGUSERPF;
	RMO->RMOUID = 1;
	RMOList.Add(RMO);
}



