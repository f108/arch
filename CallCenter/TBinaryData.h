// TBinaryData.h: interface for the TBinaryData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TBINARYDATA_H__A51F7235_DC50_11D4_AE9C_00E04CB9345C__INCLUDED_)
#define AFX_TBINARYDATA_H__A51F7235_DC50_11D4_AE9C_00E04CB9345C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <unsigned __int32 BlockSize>
class __TBD_TMemory
{
protected:
	 __TBD_TMemory() { data = 0; size = 0; RealSize = 0; };
	 virtual ~__TBD_TMemory() { delete[] data; };

	inline void Reset(void)
	{	delete[] data; data = 0; size = 0; RealSize = 0; };

	inline void SetSize(unsigned __int32 k)
	{	delete[] data;
		data = new char[k];
		size = k; RealSize = k;	};

	inline void AppendBytes(void *mem, unsigned __int32 sz)
	{	if (RealSize<size+sz) // надо добавить новый блок
		{
			RealSize = ((size+sz)/BlockSize+((size+sz)%BlockSize==0?0:1))*BlockSize;
			char *OldData = data; data = 0;
			data = new char[RealSize];
			memcpy(data, OldData, size);
			delete[] OldData;
		};
		memcpy(&data[size], mem, sz);
		size += sz; };

	char *data;
	unsigned __int32 size;
	unsigned __int32 RealSize;
};

typedef __TBD_TMemory<512> __TBD_TBlockedMemory;

class TBinaryData : private __TBD_TBlockedMemory
{
public:
	class NoDataForRead { };

	TBinaryData();
	TBinaryData(const TBinaryData&);
	TBinaryData(void *, unsigned int);
	virtual ~TBinaryData();

	unsigned int GetSizeForStore(void) const;
	unsigned int GetSize(void) const;
	void Reset(void);

	void *GetAdjustedPtr(unsigned __int32 Offset);
	bool SetSize(unsigned int _sz);

	bool LoadFrom(HANDLE hFile);
	bool SaveTo(HANDLE hFile);

/*	void *GetData(void);

	void *GetCurrentPtr(void);
	void SetCurrentPtr(void *ptr);

	void *AddNBytes(unsigned int k);

	bool LoadFrom(void *ptr, unsigned int maxlen, unsigned int *cbread);
	bool SaveTo(void *ptr, unsigned int maxlen, unsigned int *cbwrite);

	bool AppendDataFrom(void *, unsigned int);

	bool LoadFrom(HANDLE hFile);
	bool SaveTo(HANDLE hFile);

	void operator=(const TBinaryData& TBD);
	void operator+=(const TBinaryData& TBD);

	friend bool operator==(const TBinaryData& TBD1, const TBinaryData& TBD2);
*/
	void WriteDataFrom(void *ptr, unsigned __int32 sz);
	void ReadDataTo(void *ptr, unsigned __int32 sz);

	bool LoadDataFrom(void *, unsigned __int32 sz);
	bool SaveDataTo(void *, unsigned __int32 sz);

	TBinaryData &operator << (const bool &Value);
	TBinaryData &operator << (const char &Value);
	TBinaryData &operator << (const unsigned char &Value);
	TBinaryData &operator << (const int &Value);
	TBinaryData &operator << (const unsigned int &Value);
	TBinaryData &operator << (const long &Value);
	TBinaryData &operator << (const unsigned long &Value);
/*	TBinaryData &operator << (const __int8 &Value);
	TBinaryData &operator << (const unsigned __int8 &Value);
	TBinaryData &operator << (const __int16 &Value);
	TBinaryData &operator << (const unsigned __int16 &Value);
	TBinaryData &operator << (const __int32 &Value);
	TBinaryData &operator << (const unsigned __int32 &Value);
	TBinaryData &operator << (const __int64 &Value);
	TBinaryData &operator << (const unsigned __int64 &Value);*/
	TBinaryData &operator << (const TBinaryData &Value);

	TBinaryData &operator >> (bool &Value);
	TBinaryData &operator >> (char &Value);
	TBinaryData &operator >> (unsigned char &Value);
	TBinaryData &operator >> (int &Value);
	TBinaryData &operator >> (unsigned int &Value);
	TBinaryData &operator >> (long &Value);
	TBinaryData &operator >> (unsigned long &Value);
/*	TBinaryData &operator >> (__int8 &Value);
	TBinaryData &operator >> (unsigned __int8 &Value);
	TBinaryData &operator >> (__int16 &Value);
	TBinaryData &operator >> (unsigned __int16 &Value);
	TBinaryData &operator >> (__int32 &Value);
	TBinaryData &operator >> (unsigned __int32 &Value);
	TBinaryData &operator >> (__int64 &Value);
	TBinaryData &operator >> (unsigned __int64 &Value);*/
	TBinaryData &operator >> (TBinaryData &Value);

private:
	inline void __writefrom(void * ptr, unsigned int sz);
	inline void __readto(void * ptr, unsigned int sz);

	char *CurPosForReading;
};

#endif // !defined(AFX_TBINARYDATA_H__A51F7235_DC50_11D4_AE9C_00E04CB9345C__INCLUDED_)
