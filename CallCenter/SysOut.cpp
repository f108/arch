// SysOut.cpp: implementation of the CSysOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysOut.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysOut::CSysOut(char *filename,bool OutToCout)
{
	_OutToCout = OutToCout;
	fout.open(filename, ios::out | ios::ate);
}

void CSysOut::SetFileName(char *filename, bool OutToCout)
{
	fout.close();
	_OutToCout = OutToCout;
	fout.open(filename, ios::out | ios::ate);
}

CSysOut::~CSysOut()
{
	fout.close();
}

CSysOut& CSysOut::flush()
{
	if (_OutToCout) cout.flush();
	fout.flush();
	return *this;
}

CSysOut& CSysOut::operator<<(short a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& CSysOut::operator<<(unsigned short a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& CSysOut::operator<<(int a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& CSysOut::operator<<(unsigned int a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& CSysOut::operator<<(long a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& CSysOut::operator<<(unsigned long a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& CSysOut::operator<<(const char * a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& CSysOut::operator<<(unsigned char a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& CSysOut::operator<<(const void * a)
{
	if (_OutToCout) cout << a;
	fout << a;
	return *this;
}

CSysOut& __cdecl time(CSysOut& _outs)
{
SYSTEMTIME ST;
char buf[21];

	memset(buf, 0, 21);

	::GetLocalTime(&ST);
	sprintf(buf, "%02d/%02d/%04d.%02d:%02d:%02d ", ST.wDay, ST.wMonth, ST.wYear, ST.wHour, ST.wMinute, ST.wSecond);
	_outs << buf;
	return _outs;
}




