// TUIList.h: interface for the TUIList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TUILIST_H__E6B72BA4_14EF_11D5_8B43_34EF38000000__INCLUDED_)
#define AFX_TUILIST_H__E6B72BA4_14EF_11D5_8B43_34EF38000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TBinaryData.h"

#define __TUIList_BLSZ 30

class TUIList  
{
public:
	class CEBadIndex { };

	TUIList();
	~TUIList();

	bool SetSize(unsigned __int32 k);
	unsigned __int32 GetSize(void) const;

	void Reset(void);

	bool ValueInList(unsigned __int32 k) const;

	void operator=(const TUIList &Value);

	bool Add(unsigned __int32);
	bool Delete(unsigned __int32 index);
	int GetIndexFor(unsigned __int32 Value);
	unsigned __int32 &operator[](unsigned __int32);

	friend TBinaryData &operator << (TBinaryData &s, TUIList &Value);
	friend TBinaryData &operator >> (TBinaryData &s, TUIList &Value);

#ifdef WITHTFIXEDSIZEBINARYDATA
	template <DWORD SEGSIZE> friend TFixedSizeBinaryData<SEGSIZE> &operator << (TFixedSizeBinaryData<SEGSIZE> &s, TUIList &Value);
	template <DWORD SEGSIZE> friend TFixedSizeBinaryData<SEGSIZE> &operator >> (TFixedSizeBinaryData<SEGSIZE> &s, TUIList &Value);
#endif

	void pr(void);

protected:
	unsigned __int32 *List;
	unsigned __int32 size;
	unsigned __int32 RealSize;
};

#ifdef WITHTFIXEDSIZEBINARYDATA
template <DWORD SEGSIZE> 
TFixedSizeBinaryData<SEGSIZE> &operator << (TFixedSizeBinaryData<SEGSIZE> &s, TUIList &Value)
{
	s.WriteDataFrom((void *)&Value.size, sizeof(Value.size));
	s.WriteDataFrom((void *)Value.List, Value.size*sizeof(unsigned __int32));
	return s;
}

template <DWORD SEGSIZE> 
TFixedSizeBinaryData<SEGSIZE> &operator >> (TFixedSizeBinaryData<SEGSIZE> &s, TUIList &Value)
{
	Value.Reset();
unsigned __int32 size;
	s.ReadDataTo((void *)&size, sizeof(unsigned int));
	Value.SetSize(size);
	s.ReadDataTo((void *)Value.List, Value.size*sizeof(unsigned __int32));
	return s;
};
#endif

class TUIAutoSizeList : public TUIList
{
public:
	unsigned __int32 &operator[](unsigned __int32);
};

//###########################################################################################
class TUI64List
{
public:
	class CEBadIndex { };

	TUI64List();
	~TUI64List();

	bool SetSize(unsigned __int32 k);
	unsigned __int32 GetSize(void) const;

	void Reset(void);

	bool ValueInList(unsigned __int64 k) const;

	void operator=(const TUI64List &Value);

	bool Add(unsigned __int64);
	bool Delete(unsigned __int32 index);
	unsigned __int64 &operator[](unsigned __int32);

	friend TBinaryData &operator << (TBinaryData &s, TUI64List &Value);
	friend TBinaryData &operator >> (TBinaryData &s, TUI64List &Value);

	void pr(void);

protected:
	unsigned __int64 *List;
	unsigned __int32 size;
	unsigned __int32 RealSize;
};

class TUI64AutoSizeList : public TUI64List
{
public:
	unsigned __int64 &operator[](unsigned __int32);
};

//###########################################################################################
class TCSUI32DualList : private TUI64List
{
public:
	TCSUI32DualList() { }; //cout << "TCSUI32DualList=" << this << endl;};
	~TCSUI32DualList() { };

	void Add(unsigned __int32 data1, unsigned __int32 data2);
	void Delete(int index);

	int GetCount(void);
	unsigned __int32 GetData1(int index);
	unsigned __int32 GetData2(int index);
	int GetIndexForD1(unsigned __int32 val);
	int GetIndexForD2(unsigned __int32 val);

	void SetData2(int index, unsigned __int32 val);
};


//###########################################################################################

template <class Type>
class TCSPtrQueue : private TUIList
{
	CRITICAL_SECTION CS;
public:

	bool IsEmpty(void) { bool ret; EnterCriticalSection(&CS); ret = (TUIList::GetSize()==0); LeaveCriticalSection(&CS);return ret;};
	void Push(Type *data) { EnterCriticalSection(&CS); TUIList::Add((unsigned __int32)data); LeaveCriticalSection(&CS);};
	Type *Pop(void) { if (IsEmpty()) return NULL; EnterCriticalSection(&CS); Type *ret=(Type*)TUIList::operator[](0); TUIList::Delete(0); LeaveCriticalSection(&CS); return ret; };
	Type *Peek(void) { if (IsEmpty()) return NULL; EnterCriticalSection(&CS); Type *ret=(Type*)TUIList::operator[](0); LeaveCriticalSection(&CS); return ret; };
	void Reset(void) { EnterCriticalSection(&CS); for(unsigned i=0; i<TUIList::GetSize(); i++) delete (Type*)TUIList::operator[](i); TUIList::Reset(); LeaveCriticalSection(&CS);};

	TCSPtrQueue() { InitializeCriticalSection(&CS); };
	~TCSPtrQueue() { Reset(); DeleteCriticalSection(&CS); };
};

//###########################################################################################

template <class Type>
class TPtrList : private TUIList
{
public:

	bool IsEmpty(void) { return TUIList::GetSize()==0; };
	unsigned __int32 GetCount(void) { return TUIList::GetSize(); };

	void Add(Type *data) { TUIList::Add((unsigned __int32)data); };
	void Delete(unsigned __int32 index) {TUIList::Delete(index); };

	void Reset(void) { for (unsigned i=0; i<TUIList::GetSize(); i++) delete (Type*)TUIList::operator [](i); TUIList::Reset(); };

	Type *operator[](unsigned __int32 index) { return (Type *)TUIList::operator [](index); };

	TPtrList() { };
	~TPtrList() { Reset(); };
};

//###########################################################################################

template <class Type>
class TUI32ObjList : private TUIList
{
public:

	bool IsEmpty(void) { return TUIList::GetSize()==0; };
	unsigned __int32 GetCount(void) { return TUIList::GetSize(); };

	void Add(Type data) { TUIList::Add((unsigned __int32)data); };
	void Delete(unsigned __int32 index) {TUIList::Delete(index); };

	Type *GetDataPtr(void) { return (Type *)List;};

	Type &operator[](unsigned __int32 index) { return (Type&)TUIList::operator [](index); };

	TUI32ObjList() { };
	~TUI32ObjList() { };
};

//###########################################################################################

class TCSEVUI32Queue : private TUIList
{
	HANDLE hEvent;
	CRITICAL_SECTION CS;
public:
	class EQueueEmpty { };

	TCSEVUI32Queue();
	~TCSEVUI32Queue();

	HANDLE GetEventHandle(void);
	DWORD WaitForNewItem(DWORD timeout);
	bool IsEmpty(void);
	void Push(unsigned __int32);
	unsigned __int32 Pop(void);
	unsigned __int32 Peek(void);
	void Reset(void);
};

//###########################################################################################

class TCSEVUI64Queue : private TUI64List
{
	HANDLE hEvent;
	CRITICAL_SECTION CS;
public:
	class EQueueEmpty { };

	TCSEVUI64Queue();
	~TCSEVUI64Queue();

	HANDLE GetEventHandle(void);
	DWORD WaitForNewItem(DWORD timeout);
	bool IsEmpty(void);
	void Push(unsigned __int64);
	unsigned __int64 Pop(void);
	unsigned __int64 Peek(void);
	void Reset(void);
};

#endif // !defined(AFX_TUILIST_H__E6B72BA4_14EF_11D5_8B43_34EF38000000__INCLUDED_)
