// KbdProcessor.cpp: implementation of the CKbdProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KbdProcessor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKbdProcessor::CKbdProcessor()
{
	Init();
}

CKbdProcessor::~CKbdProcessor()
{
	CloseHandle(hMailslot);
	CloseHandle(hFlagsMemory);
}

bool CKbdProcessor::Init(void)
{
	hMailslot = CreateFile(KBDHOOKMAILSLOT, GENERIC_WRITE, 
		FILE_SHARE_WRITE|FILE_SHARE_READ, NULL, OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, NULL);

	hFlagsMemory = OpenFileMapping(FILE_MAP_READ, TRUE, KBDMEMORYMAPPINGNAME);
	if (hFlagsMemory!=NULL)
	{
		CKP = (ST_CKP*)MapViewOfFile(hFlagsMemory, FILE_MAP_READ, 0, 0, sizeof(ST_CKP));
	};
	return true;
}

bool CKbdProcessor::DoKey(int Code, WPARAM wParam, LPARAM lParam, bool *SupressKey)
{
unsigned __int32 buf[4];
DWORD cbw;
	buf[0] = 0x5A5A5A5A;
	buf[1] = Code;
	buf[2] = wParam;
	buf[3] = lParam;
	WriteFile(hMailslot, buf, sizeof(buf), &cbw, NULL);
	if (CKP!=NULL)
	{
		*SupressKey = bool(CKP->SupressingFlag[wParam%256]);
	} else *SupressKey = false;
	return true;
}
