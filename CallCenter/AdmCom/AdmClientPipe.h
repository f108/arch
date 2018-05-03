// AdmClientPipe.h: interface for the CAdmClientPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADMCLIENTPIPE_H__7897A8E2_0403_4EC2_A4EA_DFECA930F455__INCLUDED_)
#define AFX_ADMCLIENTPIPE_H__7897A8E2_0403_4EC2_A4EA_DFECA930F455__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\TESTCLIENTPIPE\ClientNamedPipe.h"
#include "..\WSDEFINES.h"

class CAdmClientPipe : public CClientNamedPipe  
{
public:
	CAdmClientPipe();
	virtual ~CAdmClientPipe();

	unsigned __int32 GetClientType(void) { return RMOA_ADMINISTRATOR;};
	void ProcessMessage(TSNPData &TND);

};

#endif // !defined(AFX_ADMCLIENTPIPE_H__7897A8E2_0403_4EC2_A4EA_DFECA930F455__INCLUDED_)
