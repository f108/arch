// MatrixView.cpp : implementation file
//

#include "stdafx.h"
#include "Editor.h"
#include "MatrixView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatrixView

CMatrixView::CMatrixView()
{
	HS=0;
	VS=0;
	buf=NULL;
//	buf = new char[HS*VS];
//	for (int i=0; i<HS*VS; i++) buf[i]=i%3;
	RegisterWindowClass();
	CustAttr=0;
}

CMatrixView::~CMatrixView()
{
	delete[] buf;
}

BEGIN_MESSAGE_MAP(CMatrixView, CWnd)
	//{{AFX_MSG_MAP(CMatrixView)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMatrixView::RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, CMV_CLASSNAME, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = CMV_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMatrixView message handlers

void CMatrixView::Init(int _HS, int _VS, char *_buf)
{
	HS=_HS;
	VS=_VS;
	buf = _buf;
}

void CMatrixView::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd::PreSubclassWindow();
	this->ModifyStyle(0, WS_BORDER, SWP_FRAMECHANGED | WS_TABSTOP);
	this->ModifyStyleEx(WS_EX_NOPARENTNOTIFY, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
	SetFont(GetParent()->GetFont());
}

void CMatrixView::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	UnsubclassWindow();
}


void CMatrixView::OnPaint() 
{
	// TODO: Add your message handler code here
	CPaintDC dc(this); // device context for painting
	if (HS*VS==0) return;

int x,y;
CRect rect;
SCustMVDrawItem SCMVDI;

	GetUpdateRect(&rect);
	if (rect.Width()==0)
	{
		GetClientRect(&rect);
		SCMVDI.xs = rect.Width();
		SCMVDI.ys = rect.Height();
		for (x=0; x<HS; x++) 
			for (y=0; y<VS; y++) 
				if (CustAttr&CA_NOTIFY_CUSTDRAW)
				{
					SCMVDI.dc = &dc;
					SCMVDI.x = x; SCMVDI.y = y;
					GetParent()->SendMessage(WM_DRAWITEM, 0, (LPARAM)&SCMVDI);
				} 
				else if (buf!=NULL)
				{
					dc.FillSolidRect(x*rect.Width()/HS, y*rect.Height()/VS,
						(x+1)*rect.Width()/HS, (y+1)*rect.Height()/VS, buf[y*HS+x]==0?0:0x888888);
				};


	CPen Pen, *PrevPen;
		Pen.CreatePen(PS_DOT, 1, 0x00FFFF);
		PrevPen = dc.SelectObject(&Pen);
		GetClientRect(&rect);
		for (x=1; x<HS; x++) { dc.MoveTo(x*rect.Width()/HS, 0); dc.LineTo(x*rect.Width()/HS, rect.Height()); };
		for (y=1; y<VS; y++) { dc.MoveTo(0, y*rect.Height()/VS); dc.LineTo(rect.Width(), y*rect.Height()/VS); };
		dc.SelectObject(PrevPen);
	}
	else
	{
		CPoint Point;
		WhereMouse(Point, &Point);
		dc.FillSolidRect(Point.x*rect.Width()/HS, Point.y*rect.Height()/VS,
				(Point.x+1)*rect.Width()/HS, (Point.y+1)*rect.Height()/VS, buf[Point.y*HS+Point.x]==0?0:0x888888);
	};

	// Do not call CWnd::OnPaint() for painting messages
}

void CMatrixView::WhereMouse(CPoint mpxl, CPoint *mcl)
{
CRect rect;
	GetClientRect(&rect);
	mcl->x = mpxl.x*HS/rect.Width();
	mcl->y = mpxl.y*VS/rect.Height();
}

void CMatrixView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (CustAttr&CA_NOTIFY_MOUSEMESSAGE)
	{
CPoint MP;
		WhereMouse(point, &MP);
		GetParent()->SendMessage(WM_LBUTTONDOWN, 0x20|nFlags, MAKELPARAM(MP.x, MP.y));
		return;
	};
	if (buf==NULL) return;
CPoint MP;
	WhereMouse(point, &MP);
	if (MP.x>HS || MP.y>VS) return;
	buf[MP.y*HS+MP.x] = !buf[MP.y*HS+MP.x];
	PrevColor = buf[MP.y*HS+MP.x];
	CWnd::OnLButtonDown(nFlags, point);
CRect rect, rect2;
	GetClientRect(&rect2);
	rect.top=MP.y*rect2.Height()/VS;
	rect.bottom=(MP.y+1)*rect2.Height()/VS;
	rect.left=MP.x*rect2.Width()/HS;
	rect.right=(MP.x+1)*rect2.Width()/HS;
	RedrawWindow(&rect,NULL,RDW_INVALIDATE | RDW_UPDATENOW|RDW_NOERASE);
	if (CustAttr&CA_NOTIFY_CHANGEIMAGE)
		GetParent()->SendMessage(WM_LBUTTONDOWN, 0x30|nFlags, MAKELPARAM(MP.x, MP.y));
}

void CMatrixView::RedrawItem(int x, int y)
{
CRect rect, rect2;
	GetClientRect(&rect2);
	rect.top=y*rect2.Height()/VS;
	rect.bottom=(y+1)*rect2.Height()/VS;
	rect.left=x*rect2.Width()/HS;
	rect.right=(x+1)*rect2.Width()/HS;
	RedrawWindow(&rect,NULL,RDW_INVALIDATE | RDW_UPDATENOW|RDW_NOERASE);
}

void CMatrixView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (CustAttr&CA_NOTIFY_MOUSEMESSAGE)
	{
CPoint MP;
		WhereMouse(point, &MP);
		GetParent()->SendMessage(WM_LBUTTONUP, 0x20|nFlags, MAKELPARAM(MP.x, MP.y));
		return;
	};
	CWnd::OnLButtonUp(nFlags, point);
}

void CMatrixView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (buf==NULL) return;
	if (MK_LBUTTON&nFlags)
	{
	CPoint MP;
		WhereMouse(point, &MP);
		if (MP.x>HS || MP.y>VS) return;
		if (PrevColor != buf[MP.y*HS+MP.x])
		{
			buf[MP.y*HS+MP.x] = !buf[MP.y*HS+MP.x];
		CRect rect, rect2;
			GetClientRect(&rect2);
			rect.top=MP.y*rect2.Height()/VS;
			rect.bottom=(MP.y+1)*rect2.Height()/VS;
			rect.left=MP.x*rect2.Width()/HS;
			rect.right=(MP.x+1)*rect2.Width()/HS;
			RedrawWindow(&rect,NULL,RDW_INVALIDATE | RDW_UPDATENOW|RDW_NOERASE);
		};
	};
	CWnd::OnMouseMove(nFlags, point);
}
