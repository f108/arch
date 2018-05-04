// LEDServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LEDServer.h"

#include "FrameSet.h"
#include <iostream.h>

#include "ServiceModule.h"

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

char PortName[512];
char Path[512];


void LoadRegData(void);

int main(int argc, char* argv[])
{
	if (argc>1)
	{
		if (*argv[1]=='-' || *argv[1]=='/')
		{
			DWORD res;
			if (strcmp(argv[1]+1, "install")==0) 
			{ res = __CServiceModule.InstallService(); return 0;}
			else if (strcmp(argv[1]+1, "remove")==0) 
			{ res = __CServiceModule.RemoveService(); return 0; }
			else if (strcmp(argv[1]+1, "run")==0) 
			{ __CServiceModule.ServiceInProgress = true; Main(); return 0;}
			else if (strcmp(argv[1]+1, "?")==0)
			{
				cout << "SP09 service" << endl <<
					"  /install        to install the service" << endl <<
					"  /remove         to remove the service" << endl <<
					"  /run            to run the service" << endl <<
					"  /?              this help" << endl;
				return 0;
			};
			cout << res << endl;
		};
	};

	__CServiceModule.SetDispatchTable();

	return 0;
}
 


void Main(void)
{
	LoadRegData();
CFrameSet CFS;
CPanelImage CPI;
HANDLE hFind = INVALID_HANDLE_VALUE;
HANDLE hFile;
DWORD filesize;
char *buf, *ptr;
WIN32_FIND_DATA WFD;
char FindMask[512];
char FileName[512];
bool HaveFile;
DWORD NextTransmissionTime = GetTickCount();
bool ReadNew=true;

	strcpy(FindMask, Path);
	strcat(FindMask, "*.tsk");
	WFD.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;

	for (;__CServiceModule.ServiceInProgress;)
	{
		if (hFind!=INVALID_HANDLE_VALUE) FindClose(hFind);
		for (hFind = FindFirstFile(FindMask, &WFD), HaveFile=true;HaveFile;HaveFile=FindNextFile(hFind, &WFD))
		{
			strcpy(FileName, Path);
			strcat(FileName, WFD.cFileName);

			hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (hFile==INVALID_HANDLE_VALUE) 
			{ Sleep(100); break;};

			filesize = GetFileSize(hFile, NULL);
			buf = new char[filesize];
			ptr=buf;
			ReadFile(hFile, buf, filesize, &filesize, NULL);

			CPI.Clear();

			for (;ptr;)
				ptr = CPI.ExecProg(ptr);

			delete[] buf;

			CFS.LoadFrom(&CPI, CPI.GetNotNullFrameCount());

			NextTransmissionTime -= CFS.GetTrasmissionTime()+100;

			for (;NextTransmissionTime>GetTickCount() && __CServiceModule.ServiceInProgress;) 
				Sleep(10);

			CFS.SendToPort(PortName, __CServiceModule.ServiceInProgress);

			NextTransmissionTime = GetTickCount()+CFS.GetExpositionTime();
		};
	};
	return;
}

void LoadRegData(void)
{
HKEY hk;
DWORD dwData;
UCHAR buf[256];
DWORD Type = REG_EXPAND_SZ;
DWORD k;

	sprintf((char*)buf,"SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters", SRVNAME);
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, (char*)buf, 0, KEY_READ, &hk);
	if (hk==0) return;

	dwData = 512;
	k = RegQueryValueEx(hk, "PortName", NULL, &Type, (unsigned char *)PortName, &dwData);

	dwData = 512;
	RegQueryValueEx(hk, "BasePath", NULL, &Type, (unsigned char *)Path, &dwData);

	RegCloseKey(hk);
	return;
};

