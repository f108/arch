// SystemObject.cpp: implementation of the CSystemObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemObject.h"
#include "SystemKernel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemKernel *CSystemObject::SystemKernel = NULL;

void CSystemObject::PostSysMessage(unsigned __int8 Command, unsigned __int8 SubCommand, unsigned __int16 data1, unsigned __int32 data2)
{
	SystemKernel->PostSysMessage(Command, SubCommand, data1, data2);
}

void CSystemObject::PostSysMessageWI(DWORD Interval, unsigned __int8 Command, unsigned __int8 SubCommand, unsigned __int16 data1, unsigned __int32 data2)
{
	SystemKernel->PostSysMessageWI(Interval, Command, SubCommand, data1, data2);
}

