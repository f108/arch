

#include "TFixedSizeBinaryData.hxx"

#define RMCMD_SRVKEEPALIVE				(unsigned __int8)0x00
#define RMCMD_WHOAREYOU					(unsigned __int8)0x01
#define RMCMD_MYNAME					(unsigned __int8)0x02
#define RMCMD_SETRMOSLNUM				(unsigned __int8)0x03

#define RMCMD_GETUIDUSERLIST			(unsigned __int8)0x10
#define RMCMD_GETUIDUSERLISTANS			(unsigned __int8)0x11
#define RMCMD_GETUSERPROFILE			(unsigned __int8)0x12
#define RMCMD_GETUSERPROFILEANS			(unsigned __int8)0x13
#define RMCMD_SETUSERPROFILE			(unsigned __int8)0x14

#define RMCMD_GETUIDSERGRPLIST			(unsigned __int8)0x20
#define RMCMD_GETUIDSERGRPLISTANS		(unsigned __int8)0x21
#define RMCMD_GETSERGRPPROFILE			(unsigned __int8)0x22
#define RMCMD_GETSERGRPPROFILEANS		(unsigned __int8)0x23
#define RMCMD_SETSERGRPPROFILE			(unsigned __int8)0x24

#define RMCMD_GETSLLIST					(unsigned __int8)0x30
#define RMCMD_GETSLLISTANS				(unsigned __int8)0x31
#define RMCMD_SETSLPROFILE				(unsigned __int8)0x32

#define RMCMD_REQUESTBUSYSTATE			(unsigned __int8)0x40
#define RMCMD_SETBUSYSTATE				(unsigned __int8)0x41
#define RMCMD_SHOWRINGBANNER			(unsigned __int8)0x42
#define RMCMD_SHOWCALLBANNER			(unsigned __int8)0x43
#define RMCMD_ANSWERKEYPRESSED			(unsigned __int8)0x44
#define RMCMD_SETALARMSTATE				(unsigned __int8)0x45
#define RMCMD_SETINSERVSTATE			(unsigned __int8)0x46
#define RMCMD_SETQUEUESTATE				(unsigned __int8)0x47

#define RMCMD_DISCONNECTANDSTAYOFFLINE	(unsigned __int8)0xFF

#define NPMAXMESSAGESIZE 4096

typedef TFixedSizeBinaryData<NPMAXMESSAGESIZE> TSNPData;

