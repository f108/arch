
#define KHTMAILSLOTNAME "\\\\.\\mailslot\\KHTMAILSLOT"

struct __ST_KeyboardHookTag
{
	HHOOK hKbdHook;
	HWND MainFrame;
	unsigned char SupressingFlags[256];
	HINSTANCE hModule;
};

