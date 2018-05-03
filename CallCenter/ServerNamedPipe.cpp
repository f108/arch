// ServerNamedPipe.cpp: implementation of the CServerNamedPipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServerNamedPipe.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*CServerNamedPipe::CServerNamedPipe()
{

}

CServerNamedPipe::~CServerNamedPipe()
{

}

void CServerNamedPipe::Execute(void)
{
SECURITY_ATTRIBUTES saPipeSecurity;
PSECURITY_DESCRIPTOR pPipeSD = NULL;
	memset((VOID *)&saPipeSecurity, 0, sizeof(SECURITY_ATTRIBUTES));
	if (!(pPipeSD=(PSECURITY_DESCRIPTOR) (malloc(SECURITY_DESCRIPTOR_MIN_LENGTH))));;
	if (!InitializeSecurityDescriptor(pPipeSD, SECURITY_DESCRIPTOR_REVISION)) ;;
	if (!SetSecurityDescriptorDacl(pPipeSD, TRUE, (PACL)NULL, FALSE)) ;;
	saPipeSecurity.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPipeSecurity.bInheritHandle = TRUE;
	saPipeSecurity.lpSecurityDescriptor = pPipeSD;

	for (int i=0; i<RMOLineCount; i++)
	{
		hEvents[i] = CreateEvent(NULL, TRUE, TRUE, NULL);
		Pipe[i].oOverlap.hEvent = hEvents[i]; 
 		Pipe[i].hPipeInst = CreateNamedPipe(PipeName, PIPE_ACCESS_DUPLEX |
				FILE_FLAG_OVERLAPPED, PIPE_TYPE_MESSAGE |
				PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
				BUFSIZE, BUFSIZE, 500, &saPipeSecurity);
		Pipe[i].WasCanceled = false;
		Pipe[i].fPendingIO = ConnectToNewClient(i); 
		Pipe[i].dwState = Pipe[i].fPendingIO ? CONNECTING_STATE : READ_STATE;
	};
}

BOOL CServerNamedPipe::ConnectToNewClient(DWORD index) 
{ 
	ConnectNamedPipe(Pipe[index].hPipeInst, Pipe[index].oOverlap);
	LastError = GetLastError();
 
	if (fConnected) 
	{
		sysout << time << " Error on ConnectNamedPipe " << LastError << endl;
	};
 
   switch (LastError) 
   { 
   // The overlapped connection in progress. 
      case ERROR_IO_PENDING: 
         fPendingIO = TRUE; 
         break; 
 
   // Client is already connected, so signal an event. 
      case ERROR_PIPE_CONNECTED: 
         if (SetEvent(lpo->hEvent)) 
            break; 
 
   // If an error occurs during the connect operation... 
		default: 
		{
			sysout << time << " Error on ConnectNamedPipe (in switch)" << LastError << endl;
		};
   } 
 
   return fPendingIO; 
} 

*/