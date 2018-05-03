// ServerNamedPipe.h: interface for the CServerNamedPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERNAMEDPIPE_H__31F0B6F4_EEFD_4385_97B0_9607F9987C73__INCLUDED_)
#define AFX_SERVERNAMEDPIPE_H__31F0B6F4_EEFD_4385_97B0_9607F9987C73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*class CConnection
{
public:
	unsigned __int32 RUID;
	OVERLAPPED oOverlap; 
	HANDLE hPipeInst; 
	CHAR chBuf[BUFSIZE]; 
	DWORD cbToWrite; 
	DWORD dwState; 
	BOOL fPendingIO; 
};

#define RMOLineCount 12
#define BUFSIZE 4096
enum TPrevOperation	{POCONNECT, POREAD, POWRITE, POINIT};

class CServerNamedPipe  
{
public:
	CServerNamedPipe();
	virtual ~CServerNamedPipe();

private:
	void Execute(void);

	CConnection Pipe[RMOLineCount];
	HANDLE hEvents[RMOLineCount];
};
*/
#endif // !defined(AFX_SERVERNAMEDPIPE_H__31F0B6F4_EEFD_4385_97B0_9607F9987C73__INCLUDED_)
