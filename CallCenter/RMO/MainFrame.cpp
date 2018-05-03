// MainFrame.cpp : implementation file
//

#include "stdafx.h"
#include "RMO.h"
#include "MainFrame.h"
#include <winioctl.h>

#include "RMOClientPipe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BORDERWIDTH		4

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
BOOL CMainFrame::RegisterWindowClass()
{
WNDCLASS wndcls;
HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, CCCMF_CLASSNAME, &wndcls)))
	{
		wndcls.style			= CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc		= ::DefWindowProc;
		wndcls.cbClsExtra		= 0;
		wndcls.cbWndExtra		= 0;
		wndcls.hInstance		= hInst;
		wndcls.hIcon			= NULL;
		wndcls.hCursor			= AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground	= (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName		= NULL;
		wndcls.lpszClassName	= CCCMF_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{	AfxThrowResourceException();
			return FALSE; };
	};
	return TRUE;
}

CMainFrame::CMainFrame()
{
	RegisterWindowClass();
	GLScrollLock = true;
	ScrollLockOn = false;
	SLN[0]=0;
	SZPR=1;
	QUEUESTATE = ::GetSysColor(COLOR_3DFACE);
}

CMainFrame::~CMainFrame()
{
}

BEGIN_MESSAGE_MAP(CMainFrame, CWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_HOOKMESSAGE, OnKbdHook)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

#define __SZCHNGMPLT 1.05

void CMainFrame::OnKbdHook(WPARAM wParam, LPARAM lParam)
{

	lParam &= 0xE1FFFFFF;

	if (lParam==0xE1460001 || lParam==0xE9460001)  //CTRL+ALT+BREAK
	{
		theApp.bDoingBackgroundProcessing = false;
		return;
	};

	switch (lParam&0x20FF0001)
	{
		case 0x204E0001: // ctrl alt +
			if (SZPR<3) SZPR *= __SZCHNGMPLT;
			Resize();
			return;
		case 0x204A0001: // ctrl alt +
			if (SZPR>0.4) SZPR /= __SZCHNGMPLT;
			Resize();
			return;
		case 0x20370001: // ctrl alt +
			SZPR = 1;
			Resize();
			return;
	};

	//
	switch (lParam)
	{
		case 0x00460001: // Scroll Lock keydown
//		case 0x08460001:
			theApp.CRCP->SendCommand(RMCMD_REQUESTBUSYSTATE);
			SetScrollLock(false);
			break;
		case 0xC0450001: // Break keyup
//		case 0xC8450001:
			theApp.CRCP->SendCommand(RMCMD_ANSWERKEYPRESSED);
			break;
	};

/*char buf[20];
	sprintf(buf, "0x%X 0x%08X", wParam, lParam);
	this->SetSubText(buf);*/

/*	switch (wParam)
	{
		case VK_NUMPAD0: SetQueueState(0); break;
		case VK_NUMPAD1: SetQueueState(1); break;
		case VK_NUMPAD2: SetQueueState(2); break;
		case VK_NUMPAD3: SetQueueState(3); break;
		case VK_NUMPAD4: SetQueueState(4); break;
		case VK_NUMPAD5: SetQueueState(5); break;
		case VK_NUMPAD6: SetQueueState(6); break;
	};*/
}

void CMainFrame::Resize()
{
CRect rect;
	GetWindowRect(&rect);
	rect.bottom = rect.top + MAINFRAMESIZE.cy*SZPR; 
	rect.right = rect.left + MAINFRAMESIZE.cx*SZPR;
	MoveWindow(rect);
	this->Invalidate();
}

#define IOCTL_KEYBOARD_SET_INDICATORS        CTL_CODE(FILE_DEVICE_KEYBOARD, 0x0002, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_KEYBOARD_QUERY_INDICATORS      CTL_CODE(FILE_DEVICE_KEYBOARD, 0x0010, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _KEYBOARD_INDICATOR_PARAMETERS {
    USHORT UnitId;          // Unit identifier.
    USHORT    LedFlags;     // LED indicator state.
} KEYBOARD_INDICATOR_PARAMETERS, *PKEYBOARD_INDICATOR_PARAMETERS;

KEYBOARD_INDICATOR_PARAMETERS InputBuffer;    // Input buffer for DeviceIoControl
KEYBOARD_INDICATOR_PARAMETERS OutputBuffer;   // Output buffer for DeviceIoControl
ULONG               DataLength = sizeof(KEYBOARD_INDICATOR_PARAMETERS);
ULONG               ReturnedLength; // Number of bytes returned in output buffer
BYTE KbdBuf[256];

void CMainFrame::SetScrollLock(bool state)
{
	if (hndKbdDev!=INVALID_HANDLE_VALUE)
	{   
		DeviceIoControl(hndKbdDev, IOCTL_KEYBOARD_QUERY_INDICATORS,
              &InputBuffer, DataLength,
              &OutputBuffer, DataLength,
              &ReturnedLength, NULL);
		OutputBuffer.LedFlags &= ~1;
		OutputBuffer.LedFlags |= state?1:0;//ScrollLockOn;

		DeviceIoControl(hndKbdDev, IOCTL_KEYBOARD_SET_INDICATORS,
              &OutputBuffer, DataLength,
			  NULL,   0,  &ReturnedLength, NULL);
	}
	else
	{
//		GetKeyboardState(KbdBuf);
//		KbdBuf[VK_SCROLL]=state;
//		SetKeyboardState(KbdBuf);
	};
}

void CMainFrame::SetScrollTimer(void)
{
	SetTimer(2, 100, NULL);
}

void CMainFrame::KillScrollTimer(void)
{
	KillTimer(2);
	SetScrollLock(0);
}

void CMainFrame::SetSLNum(unsigned k)
{
	sprintf(SLN, "%d", k);
	RedrawWindow();
}

void CMainFrame::Show(void)
{
	CreateEx(WS_EX_TOPMOST|WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW, 
		CCCMF_CLASSNAME, "==========", WS_VISIBLE|WS_POPUP, 500, 0,
		190, 60, ::GetDesktopWindow(), NULL, NULL); //80
	hndKbdDev = INVALID_HANDLE_VALUE;
	DefineDosDevice(DDD_RAW_TARGET_PATH, "Kbd", "\\Device\\KeyboardClass0");
	hndKbdDev = CreateFile("\\\\.\\Kbd", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
}


void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	ptLBD.x = point.x; ptLBD.y = point.y;
	CWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (nFlags&MK_LBUTTON)
	{
		int dx,dy;
		dx = (signed short)point.x-ptLBD.x; 
		dy = (signed short)point.y-ptLBD.y;
		RECT rect, rect2; GetWindowRect(&rect); GetDesktopWindow()->GetWindowRect(&rect2);
		if (rect.left<-dx) dx=-rect.left; if (rect.top<-dy) dy=-rect.top;
		if (rect.right+dx>rect2.right) dx = rect2.right-rect.right;
		if (rect.bottom+dy>rect2.bottom) dy = rect2.bottom-rect.bottom;
		MoveWindow(rect.left+dx, rect.top+dy, rect.right-rect.left, rect.bottom-rect.top, TRUE);
	};
	CWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	DrawFrame(dc);
	DrawTextWindow(dc);
	DrawSubTextWindow(dc);
	DrawLeftSubTextWindow(dc);
}

void CMainFrame::SetText(const char *str, COLORREF Color, bool Blink, DWORD _TextStyle)
{
	TextVisible = true;
	Text = str;
	TextColor = Color;
	TextStyle = _TextStyle;
	KillTimer(0);
	if (Blink) SetTimer(0, 200, NULL);
	InvalidateRect(TextWinRect, FALSE);
}

void CMainFrame::SetSubText(const char *str, bool _ALARM)
{
	SubTextVisible = true;
	SubText = str;
	ALARM = _ALARM;
	KillTimer(1);
	if (ALARM) SetTimer(1, 200, NULL);
	InvalidateRect(SubTextWinRect, FALSE);
}

void CMainFrame::SetQueueState(int k)
{
	switch (k)
	{
		case 0: QUEUESTATE = ::GetSysColor(COLOR_3DFACE); break;
		case 1: QUEUESTATE = 0x008800; break;
		case 2: QUEUESTATE = 0x00DDDD; break;
		default: QUEUESTATE = 0x0000FF; break;
	};
	InvalidateRect(LeftSubTextWinRect, FALSE);
}

void CMainFrame::DrawFrame(CDC &dc)
{
CRect rect;
	GetClientRect(&rect);
	dc.DrawEdge(rect, BDR_RAISEDINNER, BF_RECT);
	rect = TextWinRect;
	rect.InflateRect(1,1,1,1);
	dc.DrawEdge(rect, EDGE_SUNKEN, BF_RECT);
	rect = SubTextWinRect;
	rect.InflateRect(1,1,1,1);
	dc.DrawEdge(rect, BDR_SUNKENOUTER, BF_RECT);
	rect = LeftSubTextWinRect;
	rect.InflateRect(1,1,1,1);
	dc.DrawEdge(rect, BDR_SUNKENOUTER, BF_RECT);

}

void CMainFrame::DrawTextWindow(CDC &dc)
{
	dc.FillSolidRect(TextWinRect, 0);
	if (TextVisible)
	{
		dc.SetTextColor(TextColor);
CFont *PrevFont = dc.SelectObject(&Font);
		dc.DrawText(Text, TextWinRect, TextStyle);
		dc.SelectObject(PrevFont);
	};
}

void CMainFrame::DrawLeftSubTextWindow(CDC &dc)
{
	dc.FillSolidRect(LeftSubTextWinRect, QUEUESTATE);
CRect rect;
	rect = LeftSubTextWinRect;
	dc.SetBkColor(QUEUESTATE);
	dc.SetTextColor(0);
	dc.SetBkMode(TRANSPARENT);
CFont *PrevFont = dc.SelectObject(&Font2);
	dc.DrawText(SLN, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	dc.SelectObject(PrevFont);
}

void CMainFrame::DrawSubTextWindow(CDC &dc)
{
	dc.FillSolidRect(SubTextWinRect, ::GetSysColor(COLOR_3DFACE));
	if (SubTextVisible)
	{
		dc.SetBkColor(::GetSysColor(COLOR_3DFACE));
		dc.SetTextColor(COLORREF(ALARM?0:0));
		dc.SetBkMode(TRANSPARENT);
CFont *PrevFont = dc.SelectObject(&Font2);
		dc.DrawText(SubText, SubTextWinRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		dc.SelectObject(PrevFont);
	};
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	TextWinRect.top = BORDERWIDTH;
	TextWinRect.left = BORDERWIDTH;
	TextWinRect.bottom = 2*cy/3;
	TextWinRect.right = cx - BORDERWIDTH;
	SubTextWinRect.top = TextWinRect.bottom + BORDERWIDTH;
	SubTextWinRect.left = BORDERWIDTH+cx/5;
	SubTextWinRect.bottom = cy - BORDERWIDTH;
	SubTextWinRect.right = cx - BORDERWIDTH;
	LeftSubTextWinRect.top = TextWinRect.bottom + BORDERWIDTH;
	LeftSubTextWinRect.left = BORDERWIDTH;
	LeftSubTextWinRect.bottom = cy - BORDERWIDTH;
	LeftSubTextWinRect.right = cx/5;

CPaintDC dc(this);

NONCLIENTMETRICS NCM;
	NCM.cbSize = sizeof(NCM);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NCM), &NCM, 0);

	NCM.lfMenuFont.lfHeight = SubTextWinRect.Height();
	NCM.lfMenuFont.lfQuality = PROOF_QUALITY;
	Font2.Detach();
	Font2.CreateFontIndirect(&NCM.lfMenuFont);

	NCM.lfMenuFont.lfHeight = TextWinRect.Height();
	NCM.lfMenuFont.lfQuality = PROOF_QUALITY;
	Font.Detach();
	Font.CreateFontIndirect(&NCM.lfMenuFont);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
		case 0:
			TextVisible = !TextVisible;
			InvalidateRect(TextWinRect, FALSE);
			break;
		case 1:
			SubTextVisible = !SubTextVisible;
			InvalidateRect(SubTextWinRect, FALSE);
			break;
		case 2:
			ScrollLockOn = !ScrollLockOn;
			SetScrollLock(ScrollLockOn);
			break;
	};
	
	CWnd::OnTimer(nIDEvent);
}

BOOL CMainFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::DestroyWindow();
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	theApp.PostThreadMessage(WM_QUIT,0,0);
	CWnd::OnClose();
}
