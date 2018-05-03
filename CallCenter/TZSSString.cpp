// TTZSuperShortString.cpp: implementation of the TTZSuperShortString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TZSSString.h"

#include <string>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TZSuperShortString::TZSuperShortString()
{
  len = 0;
  str = new char[1];
  str[0] = 0;
};

TZSuperShortString::TZSuperShortString(const char *cstr)
{
  len = strlen(cstr);
  len = len>255?255:len;
  str = new char[len+1];
  strncpy(str, cstr, len);
  str[len] = 0;
};

TZSuperShortString::TZSuperShortString(const char *cstr, int size)
{
  if (size>255) size=255;
  for (len=0; len<size; len++) if (cstr[len]==0) break;
  len = len>size?size:len;
  str = new char[len+1];
  strncpy(str, cstr, len);
  str[len] = 0;
}

TZSuperShortString::TZSuperShortString(const TZSuperShortString &A)
{
  len = strlen(A.str);
  str = new char[len+1];
  strcpy(str, A.str);
  str[len] = 0;
};

TZSuperShortString::TZSuperShortString(const char &ch, unsigned __int8 k)
{
  len = k>255?255:k;
  str = new char[len+1];
  strnset(str, ch, len);
  str[len] = 0;
};

TZSuperShortString::~TZSuperShortString()
{
  delete[] str;
};

//----------------------------------------------------------------------
unsigned __int8 TZSuperShortString::set_length(unsigned __int8 k)
{
  delete[] str;
  len = k>255?255:k;
  str = new char[len+1];
  strnset(str, 0x20, len);
  str[len] = 0;
  return len;
};

unsigned __int8 TZSuperShortString::length(void) const
{
  return len;
};

/*const char *TZSuperShortString::c_str(void) const
{
  return str;
};*/

unsigned __int8 TZSuperShortString::findchar(char ch)
{
  for (unsigned __int8 i=0; i<len; i++)
    if (str[i]==ch) return i;
  return 0;
};

//----------------------------------------------------------------------
char &TZSuperShortString::operator[](unsigned __int8 k)
{
  if (k<0||k>=len) return str[0];
  return str[k];
};

TZSuperShortString TZSuperShortString::operator()(unsigned __int8 from,unsigned __int8 to) const
{
TZSuperShortString Ret;

  if (to<=from) return Ret;
  Ret.set_length(to-from);
  for (int j=0, i=from; i<to; i++,j++)
    Ret.str[j] = this->str[i];
  Ret.str[Ret.length()] = 0;
  return Ret;
};

//----------------------------------------------------------------------
void TZSuperShortString::operator=(const TZSuperShortString &A)
{
  if (this==&A) return;
  delete[] str;
  len = A.len;
  str = new char[len+1];
  memcpy(str, A.str, len);
  str[len] = 0;
};

void TZSuperShortString::operator+=(const TZSuperShortString &A)
{
char *strnew = new char[len+A.len+1];
unsigned int i;

  for (i=0; i<len; i++) strnew[i] = str[i];
  for (i=0; i<A.len; i++) strnew[len+i] = A.str[i];
  len = len+A.len;
  delete[] str;
  str = strnew;
  str[len]=0;
};

void TZSuperShortString::Convert866to1251(void)
{
	for (int i=0; i<strlen(str); i++)
	{
		if ((unsigned char)str[i]>=0x80 && (unsigned char)str[i]<=0x9F) { str[i]+=0x40; continue; };
		if ((unsigned char)str[i]>=0xA0 && (unsigned char)str[i]<=0xAF) { str[i]+=0x40; continue; };
		if ((unsigned char)str[i]>=0xE0 && (unsigned char)str[i]<=0xEF) { str[i]+=0x10; continue; };
	};
}

void TZSuperShortString::str1251toUpper(void)
{
	for (int i=0;i<strlen(str); i++) 
		if ((unsigned char)str[i]>=0xE0 && (unsigned char)str[i]<=0xFF) str[i]-=0x20;
}

void TZSuperShortString::CutSpace(void)
{
	for (int i=strlen(str)-1; i>=0; i--)
	{
		if (str[i]!=' ') break;
		str[i]=0;
		len--;
	};
}

void TZSuperShortString::CutLeftSpace(void)
{
int i;
	for (i=0; i<strlen(str); i++)
		if (str[i]!=' ') break;
	strcpy(str, str+i);
	len -= i;

};

unsigned __int32 TZSuperShortString::ToL(void)
{
	return atol(str);
}

//----------------------------------------------------------------------
TZSuperShortString operator+(const TZSuperShortString &A, const TZSuperShortString &B)
{
TZSuperShortString ret = A;
  ret += B;
  return ret;
};

int operator==(const TZSuperShortString &A, const TZSuperShortString &B)
{
  if (A.len!=B.len) return 0;
  for (unsigned int i=0; i<A.len; i++)
    if (A.str[i]!=B.str[i]) return 0;
  return 1;
};

int operator!=(const TZSuperShortString &A, const TZSuperShortString &B)
{
  return !(A==B);
};


TBinaryData &operator << (TBinaryData &s, TZSuperShortString &Value)
{
unsigned __int8 size;

	size = Value.length();
	s.WriteDataFrom((void *)&size, sizeof(size));
	s.WriteDataFrom((void *)Value.c_str(), size);
	return s;
}

TBinaryData &operator >> (TBinaryData &s, TZSuperShortString &Value)
{
unsigned __int8 size;
	s.ReadDataTo((void *)&size, sizeof(size));
	Value.set_length(size);
	s.ReadDataTo((void *)Value.c_str(), size);
	return s;
}

void TZSuperShortString::__debug(ostream &s)
{
	s << len << ":" << &str <<":" << str << endl;
}


