// TZSuperShortString.h: interface for the TZSuperShortString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TZSUPERSHORTSTRING_H__859D4A28_ECCE_11D4_AEAA_00E04CB9345C__INCLUDED_)
#define AFX_TZSUPERSHORTSTRING_H__859D4A28_ECCE_11D4_AEAA_00E04CB9345C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TBinaryData.h"

#include <ostream>
using namespace std;

class TZSuperShortString  
{
public:
	TZSuperShortString();
	TZSuperShortString(const char *);
	TZSuperShortString(const char *, int size);
	TZSuperShortString(const TZSuperShortString &);
	TZSuperShortString(const char &, unsigned __int8);
	~TZSuperShortString();

	unsigned __int8 set_length(unsigned __int8);
	unsigned __int8 length(void) const;
	inline const char *c_str(void) const { return str; };
	unsigned __int8 findchar(char);

	char &operator[](unsigned __int8);
	void operator=(const TZSuperShortString &);
	void operator+=(const TZSuperShortString &);
	TZSuperShortString operator()(unsigned __int8,unsigned __int8) const;

	void Convert866to1251(void);
	void str1251toUpper(void);
	void CutSpace(void);
	void CutLeftSpace(void);

	unsigned __int32 ToL(void);

	void __debug(ostream &s);

	friend TZSuperShortString operator+(const TZSuperShortString &, const TZSuperShortString &);
	friend int operator==(const TZSuperShortString&, const TZSuperShortString&);
	friend int operator!=(const TZSuperShortString&, const TZSuperShortString&);

	friend TBinaryData &operator << (TBinaryData &s, TZSuperShortString &Value);
	friend TBinaryData &operator >> (TBinaryData &s, TZSuperShortString &Value);

#ifdef WITHTFIXEDSIZEBINARYDATA
	template <DWORD SEGSIZE> friend TFixedSizeBinaryData<SEGSIZE> &operator << (TFixedSizeBinaryData<SEGSIZE> &s, TZSuperShortString &Value);
	template <DWORD SEGSIZE> friend TFixedSizeBinaryData<SEGSIZE> &operator >> (TFixedSizeBinaryData<SEGSIZE> &s, TZSuperShortString &Value);
#endif

private:
	unsigned __int8 len;
	char *str;
};

#ifdef WITHTFIXEDSIZEBINARYDATA
template <DWORD SEGSIZE> 
TFixedSizeBinaryData<SEGSIZE> &operator << (TFixedSizeBinaryData<SEGSIZE> &s, TZSuperShortString &Value)
{
unsigned __int8 size;
	size = Value.length();
	s.WriteDataFrom((void *)&size, sizeof(size));
	s.WriteDataFrom((void *)Value.c_str(), size);
	return s;
};

template <DWORD SEGSIZE> 
TFixedSizeBinaryData<SEGSIZE> &operator >> (TFixedSizeBinaryData<SEGSIZE> &s, TZSuperShortString &Value)
{
unsigned __int8 size;
	s.ReadDataTo((void *)&size, sizeof(size));
	Value.set_length(size);
	s.ReadDataTo((void *)Value.c_str(), size);
	return s;
};
#endif

#endif // !defined(AFX_TZSUPERSHORTSTRING_H__859D4A28_ECCE_11D4_AEAA_00E04CB9345C__INCLUDED_)
