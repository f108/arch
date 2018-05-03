// TUIList.cpp: implementation of the TUIList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TUIList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TUIList::TUIList()
{
	List = NULL;
	size = 0;
	RealSize = 0;
}

TUIList::~TUIList()
{
	delete[] List;
}

bool TUIList::SetSize(unsigned __int32 k)
{
	delete[] List;
	List = new unsigned __int32[k];
	if (List==NULL) return false;
	memset(List, 0, k*sizeof(unsigned __int32));
	size = k;
	RealSize = k;
	return true;
}

unsigned __int32 TUIList::GetSize(void) const
{
	return size;
}

void TUIList::operator=(const TUIList &Value)
{
	if (size!=Value.size)
	{
		delete[] List;
		size = Value.size;
		RealSize = Value.RealSize;
		List = new unsigned __int32[size];
	};
	memcpy(List, Value.List, size*sizeof(unsigned __int32));
}

void TUIList::Reset(void)
{
	delete[] List;
	List = NULL;
	size = 0;
	RealSize = 0;
}

bool TUIList::ValueInList(unsigned __int32 k) const
{
	for (unsigned __int32 i=0; i<size; i++)
		if (List[i] == k) return true;
	return false;
}

int TUIList::GetIndexFor(unsigned __int32 Value)
{
	for (int i=0; i<size; i++)
		if (List[i] == Value) return i;
	return -1;
}

bool TUIList::Add(unsigned __int32 vl)
{
	if (RealSize<size+1) // 
	{
unsigned __int32 *OldList = List;
		List = NULL;
		RealSize = ((size+1)/__TUIList_BLSZ+((size+1)%__TUIList_BLSZ==0?0:1))*__TUIList_BLSZ;
		List = new unsigned __int32[RealSize];
		memcpy(List, OldList, size*sizeof(unsigned __int32));
		delete[] OldList;
	}
	List[size] = vl;
	size++;
	return true;
}

bool TUIList::Delete(unsigned __int32 index)
{
	if (index >= size) return false;
	if ((RealSize-__TUIList_BLSZ)>=size-1) // 
	{
unsigned __int32 *OldList = List;
		List = NULL;
		RealSize = ((size-1)/__TUIList_BLSZ+((size-1)%__TUIList_BLSZ==0?0:1))*__TUIList_BLSZ;
		List = new unsigned __int32[RealSize];
		memcpy(&List[0], &OldList[0], index*sizeof(unsigned __int32));
		memcpy(&List[index], &OldList[index+1], (size-index-1)*sizeof(unsigned __int32));
		delete[] OldList;
		size--;
		return true;
	}
	memcpy(&List[index], &List[index+1], (size-index-1)*sizeof(unsigned __int32));
	size--;
	return true;
}

unsigned __int32 &TUIList::operator[](unsigned __int32 k)
{
	if (k<size) return List[k];
	throw CEBadIndex();
}

TBinaryData &operator << (TBinaryData &s, TUIList &Value)
{
	s.WriteDataFrom((void *)&Value.size, sizeof(Value.size));
	s.WriteDataFrom((void *)Value.List, Value.size*sizeof(unsigned __int32));
	return s;
}

TBinaryData &operator >> (TBinaryData &s, TUIList &Value)
{
	Value.Reset();
unsigned __int32 size;
	s.ReadDataTo((void *)&size, sizeof(unsigned int));
	Value.SetSize(size);
	s.ReadDataTo((void *)Value.List, Value.size*sizeof(unsigned __int32));
	return s;
}

void TUIList::pr(void)
{
//	cout << (unsigned)size << ":" << (unsigned)RealSize << "  ";
//	for (int i=0; i<RealSize; i++)
//		cout << (unsigned)List[i] << " ";
//	cout << endl;
}

unsigned __int32 &TUIAutoSizeList::operator[](unsigned __int32 k)
{
	if (k<size) return List[k];
unsigned __int32 *OldList = List;
	List = NULL;
	RealSize = ((k+1)/__TUIList_BLSZ+((k+1)%__TUIList_BLSZ==0?0:1))*__TUIList_BLSZ;
	List = new unsigned __int32[RealSize];
	memcpy(&List[0], &OldList[0], size*sizeof(unsigned __int32));
	delete[] OldList;
	memset(&List[size], 0, (k-size)*sizeof(unsigned __int32));
	size=k+1;
	return List[k];
}
//###########################################################################################

TUI64List::TUI64List()
{
	List = NULL;
	size = 0;
	RealSize = 0;
//	cout << "TUI64List=" << this << "-" << (void*)(((char*)this)+sizeof(*this))<< endl;
}

TUI64List::~TUI64List()
{
	delete[] List;
}

bool TUI64List::SetSize(unsigned __int32 k)
{
	delete[] List;
	List = new unsigned __int64[k];
	if (List==NULL) return false;
	memset(List, 0, k*sizeof(unsigned __int64));
	size = k;
	RealSize = k;
	return true;
}

unsigned __int32 TUI64List::GetSize(void) const
{
	return size;
}

void TUI64List::operator=(const TUI64List &Value)
{
	if (size!=Value.size)
	{
		delete[] List;
		size = Value.size;
		RealSize = Value.RealSize;
		List = new unsigned __int64[size];
	};
	memcpy(List, Value.List, size*sizeof(unsigned __int64));
}

void TUI64List::Reset(void)
{
	delete[] List;
	List = NULL;
	size = 0;
	RealSize = 0;
}

bool TUI64List::ValueInList(unsigned __int64 k) const
{
	for (unsigned __int32 i=0; i<size; i++)
		if (List[i] == k) return true;
	return false;
}

bool TUI64List::Add(unsigned __int64 vl)
{
	if (RealSize<size+1) // 
	{
unsigned __int64 *OldList = List;
		List = NULL;
		RealSize = ((size+1)/__TUIList_BLSZ+((size+1)%__TUIList_BLSZ==0?0:1))*__TUIList_BLSZ;
		List = new unsigned __int64[RealSize];
		memcpy(List, OldList, size*sizeof(unsigned __int64));
		delete[] OldList;
	}
	List[size] = vl;
	size++;
	return true;
}

bool TUI64List::Delete(unsigned __int32 index)
{
	if (index >= size) return false;
	if ((RealSize-__TUIList_BLSZ)>=size-1) // 
	{
unsigned __int64 *OldList = List;
		List = NULL;
		RealSize = ((size-1)/__TUIList_BLSZ+((size-1)%__TUIList_BLSZ==0?0:1))*__TUIList_BLSZ;
		List = new unsigned __int64[RealSize];
		memcpy(&List[0], &OldList[0], index*sizeof(unsigned __int64));
		memcpy(&List[index], &OldList[index+1], (size-index-1)*sizeof(unsigned __int64));
		delete[] OldList;
		size--;
		return true;
	}
	memcpy(&List[index], &List[index+1], (size-index-1)*sizeof(unsigned __int64));
	size--;
	return true;
}

unsigned __int64 &TUI64List::operator[](unsigned __int32 k)
{
	if (k<size) return List[k];
	throw CEBadIndex();
}

TBinaryData &operator << (TBinaryData &s, TUI64List &Value)
{
	s.WriteDataFrom((void *)&Value.size, sizeof(Value.size));
	s.WriteDataFrom((void *)Value.List, Value.size*sizeof(unsigned __int64));
	return s;
}

TBinaryData &operator >> (TBinaryData &s, TUI64List &Value)
{
	Value.Reset();
unsigned __int32 size;
	s.ReadDataTo((void *)&size, sizeof(unsigned int));
	Value.SetSize(size);
	s.ReadDataTo((void *)Value.List, Value.size*sizeof(unsigned __int64));
	return s;
}


/*#ifdef AFX_TFIXEDSIZEBINARYDATA_H__1ED34545_EF66_431A_B0A9_5D80044AA27F__INCLUDED_
template <DWORD SEGSIZE>
TFixedSizeBinaryData &operator << (TFixedSizeBinaryData &s, TUIList &Value)
{
	s.WriteDataFrom((void *)&Value.size, sizeof(Value.size));
	s.WriteDataFrom((void *)Value.List, Value.size*sizeof(unsigned __int64));
	return s;
}

template <DWORD SEGSIZE>
TFixedSizeBinaryData &operator >> (TFixedSizeBinaryData &s, TUIList &Value)
{
	Value.Reset();
unsigned __int32 size;
	s.ReadDataTo((void *)&size, sizeof(unsigned int));
	Value.SetSize(size);
	s.ReadDataTo((void *)Value.List, Value.size*sizeof(unsigned __int64));
	return s;
}
#endif*/

void TUI64List::pr(void)
{
//	cout << (unsigned)size << ":" << (unsigned)RealSize << "  ";
//	for (int i=0; i<RealSize; i++)
//		cout << (unsigned)List[i] << " ";
//	cout << endl;
}

unsigned __int64 &TUI64AutoSizeList::operator[](unsigned __int32 k)
{
	if (k<size) return List[k];
unsigned __int64 *OldList = List;
	List = NULL;
	RealSize = ((k+1)/__TUIList_BLSZ+((k+1)%__TUIList_BLSZ==0?0:1))*__TUIList_BLSZ;
	List = new unsigned __int64[RealSize];
	memcpy(&List[0], &OldList[0], size*sizeof(unsigned __int64));
	delete[] OldList;
	memset(&List[size], 0, (k-size)*sizeof(unsigned __int64));
	size=k+1;
	return List[k];
}

//###########################################################################################
void TCSUI32DualList::Add(unsigned __int32 data1, unsigned __int32 data2)
{
	TUI64List::Add((((unsigned __int64)data1)<<32)|data2);
}

void TCSUI32DualList::Delete(int index)
{
	TUI64List::Delete(index);
}

int TCSUI32DualList::GetCount(void)
{
	return TUI64List::GetSize();
}

unsigned __int32 TCSUI32DualList::GetData1(int index)
{
	return (unsigned __int32)(((*this)[index]) >> 32);
}

unsigned __int32 TCSUI32DualList::GetData2(int index)
{
	return (unsigned __int32)(((*this)[index]) & 0xFFFFFFFF);
}

int TCSUI32DualList::GetIndexForD1(unsigned __int32 val)
{
	for (int i=0; i<GetCount(); i++)
		if (GetData1(i)==val) return i;
	return -1;
}

int TCSUI32DualList::GetIndexForD2(unsigned __int32 val)
{
	for (int i=0; i<GetCount(); i++)
		if (GetData2(i)==val) return i;
	return -1;
}

void TCSUI32DualList::SetData2(int index, unsigned __int32 val)
{
unsigned __int64 data;

	data = (*this)[index];
	data = (data & 0xFFFFFFFF00000000) | val;
	(*this)[index] = data;
}

//###########################################################################################

TCSEVUI32Queue::TCSEVUI32Queue()
{
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	InitializeCriticalSection(&CS);
//	cout << "TCSEVUI32Queue=" << this << "-" << (void*)(((char*)this)+sizeof(*this))<< endl;
};

TCSEVUI32Queue::~TCSEVUI32Queue()
{
	CloseHandle(hEvent);
	DeleteCriticalSection(&CS);
};

HANDLE TCSEVUI32Queue::GetEventHandle(void)
{
	return hEvent;
}

DWORD TCSEVUI32Queue::WaitForNewItem(DWORD timeout)
{
	return WaitForSingleObject(hEvent, timeout);
}

bool TCSEVUI32Queue::IsEmpty(void)
{
bool ret;
	EnterCriticalSection(&CS);
	ret = TUIList::GetSize()==0;
	LeaveCriticalSection(&CS);
	return ret;
}

void TCSEVUI32Queue::Push(unsigned __int32 k)
{
	EnterCriticalSection(&CS);
	TUIList::Add(k);
	LeaveCriticalSection(&CS);
}

unsigned __int32 TCSEVUI32Queue::Pop(void)
{
	if (IsEmpty()) throw EQueueEmpty();
unsigned __int32 ret;
	EnterCriticalSection(&CS);
	ret = TUIList::operator [](0);
	TUIList::Delete(0);
	LeaveCriticalSection(&CS);
	return ret;
}

unsigned __int32 TCSEVUI32Queue::Peek(void)
{
	if (IsEmpty()) throw EQueueEmpty();
unsigned __int32 ret;
	EnterCriticalSection(&CS);
	ret = TUIList::operator [](0);
	LeaveCriticalSection(&CS);
	return ret;
}

void TCSEVUI32Queue::Reset(void)
{
	EnterCriticalSection(&CS);
	TUIList::Reset();
	LeaveCriticalSection(&CS);
}


//###########################################################################################

TCSEVUI64Queue::TCSEVUI64Queue()
{
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	InitializeCriticalSection(&CS);
//	cout << "TCSEVUI64Queue=" << this << "-" << (void*)(((char*)this)+sizeof(*this))<< endl;
};

TCSEVUI64Queue::~TCSEVUI64Queue()
{
	CloseHandle(hEvent);
	DeleteCriticalSection(&CS);
};

HANDLE TCSEVUI64Queue::GetEventHandle(void)
{
	return hEvent;
}

DWORD TCSEVUI64Queue::WaitForNewItem(DWORD timeout)
{
	return WaitForSingleObject(hEvent, timeout);
}

bool TCSEVUI64Queue::IsEmpty(void)
{
bool ret;
	EnterCriticalSection(&CS);
	ret = TUI64List::GetSize()==0;
	LeaveCriticalSection(&CS);
	return ret;
}

void TCSEVUI64Queue::Push(unsigned __int64 k)
{
	EnterCriticalSection(&CS);
	TUI64List::Add(k);
	LeaveCriticalSection(&CS);
	SetEvent(hEvent);
}

unsigned __int64 TCSEVUI64Queue::Pop(void)
{
	if (IsEmpty()) return 0;// throw EQueueEmpty();
unsigned __int64 ret;
	EnterCriticalSection(&CS);
	ret = TUI64List::operator [](0);
	TUI64List::Delete(0);
	if (TUI64List::GetSize()==0) ResetEvent(hEvent);
	LeaveCriticalSection(&CS);
	return ret;
}

unsigned __int64 TCSEVUI64Queue::Peek(void)
{
	if (IsEmpty()) throw EQueueEmpty();
unsigned __int64 ret;
	EnterCriticalSection(&CS);
	ret = TUI64List::operator [](0);
	LeaveCriticalSection(&CS);
	return ret;
}

void TCSEVUI64Queue::Reset(void)
{
	EnterCriticalSection(&CS);
	TUI64List::Reset();
	LeaveCriticalSection(&CS);
	ResetEvent(hEvent);
}
