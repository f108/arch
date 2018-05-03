// SLDLG.cpp : implementation file
//

#include "stdafx.h"
#include "AdmCom.h"
#include "SLDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSLDLG property page

IMPLEMENT_DYNCREATE(CSLDLG, CPropertyPage)

CSLDLG::CSLDLG() : CPropertyPage(CSLDLG::IDD)
{
	//{{AFX_DATA_INIT(CSLDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSLDLG::~CSLDLG()
{
}

void CSLDLG::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSLDLG)
	DDX_Control(pDX, IDC_EDIT1, CE);
	DDX_Control(pDX, IDC_COMBO1, CCB);
//	DDX_Control(pDX, IDC_LIST2, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSLDLG, CPropertyPage)
	//{{AFX_MSG_MAP(CSLDLG)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_CBN_SELENDOK(IDC_COMBO1, OnSelendokCombo1)
	ON_CBN_SELENDCANCEL(IDC_COMBO1, OnSelendcancelCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSLDLG message handlers
void CSLDLG::SetSLProfile(TSNPData *TND)
{
	for (int i=0; i<12; i++)
		(*TND) >> SLData[i].SG >> SLData[i].Comment;
	RedrawWindow();
}

BOOL CSLDLG::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	theApp.CACP.SendCommand(RMCMD_GETSLLIST);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSLDLG::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam==0x0d)
		{
			pMsg->wParam = 0x20;
			pMsg->lParam = 0x00390001;
			DoEditObject();
		};
	};
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CSLDLG::DoEditObject(void)
{
int k;

	if (!CCB.IsWindowVisible() && !CE.IsWindowVisible())
	{
		CCB.ShowWindow(SW_SHOW);
	};
}

int COLWIDTH[] = { 60, 140, 300};
#define HOROFFSET 20
#define VERTOFFSET 20

void CSLDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
CFont *PrevFont = dc.SelectObject(GetFont());
CRect rect, rect2, rect3;
	CCB.GetClientRect(&rect);
int RCH = rect.Height(), k;
char buf[512];

	rect.top = VERTOFFSET;
	for (int i=0; i<12; i++)
	{
		rect.left = HOROFFSET;
		for (int j=0; j<3; j++)
		{
			rect.right = rect.left+COLWIDTH[j];
			rect.bottom = rect.top+RCH;
			switch (j)
			{
				case 0:
					sprintf(buf, "%d", i+1);
					dc.DrawText(buf, -1, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
					break;
				case 1:
					buf[0]=0;
					for (k=0; k<CCB.GetCount(); k++)
					{
						if (CCB.GetItemData(k)==SLData[i].SG)
						{
							CCB.GetLBText(k, buf);
							break;
						};
					};
					if (strlen(buf)==0) strcpy(buf, "INVALID");
					dc.DrawText(buf, -1, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
					break;
				case 2:
					rect3 = rect;
					rect3.left += 3;
					dc.DrawText(SLData[i].Comment.c_str(), -1, rect3, DT_VCENTER|DT_SINGLELINE);
					break;
			};
			rect2 = rect;
			rect2.DeflateRect(1,1,1,1);
			dc.DrawEdge(rect2, BDR_SUNKENOUTER, BF_RECT);
			rect.left = rect.right+2;
		};
		rect.top = rect.bottom;
	};

	dc.SelectObject(PrevFont);
}

void CSLDLG::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (CE.IsWindowVisible())
	{
		CE.ShowWindow(SW_HIDE);
		RedrawWindow();
	}
CRect rect;
	CCB.GetClientRect(&rect);
int i,j,k;
int RCH = rect.Height();
	i = (point.y-VERTOFFSET)/rect.Height();
	LINEINDEX = i;
	if (i>=0 & i<12)
	{
		rect.left = HOROFFSET + COLWIDTH[0]+2;
		rect.right = rect.left + COLWIDTH[1];
		rect.top = VERTOFFSET + i*RCH;
		rect.bottom = rect.top + RCH;

		if (rect.PtInRect(point))
		{
			CCB.MoveWindow(rect, TRUE);
			for (k=0; k<CCB.GetCount(); k++)
			{	if (CCB.GetItemData(k)==SLData[i].SG)
				{
					CCB.SetCurSel(k);
					break;
				};
			};
			CCB.ShowWindow(SW_SHOW);
			CCB.ShowDropDown(TRUE);
		}
		else
		{
			rect.left = rect.right+2;
			rect.right += COLWIDTH[2];
			if (rect.PtInRect(point))
			{
				CE.SetWindowText(SLData[i].Comment.c_str());
				CE.MoveWindow(rect, TRUE);
				CE.ShowWindow(SW_SHOW);
			};
		};
	};
	CPropertyPage::OnLButtonDown(nFlags, point);
}

void CSLDLG::SendData(void)
{
	// TODO: Add your specialized code here and/or call the base class
TSNPData *TND = new TSNPData;

	(*TND) << RMCMD_SETSLPROFILE << (unsigned __int32)LINEINDEX << SLData[LINEINDEX].SG << SLData[LINEINDEX].Comment;
	theApp.CACP.SendMessage(TND);
}

void CSLDLG::OnSelendokCombo1() 
{
int k = CCB.GetCurSel();
	if (k==-1) return;
	SLData[LINEINDEX].SG = CCB.GetItemData(k);
	CCB.ShowWindow(SW_HIDE);
	SendData();
	RedrawWindow();
}

void CSLDLG::OnSelendcancelCombo1() 
{
	CCB.ShowWindow(SW_HIDE);
	RedrawWindow();
}

void CSLDLG::OnKillfocusEdit1() 
{
char buf[200];

//	CE.ShowWindow(SW_HIDE);
	CE.GetWindowText(buf, 200);
	SLData[LINEINDEX].Comment = buf;	
	SendData();
}
