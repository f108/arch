// SysOut.h: interface for the CSysOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSOUT_H__37477336_0DED_11D5_AED7_00E04CB9345C__INCLUDED_)
#define AFX_SYSOUT_H__37477336_0DED_11D5_AED7_00E04CB9345C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <fstream>
#include <ios>
using namespace std;

class CSysOut : virtual public ios {

public:
        CSysOut(char *filename, bool OutToCout=false);
        virtual ~CSysOut();

		void SetFileName(char *filename, bool OutToCout=false);

        CSysOut& flush();

inline	CSysOut& operator<<(CSysOut& (__cdecl * _f)(CSysOut&));
inline	CSysOut& operator<<(ios& (__cdecl * _f)(ios&));
		CSysOut& operator<<(const char *);
inline	CSysOut& operator<<(const unsigned char *);
inline	CSysOut& operator<<(const signed char *);
inline	CSysOut& operator<<(char);
        CSysOut& operator<<(unsigned char);
inline	CSysOut& operator<<(signed char);
        CSysOut& operator<<(short);
        CSysOut& operator<<(unsigned short);
        CSysOut& operator<<(int);
        CSysOut& operator<<(unsigned int);
        CSysOut& operator<<(long);
        CSysOut& operator<<(unsigned long);
        CSysOut& operator<<(const void *);

protected:
private:
	bool _OutToCout;
	fstream fout;
};

inline CSysOut& CSysOut::operator<<(CSysOut& (__cdecl * _f)(CSysOut&)) { (*_f)(*this); return *this; }
inline CSysOut& CSysOut::operator<<(ios& (__cdecl * _f)(ios& )) { (*_f)(cout); (*_f)(fout); return *this; }

inline  CSysOut& CSysOut::operator<<(char _c) { return operator<<((unsigned char) _c); }
inline  CSysOut& CSysOut::operator<<(signed char _c) { return operator<<((unsigned char) _c); }

inline  CSysOut& CSysOut::operator<<(const unsigned char * _s) { return operator<<((const char *) _s); }
inline  CSysOut& CSysOut::operator<<(const signed char * _s) { return operator<<((const char *) _s); }

inline CSysOut& __cdecl flush(CSysOut& _outs) { return _outs.flush(); }
inline CSysOut& __cdecl endl(CSysOut& _outs) { return _outs << '\n' << flush; }
inline CSysOut& __cdecl ends(CSysOut& _outs) { return _outs << char('\0'); }

CSysOut& __cdecl time(CSysOut& _outs);

	ios&           __cdecl dec(ios&);
	ios&           __cdecl hex(ios&);
	ios&           __cdecl oct(ios&);

/////////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_SYSOUT_H__37477336_0DED_11D5_AED7_00E04CB9345C__INCLUDED_)
