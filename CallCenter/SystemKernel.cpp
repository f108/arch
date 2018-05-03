// SystemKernel.cpp: implementation of the CSystemKernel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemKernel.h"
#include "SystemObject.h"

#include "SYSKERNELDEFINES.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#####################################################################################

CSystemKernel::CSystemKernel(bool CreateSuspend) : CThread(CreateSuspend), 
								 CSLWS(true),
								 CCS(true)
{
	CSystemObject::SystemKernel = this;
	PostSysMessage(SCMD_LOADPROFILE);
	cout << "CSK = " << this << endl;
}

CSystemKernel::~CSystemKernel()
{

}

void CSystemKernel::PostSysMessage(SYSCOMMAND &Command)
{
	SysMessageQueue.Push(Command);
}

void CSystemKernel::PostSysMessage(unsigned __int8 Command, unsigned __int8 SubCommand, unsigned __int16 data1, unsigned __int32 data2)
{
	SysMessageQueue.Push(SYSCOMMAND(Command, SubCommand, data1, data2));
}

void CSystemKernel::PostSysMessageWI(DWORD Interval, unsigned __int8 Command, unsigned __int8 SubCommand, unsigned __int16 data1, unsigned __int32 data2)
{
	CTMQ.Push(Interval, SYSCOMMAND(Command, SubCommand, data1, data2));
}

void CSystemKernel::PostSysMessageWI(DWORD Interval, SYSCOMMAND &Command)
{
	CTMQ.Push(Interval, Command);
}

//#########################################################################################################

void CSystemKernel::LoadProfile(void)
{
HANDLE hFile = CreateFile("TLGCC.cfg", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile==INVALID_HANDLE_VALUE)
	{
		RMOList.CreateDefaultStartUpProfile();
		PostSysMessage(SCMD_SAVEPROFILE);
		return;
	};
TBinaryData TBD;

	TBD.LoadFrom(hFile);

	RMOList.LoadFrom(&TBD);
	FLOG << time << "Load RMOList" << endl;
	SGList.LoadFrom(&TBD);
	FLOG << time << "Load SGList" << endl;
	CSLWS.LoadFrom(&TBD);
	FLOG << time << "Load SLList" << endl;
	CloseHandle(hFile);
}

void CSystemKernel::SaveProfile(void)
{
HANDLE hFile = CreateFile("TLGCC.cfg", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
TBinaryData TBD;

	RMOList.SaveTo(&TBD);
	SGList.SaveTo(&TBD);
	CSLWS.SaveTo(&TBD);

	TBD.SaveTo(hFile);

	CloseHandle(hFile);
}

//#########################################################################################################

bool CSystemKernel::FindRMOForCall(unsigned SLNum, unsigned SGNum)
{
int k;
	FLOG << time << "FRFC :" << FreeRmoQueue.GetCount() << " ";
	for (k=0; k<FreeRmoQueue.GetCount(); k++)
		FLOG << (unsigned)FreeRmoQueue.GetData1(k) << "," << (unsigned)FreeRmoQueue.GetData2(k) << " ";
	FLOG << endl;

	k = SGList.GetRMOIndexForCallServ(FreeRmoQueue, SGNum);
	FLOG << time << "FRMOFC " << SLNum << " " << SGNum << " " << k << endl;
	if (k==-1) return false;
	SendAnswerRequest(FreeRmoQueue.GetData1(k), SLNum, SGNum);
	FreeRmoQueue.Delete(k);
	return true;
}

bool CSystemKernel::FindCallForRMO(unsigned index)
{
TUIList UIL;
int k;
	CCS.GetSGListForRMO(index, &UIL);
	for (k=0; k<RingQueue.GetCount(); k++)
	{
		if (UIL.ValueInList(RingQueue.GetData2(k))) // нашли вызов - обслуживаем
		{
			SendAnswerRequest(index, RingQueue.GetData1(k), RingQueue.GetData2(k));
			RingQueue.Delete(k);
			SendQueueState();
			return true;
		};
	};
	SendQueueState();
	return false;
}

bool CSystemKernel::SendAnswerRequest(unsigned index, unsigned SLNum, unsigned SGNum)
{
	CCS.SetCALLAttr(index, SLNum, SGNum);
	CCS.SetRMOState(index, RMO_CONNECTIONINPROGRESS);
	CSLWS.SetRMState(CCS.GetRMOSLNum(index), CCS_RMTONE);
	CSLWS.SetRMState(CCS.GetRMOSLNum(index), CCS_RMDEFAULT);
TSNPData *TND;
	TND = new TSNPData;
	(*TND) << RMCMD_SHOWRINGBANNER;
	CCS.SendMessage(index, TND);
	return true;
}

bool CSystemKernel::EstablishConnection(unsigned index)
{
unsigned SGID, SLNum;
TSNPData *TND;
	CCS.GetCALLAttr(index, &SLNum, &SGID);
	CCS.SetRMOState(index, RMO_INUSE);
	TND = new TSNPData;
	(*TND) << RMCMD_SHOWCALLBANNER;
	SGList.SaveInfoForBanner(SGID, TND);
	CCS.SendMessage(index, TND);
	CSLWS.SetSLState(SLNum, CCS.GetRMOSLNum(index));
	return true;
}

bool CSystemKernel::BreakConnection(unsigned index)
{
	CCS.SetRMOState(index, RMO_WAITCALL);
	CSLWS.SetRMState(CCS.GetRMOSLNum(index), CCS_RMDEFAULT);
	CCS.SetCALLAttr(index, -1, 0);
TSNPData *TND;
	TND = new TSNPData;
	(*TND) << RMCMD_SETINSERVSTATE;
	CCS.SendMessage(index, TND);
	return true;
}

bool CSystemKernel::CancelAnswerRequest(unsigned SLNum)
{
unsigned SGID, SLNum2;
int index;
	for (index=0; index<INSTANCESCOUNT; index++)
	{
		CCS.GetCALLAttr(index, &SLNum2, &SGID);
		if (SLNum2==SLNum) break;
	};
	if (index>=INSTANCESCOUNT) return false;

	CCS.SetRMOState(index, RMO_WAITCALL);
	CSLWS.SetRMState(CCS.GetRMOSLNum(index), CCS_RMDEFAULT);
TSNPData *TND;
	TND = new TSNPData;
	(*TND) << RMCMD_SETINSERVSTATE;
	CCS.SendMessage(index, TND);
	if (FreeRmoQueue.GetIndexForD1(index)==-1)
		FreeRmoQueue.Add(index, CCS.GetPipeInstRUID(index));
	return true;
}

bool CSystemKernel::CancelAnswerRequestAndSetBusyState(unsigned SLNum)
{
unsigned SGID, SLNum2;
int index;
	for (index=0; index<INSTANCESCOUNT; index++)
	{
		CCS.GetCALLAttr(index, &SLNum2, &SGID);
		if (SLNum2==SLNum) break;
	};
	if (index>=INSTANCESCOUNT) return false;

	CSLWS.SetRMState(CCS.GetRMOSLNum(index), CCS_RMDEFAULT);
	CCS.SetCALLAttr(index, -1, 0);
	SetBusyState(index);
	return true;
}

int CSystemKernel::GetIndexForAnswerRequest(unsigned SLNum)
{
unsigned SGID, SLNum2;
int index;
	for (index=0; index<INSTANCESCOUNT; index++)
	{
		CCS.GetCALLAttr(index, &SLNum2, &SGID);
		if (SLNum2==SLNum) return index;
	};
	return -1;
}

bool CSystemKernel::SetBusyState(unsigned index)
{
TSNPData *TND;
	CCS.SetRMOState(index, RMO_BUSY);
	CCS.ClearRMOState(index, RMO_REQBUSYSTATE);
	TND = new TSNPData;
	(*TND) << RMCMD_SETBUSYSTATE;
	CCS.SendMessage(index, TND);
	return true;
}

void CSystemKernel::CheckOprInSG(void)
{
TCSUI32DualList TUIDL;
int index;
unsigned D2;
TUIList UIL;

	for (int i=0; i<CCS.GetCount(); i++)
	{
		if ((CCS.GetClientType(i)&RMOA_CATEGORYMASK)!=RMOA_OPERATOR) continue;
		CCS.GetSGList(i, &UIL);

		for (int j=0; j<UIL.GetSize(); j++)
		{
			index = TUIDL.GetIndexForD1(UIL[j]);
			if (index==-1)
			{
				TUIDL.Add(UIL[j], 0);
				index = TUIDL.GetIndexForD1(UIL[j]);
			};
			if ((CCS.GetRMOState(i)&RMO_STATEMASK)!=RMO_BUSY && 
				(CCS.GetRMOState(i)&RMO_STATEMASK)!=RMO_ALARM) 
			{
				D2 = TUIDL.GetData2(index);
				D2++;
				TUIDL.SetData2(index, D2);
			};
		};
	};

	for (int i=0; i<TUIDL.GetCount(); i++)
	{
		CSLWS.CheckSLCount(TUIDL.GetData1(i), SGList.GetActiveRMCountInSG(TUIDL.GetData1(i),TUIDL.GetData2(i)));
		FLOG << time << (unsigned)TUIDL.GetData1(i) << " " << (unsigned)TUIDL.GetData2(i) << endl;
	};
}

void CSystemKernel::SendQueueState()
{
TSNPData *TND;
unsigned __int32 k;

	k = RingQueue.GetCount();

	for (int i=0; i<CCS.GetCount(); i++)
	{
		if ((CCS.GetClientType(i)&RMOA_CATEGORYMASK)!=RMOA_OPERATOR) continue;
		TND = new TSNPData;
		(*TND) << RMCMD_SETQUEUESTATE << k;
		CCS.SendMessage(i, TND);
	};
}

//#########################################################################################################

void CSystemKernel::Execute(void)
{
	Sleep(500);
	CSLWS.Resume();
	Sleep(200);
	CCS.Resume();
	Sleep(500);

DWORD res;
SYSCOMMAND CMD;
TUIList TUIL;
TSNPData *TND;
unsigned __int32 ui32;
unsigned RMOIndex;
int k;
DWORD CHKCOUNT=GetTickCount(), TC1;

	for (;!Terminated;)
	{
		res = WaitForSingleObject(SysMessageQueue.GetEventHandle(), 500);
//		if (res==WAIT_TIMEOUT) continue;

		TC1=GetTickCount();
		if ((max(TC1,CHKCOUNT)-min(TC1,CHKCOUNT))>=3000)
		{
			CHKCOUNT=TC1;
			PostSysMessage(SCMD_REQESTCOMMSTATE);
		};

		try
		{
			for (;;)
			{
				Sleep(100);
//				try
//				{
					CMD = CTMQ.Pop();
//				}
//				catch (CSystemMessageQueueWithTimer::ENoMessage)
//				{
					if (CMD==0)
					CMD = SysMessageQueue.Pop();
//				};

				switch (CMD.GetCommand())
				{
					case SCMD_ADDRINGINQUEUE:
						CancelAnswerRequestAndSetBusyState(CMD.GetData1());
						if (!FindRMOForCall(CMD.GetData1(), CMD.GetData2()))
						{
							k = RingQueue.GetIndexForD1(CMD.GetData1());
							if (k!=-1) 
							{
								RingQueue.Delete(k);
								FLOG << time << "REMOVE ring from queue" << endl;
							};
							RingQueue.Add(CMD.GetData1(), CMD.GetData2());
							FLOG << time << "ADD ring in queue [" << (unsigned)CMD.GetData1() << "," << (unsigned)CMD.GetData2() << "]" << endl;
						};
						SendQueueState();
						break;
					case SCMD_DELETERINGINQUEUE:
						if (!CancelAnswerRequest(CMD.GetData1()))
						{
							k = RingQueue.GetIndexForD1(CMD.GetData1());
							if (k!=-1)
							{
								RingQueue.Delete(k);
								FLOG << time << "REMOVE ring from queue" << endl;
							};
						};
						SendQueueState();
						break;
					case SCMD_RMOALARM:
						try { RMOIndex = CCS.GetRMOIndexBySLNum(CMD.GetData1()); }
						catch (CConnectionServer::ERMNotAttached) { break; };
						k = FreeRmoQueue.GetIndexForD1(RMOIndex);
						if (k!=-1) FreeRmoQueue.Delete(k);
//						if ((CCS.GetRMOState(RMOIndex)&RMO_STATEMASK)!=RMO_ALARM &&
//							(CCS.GetRMOState(RMOIndex)&RMO_STATEMASK)!=RMO_BUSY)
//							SGList.DecAOCounter(CCS.GetRMS(RMOIndex));
						CCS.SetRMOState(RMOIndex, RMO_ALARM);
						CSLWS.SetRMState(CCS.GetRMOSLNum(RMOIndex), CCS_RMDEFAULT);
						FLOG << time << "RMO Alarm #" << RMOIndex << endl; 
						TND = new TSNPData;
						(*TND) << RMCMD_SETALARMSTATE;
						CCS.SendMessage(RMOIndex, TND);
						CheckOprInSG();
						break;
					case SCMD_SETRMOINSERV:
						try { RMOIndex = CCS.GetRMOIndexBySLNum(CMD.GetData1()); }
						catch (CConnectionServer::ERMNotAttached) { break; };
						CCS.SetRMOState(RMOIndex, RMO_BUSY);
						TND = new TSNPData;
						(*TND) << RMCMD_SETBUSYSTATE;
						CCS.SendMessage(RMOIndex, TND);
						break;

					case SCMD_SETACTIVERMOINSG:
						FLOG << time << "== SCMD_SETACTIVERMOINSG" << endl;
						break;
					case SCMD_DECACTOPTINSG:
//						SGList.DecAOCounter(CMD.GetData1());
						CheckOprInSG();
						break;

					case SCMD_REGISTEROPERATOR:
						CCS.GetSGList(CMD.GetData1(), &TUIL);
						SGList.RegisterOperator(CMD.GetData1(), TUIL);
						break;
					case SCMD_UNREGISTEROPERATOR:
						SGList.UnregisterOperator(CMD.GetData1());
						CheckOprInSG();
						break;
					case SCMD_CHECKSLCOUNT:
						CheckOprInSG();
//						CSLWS.CheckSLCount(CMD.GetData2(), SGList.GetActiveRMCountInSG(CMD.GetData2()), 		CMD.GetData1());
						break;

			//------------------------------------------------------------------------------
					case SCMD_USERPRESSSCROLL:
						if ((CCS.GetRMOState(CMD.GetData1())&RMO_STATEMASK)!=RMO_BUSY)
						{
							if ((CCS.GetRMOState(CMD.GetData1())&RMO_STATEMASK)!=RMO_CONNECTIONINPROGRESS &&
								(CCS.GetRMOState(CMD.GetData1())&RMO_STATEMASK)!=RMO_INUSE)
							{
								SetBusyState(CMD.GetData1());
								k = FreeRmoQueue.GetIndexForD1(CMD.GetData1());
								if (k!=-1) FreeRmoQueue.Delete(k);
//								SGList.DecAOCounter(CCS.GetRMS(CMD.GetData1()));
								PostSysMessageWI(2000, SCMD_SETACTIVERMOINSG);
							}
							else
							{
								CCS.SetRMOState(CMD.GetData1(), RMO_REQBUSYSTATE);
							};
						}
						else
						{
							if (CCS.GetRMOState(CMD.GetData1())!=RMO_ALARM)
							{
//								SGList.IncAOCounter(CCS.GetRMS(CMD.GetData1()));
								CCS.SetRMOState(CMD.GetData1(), RMO_WAITCALL);
								TND = new TSNPData;
								(*TND) << RMCMD_SETINSERVSTATE;
								CCS.SendMessage(CMD.GetData1(), TND);
								if (!FindCallForRMO(CMD.GetData1()) && FreeRmoQueue.GetIndexForD1(CMD.GetData1())==-1)
									FreeRmoQueue.Add(CMD.GetData1(), CCS.GetPipeInstRUID(CMD.GetData1()));
							};
						};
						CheckOprInSG();
						CSLWS.RequestRMsState();
						break;
					case SCMD_USERPRESSPAUSE:
						FLOG << time << "Answer pressed RM#" << CMD.GetData1() << endl;
						if ((CCS.GetRMOState(CMD.GetData1())&RMO_STATEMASK)==RMO_CONNECTIONINPROGRESS)
						{
							EstablishConnection(CMD.GetData1());
						}
						else if ((CCS.GetRMOState(CMD.GetData1())&RMO_STATEMASK)==RMO_INUSE)
						{
							BreakConnection(CMD.GetData1());
							if ((CCS.GetRMOState(CMD.GetData1())&RMO_REQBUSYSTATE)!=0)
							{
								CCS.ClearRMOState(CMD.GetData1(), RMO_REQBUSYSTATE);
								SetBusyState(CMD.GetData1());
//								SGList.DecAOCounter(CCS.GetRMS(RMOIndex));
								k = FreeRmoQueue.GetIndexForD1(CMD.GetData1());
								if (k!=-1) FreeRmoQueue.Delete(k);
								CheckOprInSG();
							}
							else
							{
								if (!FindCallForRMO(CMD.GetData1()) && FreeRmoQueue.GetIndexForD1(CMD.GetData1())==-1)
									FreeRmoQueue.Add(CMD.GetData1(), CCS.GetPipeInstRUID(CMD.GetData1()));
							};
						};
						break;
			//------------------------------------------------------------------------------
					case SCMD_REQESTCOMMSTATE:
				//		CSLWS.RequestRMsState();
						CheckOprInSG();
						CSLWS.RequestSLsState();
					//	PostSysMessageWI(3000, SCMD_REQESTCOMMSTATE);
					//	SendQueueState();
						break;
					case SCMD_SAVEPROFILE:
						SaveProfile();
						break;
					case SCMD_LOADPROFILE:
						LoadProfile();
						break;
					case SCMD_RELOADRMOPROFILE:
						CCS.ReloadRMOProfile(RMOList.GetRMODataByUID(CMD.GetData2()));
						break;
			//------------------------------------------------------------------------------
					case SCMD_LOADPIPEINSTRMOPROFILE:
						CCS.LoadRMOProfile(CMD.GetData1(), 
							RMOList.GetRMODataByNameAndType(CCS.GetPipeInstName(CMD.GetData1()),
							CCS.GetClientType(CMD.GetData1())));
						if (CCS.GetClientType(CMD.GetData1())==RMOA_OPERATOR)
						{
							CCS.SetRMOState(CMD.GetData1(), RMO_BUSY);
							TND = new TSNPData;
							(*TND) << RMCMD_SETBUSYSTATE;
							CCS.SendMessage(CMD.GetData1(), TND);
							TND = new TSNPData;
							(*TND) << RMCMD_SETRMOSLNUM << CCS.GetRMOSLNum(CMD.GetData1())+1;
							CCS.SendMessage(CMD.GetData1(), TND);
							CSLWS.RequestRMsState();
						};
						break;
					case SCMD_USERSPROFILEACCESS:
						switch (CMD.GetSubCommand())
						{
							case RMCMD_GETUIDUSERLIST:
								FLOG << time << "USER GET LIST " << endl;
								if (!(RMOList.GetUserAttr(CCS.GetPipeInstRUID(CMD.GetData1()))&RMOA_CANCHNGUSERPF)) break;
								TND = new TSNPData;
								(*TND) << RMCMD_GETUIDUSERLISTANS;
								RMOList.SaveRMUIDListTo(TND);
								CCS.SendMessage(CMD.GetData1(), TND);
								break;
							case RMCMD_GETUSERPROFILE:
								FLOG << time << "USER GET USER PROFILE " << endl;
								if (!(RMOList.GetUserAttr(CCS.GetPipeInstRUID(CMD.GetData1()))&RMOA_CANCHNGUSERPF)) break;
								TND = (TSNPData*)CMD.GetData2();
								(*TND) >> ui32;
								TND->Reset();
								(*TND) << RMCMD_GETUSERPROFILEANS;
								if (!RMOList.SaveTo(ui32, TND)) break;
								CCS.SendMessage(CMD.GetData1(), TND);
								break;
							case RMCMD_SETUSERPROFILE:
								FLOG << time << "USER SET USER PROFILE " << endl;
								if (!(RMOList.GetUserAttr(CCS.GetPipeInstRUID(CMD.GetData1()))&RMOA_CANCHNGUSERPF)) break;
								TND = (TSNPData*)CMD.GetData2();
								(*TND) >> ui32;
								if (!RMOList.LoadFrom(ui32, TND)) break;
								TND->Reset();
								(*TND) << RMCMD_GETUSERPROFILEANS;
								if (!RMOList.SaveTo(ui32, TND)) break;
								CCS.SendMessage(CMD.GetData1(), TND);
								break;
						};
						break;
					case SCMD_SERVGPROFILEACCESS:
						switch (CMD.GetSubCommand())
						{
							case RMCMD_GETUIDSERGRPLIST:
								FLOG << time << "USER GET SG LIST " << endl;
								if (!(RMOList.GetUserAttr(CCS.GetPipeInstRUID(CMD.GetData1()))&RMOA_CANCHNGSERGPF)) break;
								TND = new TSNPData;
								(*TND) << RMCMD_GETUIDSERGRPLISTANS;
								SGList.SaveSGUIDListTo(TND);
								CCS.SendMessage(CMD.GetData1(), TND);
								break;
							case RMCMD_GETSERGRPPROFILE:
								FLOG << time << "USER GET SERGRP PROFILE " << endl;
								if (!(RMOList.GetUserAttr(CCS.GetPipeInstRUID(CMD.GetData1()))&RMOA_CANCHNGSERGPF)) break;
								TND = (TSNPData*)CMD.GetData2();
								(*TND) >> ui32;
								TND->Reset();
								(*TND) << RMCMD_GETSERGRPPROFILEANS;
								if (!SGList.SaveTo(ui32, TND)) break;
								CCS.SendMessage(CMD.GetData1(), TND);
								break;
							case RMCMD_SETSERGRPPROFILE:
								FLOG << time << "USER SET SERGRP PROFILE " << endl;
								if (!(RMOList.GetUserAttr(CCS.GetPipeInstRUID(CMD.GetData1()))&RMOA_CANCHNGSERGPF)) break;
								TND = (TSNPData*)CMD.GetData2();
								(*TND) >> ui32;
								if (!SGList.LoadFrom(ui32, TND)) break;
								TND->Reset();
								(*TND) << RMCMD_GETSERGRPPROFILEANS;
								if (!SGList.SaveTo(ui32, TND)) break;
								CCS.SendMessage(CMD.GetData1(), TND);
								break;
						};
						break;
					case SCMD_SLPPROFILEACCESS:
						switch (CMD.GetSubCommand())
						{
							case RMCMD_GETSLLIST:
								FLOG << time << "USER GET SL LIST " << endl;
								if (!(RMOList.GetUserAttr(CCS.GetPipeInstRUID(CMD.GetData1()))&RMOA_CANCHNGSLPRF)) break;
								TND = new TSNPData;
								(*TND) << RMCMD_GETSLLISTANS;
								CSLWS.SaveTo(TND);
								CCS.SendMessage(CMD.GetData1(), TND);
								break;
							case RMCMD_SETSLPROFILE:
								FLOG << time << "USER SET SL PROFILE " << endl;
								if (!(RMOList.GetUserAttr(CCS.GetPipeInstRUID(CMD.GetData1()))&RMOA_CANCHNGSLPRF)) break;
								TND = (TSNPData*)CMD.GetData2();
								CSLWS.LoadFrom(TND);
								delete TND;
								break;
						};
						break;
				};
			};
		}
		catch (TCSEVUI64Queue::EQueueEmpty)
		{
		}
		catch (...)
		{
			FLOG << time << "Exception in SystemKernal" << endl;
		};
	};
}

