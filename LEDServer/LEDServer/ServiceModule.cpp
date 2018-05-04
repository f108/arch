// ServiceModule.cpp: implementation of the CServiceModule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceModule.h"
#include "LEDServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServiceModule __CServiceModule;

CServiceModule::CServiceModule()
{
	ServiceInProgress = false;
	Restart = false;
	strcpy(ServiceName, SRVNAME);
	strcpy(DisplayName, SRVDISP);
}

CServiceModule::~CServiceModule()
{

}

void CServiceModule::SetDispatchTable(void)
{
    SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { TEXT(ServiceName), (LPSERVICE_MAIN_FUNCTION)CServiceModule::service_main },
        { NULL, NULL }
    };
    StartServiceCtrlDispatcher(dispatchTable);
}

DWORD CServiceModule::InstallService(void)
{
SC_HANDLE schService;
SC_HANDLE schSCManager;
TCHAR szPath[512];

	GetModuleFileName(NULL, szPath, 512);
	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager)
	{
        schService = CreateService(schSCManager, TEXT(ServiceName), TEXT(DisplayName),
			SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL, szPath, NULL, NULL, NULL, NULL, NULL);
		if (schService)
		{
			CloseServiceHandle(schService);
			AddDataInRegistry();
			return 0;
		}
		else return GetLastError();
		CloseServiceHandle(schSCManager);
	};
	return GetLastError();
}

DWORD CServiceModule::RemoveService(void)
{
SC_HANDLE schService;
SC_HANDLE schSCManager;
	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager)
	{
		schService = OpenService(schSCManager, ServiceName, DELETE);
		if (schService!=NULL)
		{
			DeleteService(schService);
		}
		else return GetLastError();
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
	}
	else return GetLastError();
	return 0;
}

void WINAPI CServiceModule::service_ctrl(DWORD dwCtrlCode)
{
    switch(dwCtrlCode)
    {
        case SERVICE_CONTROL_STOP:
			__CServiceModule.ServiceInProgress = false;
            return;
    }
}

void WINAPI CServiceModule::service_main(DWORD dwArgc, LPTSTR *lpszArgv)
{
    __CServiceModule.sshStatusHandle = RegisterServiceCtrlHandler(__CServiceModule.ServiceName, service_ctrl);
    if (__CServiceModule.sshStatusHandle)
	{
		__CServiceModule.ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		__CServiceModule.ssStatus.dwServiceSpecificExitCode = 0;
		__CServiceModule.ServiceInProgress = true;
		__CServiceModule.ServiceMain( dwArgc, lpszArgv );
	};
    return;
}

void CServiceModule::ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 5000);
	ReportStatusToSCMgr(SERVICE_RUNNING, NO_ERROR, 0);

	Main();

	ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 10000);
	ReportStatusToSCMgr(SERVICE_STOPPED, NO_ERROR, 0);
}

BOOL CServiceModule::ReportStatusToSCMgr(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint)
{
static DWORD dwCheckPoint = 1;
BOOL fResult = TRUE;

        if (dwCurrentState == SERVICE_START_PENDING)
            ssStatus.dwControlsAccepted = 0;
        else
            ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;

        ssStatus.dwCurrentState = dwCurrentState;
        ssStatus.dwWin32ExitCode = dwWin32ExitCode;
        ssStatus.dwWaitHint = dwWaitHint;

        if ( ( dwCurrentState == SERVICE_RUNNING ) ||
             ( dwCurrentState == SERVICE_STOPPED ) )
            ssStatus.dwCheckPoint = 0;
        else
            ssStatus.dwCheckPoint = dwCheckPoint++;

		fResult = SetServiceStatus( sshStatusHandle, &ssStatus);
    return fResult;
}

void CServiceModule::AddDataInRegistry(void)
{
HKEY hk;
DWORD dwData; 
UCHAR buf[256];
LONG k;

	sprintf((char*)buf,"SYSTEM\\CurrentControlSet\\Services\\%s", ServiceName);
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, (char*)buf, 0, KEY_WRITE, &hk);
	RegSetValueEx(hk, "Description", 0, REG_SZ, (unsigned char*)DESCSRV, strlen(DESCSRV)+1);
	RegCloseKey(hk);

TCHAR szPath[512];

    GetModuleFileName(NULL, szPath, 512);
	for (int i=strlen(szPath)-1; i>=0; i--)
		if (szPath[i]=='\\') { szPath[i+1]=0; break; };

	sprintf((char*)buf,"SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters", ServiceName);
	RegCreateKey(HKEY_LOCAL_MACHINE, (char*)buf, &hk);

	RegSetValueEx(hk, "BasePath", 0, REG_EXPAND_SZ, (const unsigned char*)szPath, strlen(szPath)+1);

	sprintf((char*)buf,"\\\\,\\COM1", szPath);
	RegSetValueEx(hk, "PortName", 0, REG_EXPAND_SZ, (const unsigned char*)buf, strlen((char*)buf)+1);

	RegCloseKey(hk);
};