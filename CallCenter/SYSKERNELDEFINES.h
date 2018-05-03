

#define SCMD_PROCCLIENTCMD			0x01
#define SCMD_SAVEPROFILE			0x02
#define SCMD_LOADPROFILE			0x03
#define SCMD_RELOADRMOPROFILE		0x04
#define SCMD_LOADPIPEINSTRMOPROFILE	0x05
#define SCMD_RELOADSGPROFILE		0x06

#define SCMD_USERSPROFILEACCESS		0x10
#define SCMD_SERVGPROFILEACCESS		0x11
#define SCMD_SLPPROFILEACCESS		0x12

#define SCMD_ADDRINGINQUEUE			0x20
#define SCMD_DELETERINGINQUEUE		0x21

#define SCMD_FINDRMOFORRINGINSERGP	0x30

#define SCMD_REGISTEROPERATOR		0x50
#define SCMD_UNREGISTEROPERATOR		0x51

#define SCMD_SETACTIVERMOINSG		0x40
#define SCMD_REQESTCOMMSTATE		0x41
#define SCMD_DECACTOPTINSG			0x42
#define SCMD_CHECKSLCOUNT			0x43 // линия d1, группа d2

#define SCMD_RINGONLINE				0x60 // звонок на линии. d1  группы обсл d2
#define SCMD_CONNECTIONLOST			0x61 // потеряно соединение на линии d1
#define SCMD_SLALARM1				0x62 // авария на СЛ d1
#define SCMD_SLALARM2				0x63 // авария на СЛ d1: не исходного состяния
#define SCMD_RMOALARM				0x64 // авария на РМО d1 - нет цепи
#define SCMD_REMOTERINGREQ			0x65 // удалить звонок из очереди на линию. d1
#define SCMD_SETRMOINSERV			0x66 // РМО d1 в работе

#define SCMD_USERPRESSSCROLL		0x70
#define SCMD_USERPRESSPAUSE			0x71


//===========================================================================

#define CCS_DEFAULT					0x00
#define CCS_RING					0x01
#define CCS_ALARM					0x02
#define CCS_ALARM2					0x03
#define CCS_COMBUSY					0x05
#define CCS_CALLINPROGRESS			0x06
#define CCS_HOLD					0x07
#define CCS_DIALINGPROGRESS			0x09
#define CCS_BLOCKED					0x0e

#define CCS_RMALARM					0x00
#define CCS_RMINUSE					0x01

#define CCS_SLBLOCK					0x0D
#define CCS_SLHOLD					0x0E
#define CCS_SLSETTODEFAULT			0x0F

#define CCS_RMBLOCK					0x0D
#define CCS_RMTONE					0x0E
#define CCS_RMDEFAULT				0x0F
