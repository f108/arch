// SystemObject.h: interface for the CSystemObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMOBJECT_H__BE5F7C9F_EC5E_4681_9969_30DD84B936E7__INCLUDED_)
#define AFX_SYSTEMOBJECT_H__BE5F7C9F_EC5E_4681_9969_30DD84B936E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SYSKERNELDEFINES.h"

class CSystemObject  
{
	friend class CSystemKernel;
protected:
	static CSystemKernel *SystemKernel;
	void PostSysMessage(unsigned __int8 Command, unsigned __int8 SubCommand=0, unsigned __int16 data1=NULL, unsigned __int32 data2=NULL);
	void PostSysMessageWI(DWORD Interval, unsigned __int8 Command, unsigned __int8 SubCommand=0, unsigned __int16 data1=NULL, unsigned __int32 data2=NULL);

};

#endif // !defined(AFX_SYSTEMOBJECT_H__BE5F7C9F_EC5E_4681_9969_30DD84B936E7__INCLUDED_)
