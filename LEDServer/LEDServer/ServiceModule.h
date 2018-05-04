// ServiceModule.h: interface for the CServiceModule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICEMODULE_H__D40E0F7F_FCD6_47F1_A6EF_0818E5F490D4__INCLUDED_)
#define AFX_SERVICEMODULE_H__D40E0F7F_FCD6_47F1_A6EF_0818E5F490D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CServiceModule  
{
private:
	SERVICE_STATUS          ssStatus;
	SERVICE_STATUS_HANDLE   sshStatusHandle;

	char ServiceName[200];
	char DisplayName[200];

	void AddDataInRegistry(void);
	static void WINAPI service_main(DWORD dwArgc, LPTSTR *lpszArgv);
	static void WINAPI service_ctrl(DWORD dwCtrlCode);
	BOOL ReportStatusToSCMgr(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);

public:

	bool ServiceInProgress;
	bool Restart;

	CServiceModule();
	virtual ~CServiceModule();

	void SetDispatchTable(void);
	void ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);

	DWORD InstallService(void);
	DWORD RemoveService(void);
};

extern CServiceModule __CServiceModule;

#endif // !defined(AFX_SERVICEMODULE_H__D40E0F7F_FCD6_47F1_A6EF_0818E5F490D4__INCLUDED_)
