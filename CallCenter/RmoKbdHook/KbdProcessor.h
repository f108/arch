// KbdProcessor.h: interface for the CKbdProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KBDPROCESSOR_H__E3500C74_0676_4DFD_8A10_5C0A8BCD8A6B__INCLUDED_)
#define AFX_KBDPROCESSOR_H__E3500C74_0676_4DFD_8A10_5C0A8BCD8A6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\RMO\IPCDEFINES.h"

class CKbdProcessor  
{
public:
	CKbdProcessor();
	virtual ~CKbdProcessor();

	bool DoKey(int Code, WPARAM wParam, LPARAM lParam, bool *SupressKey);

private:
	HANDLE hMailslot;
	HANDLE hFlagsMemory;
	ST_CKP *CKP;

	bool Init(void);
};

#endif // !defined(AFX_KBDPROCESSOR_H__E3500C74_0676_4DFD_8A10_5C0A8BCD8A6B__INCLUDED_)
