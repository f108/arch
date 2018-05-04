
#if !defined(AFX_LEDSERVER_H__5BA98AD0_CE64_405D_B22B_45E07D6C57DE__INCLUDED_)
#define AFX_LEDSERVER_H__5BA98AD0_CE64_405D_B22B_45E07D6C57DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#define SRVNAME "LEDPANEL"
#define SRVDISP "Служба ЦИП"
#define DESCSRV "Управляет выводом ЦИП"

extern char PortName[512];
extern char Path[512];

extern void Main(void);

#endif // !defined(AFX_LEDSERVER_H__5BA98AD0_CE64_405D_B22B_45E07D6C57DE__INCLUDED_)
