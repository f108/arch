// TBinaryData.cpp: implementation of the TBinaryData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "tzstring.h"
#include "TBinaryData.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TBinaryData::TBinaryData()
{
	CurPosForReading = this->data;
}

TBinaryData::TBinaryData(const TBinaryData&A)
{
	__TBD_TBlockedMemory::SetSize(A.size);
	memcpy(data, A.data, size);
	CurPosForReading = this->data;
}

TBinaryData::TBinaryData(void *ptr, unsigned int sz)
{
	__TBD_TBlockedMemory::SetSize(sz);
	memcpy(data, ptr, sz);
	CurPosForReading = this->data;
}

TBinaryData::~TBinaryData()
{
}

//-----------------------------------------------------------------------------
unsigned int TBinaryData::GetSizeForStore(void) const
{	
	return size+sizeof(size);
}

unsigned int TBinaryData::GetSize(void) const
{	
	return size;
}

void TBinaryData::Reset(void)
{	
	__TBD_TBlockedMemory::Reset();
	CurPosForReading = NULL; 
}

void *TBinaryData::GetAdjustedPtr(unsigned __int32 Offset)
{
	return __TBD_TBlockedMemory::data+Offset;
}

bool TBinaryData::SetSize(unsigned int _sz)
{
	__TBD_TBlockedMemory::SetSize(_sz);
	CurPosForReading = __TBD_TBlockedMemory::data;
	return true;
}

void TBinaryData::__writefrom(void * ptr, unsigned int sz)
{
	CurPosForReading = CurPosForReading - (int)__TBD_TBlockedMemory::data; 
	AppendBytes(ptr, sz);
	CurPosForReading = CurPosForReading + (int)__TBD_TBlockedMemory::data;
}

void TBinaryData::__readto(void * ptr, unsigned int sz)
{
	if (CurPosForReading-__TBD_TBlockedMemory::data+sz > size)
		throw NoDataForRead();
	memcpy(ptr, CurPosForReading, sz);
	CurPosForReading += sz;
}

void TBinaryData::WriteDataFrom(void *ptr, unsigned __int32 sz)
{
	__writefrom(ptr, sz);
}

void TBinaryData::ReadDataTo(void *ptr, unsigned __int32 sz)
{
	__readto(ptr, sz);
}

bool TBinaryData::LoadDataFrom(void *ptr, unsigned __int32 sz)
{
	SetSize(sz);
	memcpy(__TBD_TBlockedMemory::data, ptr, sz);
	return true;
}

bool TBinaryData::SaveDataTo(void *ptr, unsigned __int32 sz)
{
	memcpy(ptr, __TBD_TBlockedMemory::data, sz);
	return true;
}

//====================================================================================
TBinaryData &TBinaryData::operator << (const bool &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const char &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const unsigned char &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const int &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const unsigned int &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const long &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const unsigned long &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

/*TBinaryData &TBinaryData::operator << (const __int8 &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const unsigned __int8 &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const __int16 &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const unsigned __int16 &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const __int32 &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const unsigned __int32 &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const __int64 &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }

TBinaryData &TBinaryData::operator << (const unsigned __int64 &Value)
{	__writefrom((void *)&Value, sizeof(Value));	return (*this); }
*/
TBinaryData &TBinaryData::operator << (const TBinaryData &Value)
{
	if (this==&Value) return (*this);
	this->__writefrom((void *)&Value.size, sizeof(Value.size));
	__writefrom(Value.data, Value.size);
	return (*this);
}

TBinaryData &TBinaryData::operator >> (bool &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (char &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (unsigned char &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (int &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (unsigned int &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (long &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (unsigned long &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

/*TBinaryData &TBinaryData::operator >> (__int8 &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (unsigned __int8 &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (__int16 &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (unsigned __int16 &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (__int32 &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (unsigned __int32 &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (__int64 &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }

TBinaryData &TBinaryData::operator >> (unsigned __int64 &Value)
{	__readto((void *)&Value, sizeof(Value)); return (*this); }
*/
TBinaryData &TBinaryData::operator >> (TBinaryData &Value)
{
unsigned __int32 size;
	__readto((void *)&size, sizeof(size));
	Value.__TBD_TBlockedMemory::SetSize(size);
	__readto(Value.data, size);
	return (*this);
}

//====================================================================================

bool TBinaryData::LoadFrom(HANDLE hFile)
{
DWORD cbread;
unsigned int k;
	ReadFile(hFile, &k, sizeof(k), &cbread, NULL);
	if (cbread!=sizeof(k)) 
		throw TBinaryData::NoDataForRead();
	SetSize(k);
	ReadFile(hFile, __TBD_TBlockedMemory::data, size, &cbread, NULL);
	if (cbread!=size) 
		throw TBinaryData::NoDataForRead();
	return true;
}

bool TBinaryData::SaveTo(HANDLE hFile)
{
DWORD cbread;
	if (!WriteFile(hFile, &size, sizeof(size), &cbread, NULL)) return false;
	if (!WriteFile(hFile, __TBD_TBlockedMemory::data, size, &cbread, NULL)) return false;
	return true;
}

/*void TBinaryData::operator=(const TBinaryData& TBD)
{
	delete[] Data;
	Size = TBD.Size;
	Data = new char[Size];
	curpos = (char *)Data;
	memcpy(Data, TBD.Data, Size);
}

void TBinaryData::operator+=(const TBinaryData& TBD)
{
void *DataOld = Data;
	Data = NULL;
	Data = new char[Size+TBD.Size];
	memcpy(Data, DataOld, Size);
	memcpy((char *)Data+Size, TBD.Data, TBD.Size);
	curpos = (char *)Data;
	delete[] DataOld;
	Size = Size+TBD.Size;
}

bool TBinaryData::LoadFrom(void *ptr, unsigned int maxlen, unsigned int *cbread)
{
unsigned int sz = *(unsigned int *)ptr;
	if (sz>maxlen-sizeof(unsigned int)) return false;
	Size = sz;
	Data = new char[Size];
	curpos = (char *)Data;
	memcpy(Data, (void*)((char*)ptr+4), Size);
	if (cbread!=NULL)
		*cbread = Size+sizeof(unsigned int);
	return true;
}

bool TBinaryData::SaveTo(void *ptr, unsigned int maxlen, unsigned int *cbread)
{
	if (Size+4>maxlen) return false;
	*(unsigned int *)ptr = Size;
	memcpy(ptr, Data, Size);
	if (cbread!=NULL)
	*cbread = Size+sizeof(unsigned int);
	return true;
}

bool TBinaryData::LoadDataFrom(void *ptr, unsigned int k)
{
	delete[] Data;
	Size = 0;
	if (ptr==NULL) return false;
	Size = k;
	Data = new char[Size];
	curpos = (char *)Data;
	memcpy(Data, ptr, Size);
	return true;
}

bool TBinaryData::SaveDataTo(void *ptr, unsigned int k)
{
	memcpy(ptr, curpos, k);
	curpos += k;
	return true;
}

bool TBinaryData::AppendDataFrom(void *ptr, unsigned int k)
{
	__writefrom(ptr, k);
	return true;
}

bool TBinaryData::LoadFrom(HANDLE hFile)
{
DWORD cbread;
unsigned int k;
	ReadFile(hFile, &k, sizeof(k), &cbread, NULL);
	if (cbread!=sizeof(k)) 
		throw TBinaryData::NoDataForRead();
	if (!SetSize(k)) 
		throw TBinaryData::SetSizeFailed();
	ReadFile(hFile, Data, Size, &cbread, NULL);
	if (cbread!=Size) 
		throw TBinaryData::NoDataForRead();
	return true;
}

bool TBinaryData::SaveTo(HANDLE hFile)
{
DWORD cbread;
	if (!WriteFile(hFile, &Size, sizeof(Size), &cbread, NULL)) return false;
	if (!WriteFile(hFile, Data, Size, &cbread, NULL)) return false;
	return true;
}

unsigned int TBinaryData::GetSizeForStore(void)
{
	return Size+sizeof(unsigned int);
}

unsigned int TBinaryData::GetSize(void)
{
	return Size;
}

bool TBinaryData::SetSize(unsigned int _sz)
{
	delete[] Data;
	Size = 0;
	Data = new char[_sz];
	if (Data==NULL) return false;
	curpos = (char *)Data;
	Size = _sz;
	return true;
}

void TBinaryData::Reset(void)
{
	SetSize(0);
}

void *TBinaryData::GetData(void)
{
	return Data;
}

void *TBinaryData::GetCurrentPtr(void)
{
	return curpos;
}

void TBinaryData::SetCurrentPtr(void *ptr)
{
	curpos = (char *)ptr;
}

bool operator==(const TBinaryData& TBD1, const TBinaryData& TBD2)
{
	if (TBD1.Size!=TBD2.Size) return false;
	for (unsigned int i=0; i<TBD1.Size; i++)
		if (((char *)TBD1.Data)[i]!= ((char *)TBD2.Data)[i]) return false;
	return true;
}

void TBinaryData::__writefrom(void * ptr, unsigned int sz)
{
char *DataNew = new char[Size+sz];
	if (DataNew==NULL) return;
	memcpy((void*)DataNew, Data, Size);
	memcpy((void*)(DataNew+Size), ptr, sz);
	delete[] Data;
	Data = DataNew;
	curpos = (char *)Data;
	Size = Size+sz;
}

void TBinaryData::__readto(void * ptr, unsigned int sz)
{
	if (curpos+sz>(char *)Data+Size) return;
	memcpy(ptr, curpos, sz);
	curpos = curpos + sz;
}

void *TBinaryData::AddNBytes(unsigned int sz)
{
char *DataOld = (char *)Data;
char *Ret;

	Data = new char[Size+sz];
	if (Data==NULL) return NULL;
	memcpy((void*)Data, DataOld, Size);
	delete[] DataOld;
	curpos = (char *)Data;
	Ret = (char *)Data + Size;
	Size = Size+sz;
	return Ret;
}


*/