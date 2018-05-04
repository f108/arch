// FontEditor.cpp : implementation file
//

#include "stdafx.h"
#include "Editor.h"
#include "FontEditor.h"
#include "AddNewFontDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString FontFolder="f:\\1234\\";

/////////////////////////////////////////////////////////////////////////////
// CFontEditor dialog

CFontEditor::CFontEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CFontEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontEditor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	EdSymbBuf=NULL;
	CMV.Init(16,16,NULL);
	CMV.ChangeAttr(CA_NOTIFY_MOUSEMESSAGE|CA_NOTIFY_CUSTDRAW);
	HS=0; VS=0;
	SelectedItem = 0;
}


void CFontEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontEditor)
	DDX_Control(pDX, IDC_COMBO1, m_FontList);
	DDX_Control(pDX, IDC_CUSTOM1, CMV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFontEditor, CDialog)
	//{{AFX_MSG_MAP(CFontEditor)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_BUTTON2, OnSave)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontEditor message handlers

BOOL CFontEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CSE.Create(IDD_SMBEDITOR, this);
	ReadFontList();
	LBtnDown = CPoint(-1,  -1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFontEditor::OnButton1() 
{
	// TODO: Add your control notification handler code here
CAddNewFontDlg dlg;

	if (dlg.DoModal(FontName, HS, VS)!=IDOK) return;
	FontName+=".pfn";
	delete[] EdSymbBuf;
	EdSymbBuf = new char[256*HS*VS];
	memset(EdSymbBuf, 0, 256*HS*VS);
	memset(Changed, 0, sizeof(Changed));
	CMV.RedrawWindow();
	CSE.SetParam(NULL, HS, VS, &EdSymbBuf[SelectedItem*HS*VS]);
}

void CFontEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	LBtnDown = point;

	CDialog::OnLButtonDown(nFlags, point);
}

void CFontEditor::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if (nFlags&0x20)
	{
		if (LBtnDown==point)
		{
			int CharIndex = point.y*16+point.x;
			CString str;
			str.Format("0x%02X \"%c\"", CharIndex, CharIndex);
			CSE.SetParam(str, HS, VS, &EdSymbBuf[CharIndex*HS*VS]);
			CSE.ShowWindow(SW_SHOW);
			SelectedItem = CharIndex;
		}
		else 
		{
			if (LBtnDown.x!=-1 && LBtnDown.y!=-1)
			{
				unsigned char PrevCh = LBtnDown.y*16+LBtnDown.x;
				unsigned char Ch = point.y*16+point.x;
				memcpy(&EdSymbBuf[Ch*HS*VS], &EdSymbBuf[PrevCh*HS*VS], HS*VS);
				SelectedItem = Ch;
				SendMessage(WM_MEASUREITEM, 0, (WPARAM)&point);
				LBtnDown = CPoint(-1,  -1);
			};
		};
	};
	
	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CFontEditor::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CSE.SetParam("", 0, 0, NULL);
	CSE.DestroyWindow();
	return CDialog::DestroyWindow();
}


void CFontEditor::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	SCustMVDrawItem *MVDI = (SCustMVDrawItem*)lpDrawItemStruct;

CRect rect;
CString str;
int i;
COLORREF color;
	unsigned char ch = MVDI->y*16+MVDI->x;
	str.Format("%c", ch<0x20?' ':ch);
	rect.left =MVDI->x*MVDI->xs/16; rect.right = (MVDI->x+1)*MVDI->xs/16;
	rect.top = MVDI->y*MVDI->ys/16; rect.bottom = (MVDI->y+1)*MVDI->ys/16;
	MVDI->dc->FillSolidRect(rect, 0);
	color=0x888888;
	for (i=ch*HS*VS; i<(ch+1)*HS*VS; i++)
		if (EdSymbBuf[i]!=0) {color=0xFFFF00; break;};
	if (Changed[ch]==true) color=0xFF;

	MVDI->dc->SetTextColor(color);

	MVDI->dc->DrawText(str, &rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

void CFontEditor::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
//	CPoint *point = (CPoint*)lpMeasureItemStruct;
	if (Changed[SelectedItem]) return;
	Changed[SelectedItem]=true;
	CMV.RedrawItem(SelectedItem%16, SelectedItem/16);
//	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

#define FONTFILEID _TEXT("\x0PanelFontV00")

void CFontEditor::OnSave() 
{
	// TODO: Add your control notification handler code here

HANDLE hFile;
DWORD cbw;
CString FileName = FontFolder+FontName;

	hFile = CreateFile(FileName, GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, NULL);
	WriteFile(hFile, FONTFILEID, sizeof(FONTFILEID), &cbw, NULL);
	WriteFile(hFile, &HS, sizeof(HS), &cbw, NULL);
	WriteFile(hFile, &VS, sizeof(VS), &cbw, NULL);
	WriteFile(hFile, EdSymbBuf, 256*HS*VS, &cbw, NULL);
	CloseHandle(hFile);
	memset(Changed, 0, sizeof(Changed));
	CMV.RedrawWindow();
}

void CFontEditor::ReadFontList(void)
{
WIN32_FIND_DATA WFD;
CString FileMask = FontFolder+"*.pfn";

	WFD.dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	m_FontList.ResetContent();
	HANDLE hFind = FindFirstFile(FileMask, &WFD);
	for (;;)
	{
		m_FontList.AddString(WFD.cFileName);
		if (!FindNextFile(hFind, &WFD)) break;
	};
//	CloseHandle(hFind);
}

void CFontEditor::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here

int CurSel = m_FontList.GetCurSel();
	if (CurSel==-1) return;

HANDLE hFile;
DWORD cbw;
CString FileName;
char buf[20];

	m_FontList.GetLBText(CurSel, FileName);
	FileName = FontFolder+FileName;
	hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);
	if (hFile==INVALID_HANDLE_VALUE) return;
	delete[] EdSymbBuf;
	m_FontList.GetLBText(CurSel, FontName);

	ReadFile(hFile, buf, sizeof(FONTFILEID), &cbw, NULL);
	ReadFile(hFile, &HS, sizeof(HS), &cbw, NULL);
	ReadFile(hFile, &VS, sizeof(VS), &cbw, NULL);
	EdSymbBuf = new char[256*HS*VS];

	ReadFile(hFile, EdSymbBuf, 256*HS*VS, &cbw, NULL);
	CloseHandle(hFile);
	memset(Changed, 0, sizeof(Changed));
	CMV.RedrawWindow();
	CSE.SetParam(NULL, HS, VS, &EdSymbBuf[SelectedItem*HS*VS]);
}

void CFontEditor::OnButton3() 
{
	// TODO: Add your control notification handler code here

CFileDialog dlg(true, ".fon");

	if (dlg.DoModal()!=IDOK) return;

	CString filename = dlg.GetFileName();

	struct { short a; short x; short y; short k;} FontInfo;
HANDLE hFile;
DWORD cbr;

	hFile = CreateFile(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, NULL);
	ReadFile(hFile, (void*)&FontInfo, sizeof(FontInfo), &cbr, NULL);
char *buf = new char[FontInfo.k*(256-32)];
	ReadFile(hFile, buf, FontInfo.k*(256-32), &cbr, NULL);
	
	delete[] EdSymbBuf;
	EdSymbBuf = new char[256*FontInfo.x*FontInfo.y];
	memset(EdSymbBuf, 0, 256*FontInfo.x*FontInfo.y);
	HS = FontInfo.x; VS = FontInfo.y;

	for (int ch=0; ch<256; ch++)
	{
		for (int i=0; i<FontInfo.y; i++)
			for (int j=0; j<FontInfo.x; j++)
				EdSymbBuf[ch*HS*VS+i*HS+j] = ((buf[(ch)*FontInfo.k+i] >> (8-j-1))&1);
		cbr=0;
	};

	CloseHandle(hFile);
	delete[] buf;
//	memset(Changed, 0, sizeof(Changed));
	CMV.RedrawWindow();
//	CSE.SetParam(NULL, HS, VS, &EdSymbBuf[SelectedItem*HS*VS]);

	
}
