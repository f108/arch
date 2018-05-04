// BitmapView.cpp : implementation file
//

#include "stdafx.h"
#include "Editor.h"
#include "BitmapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapView

IMPLEMENT_DYNCREATE(CBitmapView, CScrollView)

CBitmapView::CBitmapView()
{
	RegisterWindowClass();
	Grid_X=0; Grid_Y=0;
}

CBitmapView::~CBitmapView()
{
	int i=0;
}


BEGIN_MESSAGE_MAP(CBitmapView, CScrollView)
	//{{AFX_MSG_MAP(CBitmapView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBitmapView::RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, CBV_CLASSNAME, &wndcls)))
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
        wndcls.lpszClassName    = CBV_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CBitmapView drawing

void CBitmapView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 500;
	SetScrollSizes(MM_TEXT, sizeTotal);
	ModifyStyle(0, WS_BORDER, SWP_FRAMECHANGED);
	ModifyStyleEx(WS_EX_NOPARENTNOTIFY, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
}

void CBitmapView::OnDraw(CDC* pDC)
{
	if (Grid_X!=0 && Grid_Y!=0)
	{
		for (int i=0; i<256; i+=16)
		{
			pDC->MoveTo(i,0);
			pDC->LineTo(i,300);
			pDC->MoveTo(0,i);
			pDC->LineTo(300,i);
		};
	};

/*	CDibDoc* pDoc = GetDocument();

	HDIB hDIB = pDoc->GetHDIB();
	if (hDIB != NULL)
	{
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);*/



//	CDocument* pDoc = GetDocument();
//	pDC->LineTo(100,100);
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapView diagnostics

#ifdef _DEBUG
void CBitmapView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CBitmapView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBitmapView message handlers

void CBitmapView::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::PreSubclassWindow();
	OnInitialUpdate();
}

void CBitmapView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CBitmapView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	
	UnsubclassWindow();
}

void CBitmapView::SetGrid(int dx, int dy)
{
	Grid_X = dx;
	Grid_Y = dy;
}

