// RMOClientPipe.h: interface for the CRMOClientPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RMOCLIENTPIPE_H__4EA14135_CEB5_4A76_8643_69066ABC1C2A__INCLUDED_)
#define AFX_RMOCLIENTPIPE_H__4EA14135_CEB5_4A76_8643_69066ABC1C2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\TESTCLIENTPIPE\ClientNamedPipe.h"

class CRMOApp;

class CRMOClientPipe : public CClientNamedPipe  
{
public:
	CRMOClientPipe(CRMOApp* _Parent);
	virtual ~CRMOClientPipe();

	void ProcessMessage(TSNPData &TND);
	unsigned __int32 GetClientType(void);
	void ProcessException(unsigned);

private:
	CRMOApp *Parent;

};

#endif // !defined(AFX_RMOCLIENTPIPE_H__4EA14135_CEB5_4A76_8643_69066ABC1C2A__INCLUDED_)
