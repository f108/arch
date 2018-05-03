// AdmClientPipe.cpp: implementation of the CAdmClientPipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdmCom.h"
#include "AdmClientPipe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "AdmCom.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdmClientPipe::CAdmClientPipe()
{

}

CAdmClientPipe::~CAdmClientPipe()
{

}

void CAdmClientPipe::ProcessMessage(TSNPData &TND)
{
unsigned __int8 Command;
//TSNPData *TND2 = new TSNPData;

	TND >> Command;

	switch (Command)
	{
		case RMCMD_GETUIDUSERLISTANS:
			theApp.CRLD->SetRmoList(&TND);
			return;

		case RMCMD_GETUSERPROFILEANS:
			theApp.CRLD->SetRmoProfile(&TND);
			return;

		case RMCMD_GETUIDSERGRPLISTANS:
			theApp.CSGD->SetSGList(&TND);
			return;

		case RMCMD_GETSERGRPPROFILEANS:
			theApp.CSGD->SetSGProfile(&TND);
			return;

		case RMCMD_GETSLLISTANS:
			theApp.CSLD->SetSLProfile(&TND);
			return;

		default:
			break;
	};
	TND.ResetPos();
	CClientNamedPipe::ProcessMessage(TND);
}
