// TFixedSizeBinaryData.h: interface for the TFixedSizeBinaryData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TFIXEDSIZEBINARYDATA_H__1ED34545_EF66_431A_B0A9_5D80044AA27F__INCLUDED_)
#define AFX_TFIXEDSIZEBINARYDATA_H__1ED34545_EF66_431A_B0A9_5D80044AA27F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined(WITHTFIXEDSIZEBINARYDATA)
#define WITHTFIXEDSIZEBINARYDATA
#endif

template <DWORD SEGSIZE>
class TFixedSizeBinaryData  
{
	class EFSBDException { };
	class ENoDataForRead : public EFSBDException { };
	class EBadIndex : public EFSBDException { };
	class EObjectTooLong : public EFSBDException { };

private:
	unsigned char data[SEGSIZE];
	DWORD curpos;
	DWORD size;

	inline void __writefrom(void * ptr, unsigned int sz) { if (curpos+sz>SEGSIZE) throw EObjectTooLong(); memcpy(&data[curpos], ptr, sz); curpos+=sz; size+=sz;};
	inline void __readto(void * ptr, unsigned int sz) { if (curpos+sz>size) throw ENoDataForRead(); memcpy(ptr, &data[curpos], sz); curpos+=sz;};

public:
	TFixedSizeBinaryData(){curpos=0;size=0;};
	TFixedSizeBinaryData(char init) {curpos=0;memset(&data[0], _init, sizeof(data)); size=0;};
	virtual ~TFixedSizeBinaryData() { };

	inline operator void*(){return &data[0];};
	inline char &operator[](unsigned int index) { if (index>=size) throw BadIndex(); return &data[index]; };
	inline void Reset(void) { curpos=0; size=0;};
	inline void ResetPos(void) { curpos=0; };
	inline int GetSize(void) { return size; };
	inline LPDWORD GetSizeLP(void) { return &size; };
	inline void AdjustSize(DWORD sz) { size=sz; };

	inline void CopyUnreadDataFrom(TFixedSizeBinaryData *TND) { size=TND->size-TND->curpos; memcpy(data, &(TND->data[TND->curpos]), size); };

#define TFSBD_OPERATORLSH( T )	inline TFixedSizeBinaryData &operator<<(##T &Value){__writefrom((void*)&Value,sizeof(Value));return(*this);}
#define TFSBD_OPERATORRSH( T )	inline TFixedSizeBinaryData &operator>>(##T &Value){__readto((void *)&Value,sizeof(Value));return(*this);}

	TFSBD_OPERATORLSH(const bool);
	TFSBD_OPERATORLSH(const char);
	TFSBD_OPERATORLSH(const unsigned char);
	TFSBD_OPERATORLSH(const int);
	TFSBD_OPERATORLSH(const unsigned int);
	TFSBD_OPERATORLSH(const long);
	TFSBD_OPERATORLSH(const unsigned long);
/*	TFSBD_OPERATORLSH(const __int8);
	TFSBD_OPERATORLSH(const unsigned __int8);
	TFSBD_OPERATORLSH(const __int16);
	TFSBD_OPERATORLSH(const unsigned __int16);
	TFSBD_OPERATORLSH(const __int32);
	TFSBD_OPERATORLSH(const unsigned __int32);
	TFSBD_OPERATORLSH(const __int64);
	TFSBD_OPERATORLSH(const unsigned __int64);*/

	TFSBD_OPERATORRSH(bool);
	TFSBD_OPERATORRSH(char);
	TFSBD_OPERATORRSH(unsigned char);
	TFSBD_OPERATORRSH(int);
	TFSBD_OPERATORRSH(unsigned int);
	TFSBD_OPERATORRSH(long);
	TFSBD_OPERATORRSH(unsigned long);
/*	TFSBD_OPERATORRSH(__int8);
	TFSBD_OPERATORRSH(unsigned __int8);
	TFSBD_OPERATORRSH(__int16);
	TFSBD_OPERATORRSH(unsigned __int16);
	TFSBD_OPERATORRSH(__int32);
	TFSBD_OPERATORRSH(unsigned __int32);
	TFSBD_OPERATORRSH(__int64);
	TFSBD_OPERATORRSH(unsigned __int64);*/

	void WriteDataFrom(void *ptr, unsigned __int32 sz) { __writefrom(ptr, sz); };
	void ReadDataTo(void *ptr, unsigned __int32 sz) { __readto(ptr, sz); };

};

#endif // !defined(AFX_TFIXEDSIZEBINARYDATA_H__1ED34545_EF66_431A_B0A9_5D80044AA27F__INCLUDED_)
