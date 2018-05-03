// ServiceGroup.cpp: implementation of the CServiceGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceGroup.h"

#include "RMOWorkSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServiceGroup::CServiceGroup()
{
	LastUsingRMOPos = 0;
	ActiveOperatorCounter = 0;
}

CServiceGroup::~CServiceGroup()
{

}

void CServiceGroup::SaveTo(TBinaryData *TBD)
{
	(*TBD) << SGID << SGCaption << 
			SGDescription << Color << BlinkBanner << SGSearchMethod << RMIDOrder <<
			UseQueue << QueueType << UsingQueueByOperatorCount << OperatorCount << 
/**/		(unsigned)0 << (unsigned)0 << (unsigned)0 << (unsigned)0; /* for future using */
}

void CServiceGroup::LoadFrom(TBinaryData *TBD)
{
unsigned kkk;
	(*TBD) >> SGID >> SGCaption >>
			SGDescription >> Color >> BlinkBanner >> SGSearchMethod >> RMIDOrder >>
			UseQueue >> QueueType >> UsingQueueByOperatorCount >> OperatorCount >>
			kkk >> kkk >> kkk >> kkk;
	LastUsingRMOPos = 0;
}

void CServiceGroup::SaveTo(TSNPData *TND)
{
	(*TND) << SGID << SGCaption << 
			SGDescription << Color << BlinkBanner << SGSearchMethod << RMIDOrder <<
			UseQueue << QueueType << UsingQueueByOperatorCount << OperatorCount << 
/**/		(unsigned)0 << (unsigned)0 << (unsigned)0 << (unsigned)0; /* for future using */
}

void CServiceGroup::LoadFrom(TSNPData *TND)
{
	(*TND) 	>> SGID >> SGCaption >>
			SGDescription >> Color >> BlinkBanner >> SGSearchMethod >> RMIDOrder >>
			UseQueue >> QueueType >> UsingQueueByOperatorCount >> OperatorCount;
	LastUsingRMOPos = 0;
}


//==========================================================================================
CServiceGroupList::CServiceGroupList()
{
}

CServiceGroupList::~CServiceGroupList()
{
}

void CServiceGroupList::SaveTo(TBinaryData *TBD)
{
	(*TBD) << SGList.GetCount();
	for (int i=0; i<SGList.GetCount(); i++)
	{
		SGList[i]->SaveTo(TBD);
	};
}

void CServiceGroupList::LoadFrom(TBinaryData *TBD)
{
	SGList.Reset();
unsigned __int32 Size;
CServiceGroup *CSG;
	(*TBD) >> Size;
	for (int i=0; i<Size; i++)
	{
		CSG = new CServiceGroup;
		CSG->LoadFrom(TBD);
		SGList.Add(CSG);
	};
}


void CServiceGroupList::SaveSGUIDListTo(TSNPData *TND)
{
	(*TND) << SGList.GetCount();
	for (unsigned i=0; i<SGList.GetCount(); i++)
		(*TND) << SGList[i]->SGID << SGList[i]->SGCaption;
}

bool CServiceGroupList::SaveTo(unsigned __int32 SGUID, TSNPData *TND)
{
unsigned pos;
	for (pos=0; pos<SGList.GetCount(); pos++)
		if (SGList[pos]->SGID==SGUID)
		{
			SGList[pos]->SaveTo(TND);
			return true;
		};
	return false;
}

bool CServiceGroupList::LoadFrom(unsigned __int32 SGUID, TSNPData *TND)
{
	if (SGUID!=0xFFFFFFFF)
	{
	unsigned pos;
		for (pos=0; pos<SGList.GetCount(); pos++)
			if (SGList[pos]->SGID==SGUID) break;
		SGList[pos]->LoadFrom(TND);
		PostSysMessage(SCMD_SAVEPROFILE);
		PostSysMessage(SCMD_RELOADSGPROFILE, 0, 0, SGUID);
		return true;
	};

unsigned __int32 NUID = 10;
bool NUIDMustBeChange=false;
	for (;;)
	{
		for (unsigned i=0; i<SGList.GetCount(); i++)
			if (SGList[i]->SGID==NUID) 
			{
				NUIDMustBeChange = true;
				break;
			};
		if (NUIDMustBeChange==false) break;
		NUID++;
		NUIDMustBeChange = false;
	};

CServiceGroup *CSG = new CServiceGroup;
	CSG->LoadFrom(TND);
	CSG->SGID = NUID;
	SGList.Add(CSG);
	PostSysMessage(SCMD_SAVEPROFILE);
	PostSysMessage(SCMD_RELOADSGPROFILE, 0, 0, SGUID);
	return true;
}

bool CServiceGroupList::SaveInfoForBanner(unsigned __int32 SGUID, TSNPData *TND)
{
unsigned pos;
	for (pos=0; pos<SGList.GetCount(); pos++)
		if (SGList[pos]->SGID==SGUID)
		{
			(*TND) << SGList[pos]->SGCaption << SGList[pos]->Color << SGList[pos]->BlinkBanner;
			return true;
		};
	return false;
}

void CServiceGroupList::RegisterOperator(unsigned index, TUIList &UIL)
{
	for (unsigned pos=0; pos<SGList.GetCount(); pos++)
	{
		if (UIL.ValueInList(SGList[pos]->SGID) && !SGList[pos]->RMOIndexList.ValueInList(index))
			SGList[pos]->RMOIndexList.Add(index);
	};
}

void CServiceGroupList::UnregisterOperator(unsigned index)
{
int k;
	for (unsigned pos=0; pos<SGList.GetCount(); pos++)
	{
		k = SGList[pos]->RMOIndexList.GetIndexFor(index);
		if (k!=-1) SGList[pos]->RMOIndexList.Delete(k);
	};
}

void CServiceGroupList::IncAOCounter(CRMOStoredData *CRMO)
{
	for (unsigned pos=0; pos<SGList.GetCount(); pos++)
	{
		if (CRMO->ServiceGroupsList.ValueInList(SGList[pos]->SGID))
		{
			SGList[pos]->ActiveOperatorCounter++;
			PostSysMessage(SCMD_CHECKSLCOUNT, 0, -1, SGList[pos]->SGID);
			FLOG << time << "SG:" << (unsigned)SGList[pos]->SGID << " OC:" << SGList[pos]->ActiveOperatorCounter << endl;
		}
	};
}

void CServiceGroupList::DecAOCounter(CRMOStoredData *CRMO)
{
	for (unsigned pos=0; pos<SGList.GetCount(); pos++)
	{
		if (CRMO->ServiceGroupsList.ValueInList(SGList[pos]->SGID))
		{
			SGList[pos]->ActiveOperatorCounter--;
			PostSysMessage(SCMD_CHECKSLCOUNT, 0, -1, SGList[pos]->SGID);
			FLOG << time << "SG:" << (unsigned)SGList[pos]->SGID << " OC:" << SGList[pos]->ActiveOperatorCounter << endl;
		};
	};
}

void CServiceGroupList::DecAOCounter(unsigned SGUID)
{
	for (unsigned pos=0; pos<SGList.GetCount(); pos++)
		if (SGList[pos]->SGID==SGUID)
		{
			SGList[pos]->ActiveOperatorCounter--;
			PostSysMessage(SCMD_CHECKSLCOUNT, 0, -1, SGList[pos]->SGID);
			FLOG << time << "SG:" << (unsigned)SGList[pos]->SGID << " OC:" << SGList[pos]->ActiveOperatorCounter << endl;
			break;
		};
}

unsigned CServiceGroupList::GetActiveRMCountInSG(unsigned SGUID, unsigned ActCount)
{
	if (ActCount==0) return 0;
unsigned ret;
	for (unsigned pos=0; pos<SGList.GetCount(); pos++)
		if (SGList[pos]->SGID==SGUID)
		{
			ret = ActCount;
			if (SGList[pos]->UseQueue)
			{
				if (SGList[pos]->UsingQueueByOperatorCount && 
					(SGList[pos]->OperatorCount<=ActCount) || ret==0)
				{ }
				else
				ret += SGList[pos]->QueueType;
			};
			return ret;
		};
	return 0;
}

int CServiceGroupList::GetRMOIndexForCallServ(TCSUI32DualList &FreeRMOIndexList, unsigned SG)
{
	for (unsigned pos=0; pos<SGList.GetCount(); pos++)
	{
		if (SGList[pos]->SGID!=SG) continue;
		int k, p;
		CServiceGroup *CSG = SGList[pos];

		switch (SGList[pos]->SGSearchMethod&SGSM_SRCHMTHMASK)
		{
			case SGSM_CYCLIC:
				for (k=0; k<FreeRMOIndexList.GetCount(); k++)
				{
					if (!SGList[pos]->RMOIndexList.ValueInList(FreeRMOIndexList.GetData1(k))) continue;
					return k;
				};
				break;
			case SGSM_SUC:
				for (k=0; k<SGList[pos]->RMIDOrder.GetSize(); k++)
				{
					p = FreeRMOIndexList.GetIndexForD2(SGList[pos]->RMIDOrder[k]);
					if (p==-1) continue;
					return p;
				};
				break;
			case SGSM_RANDOM:
				break;
		};
		return -1;
	};
	return -1;
}
