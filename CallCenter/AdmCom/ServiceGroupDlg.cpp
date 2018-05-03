// ServiceGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdmCom.h"
#include "ServiceGroupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\WSDEFINES.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceGroupDlg dialog

IMPLEMENT_DYNCREATE(CServiceGroupDlg, CPropertyPage)

CServiceGroupDlg::CServiceGroupDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CServiceGroupDlg::IDD)
{
	//{{AFX_DATA_INIT(CServiceGroupDlg)
	//}}AFX_DATA_INIT
	COLOR = 0;
	SGID=0;
	SGSrchMthRngCat=0;
	OperatorCount=0;
	QueueType=0;
}


void CServiceGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServiceGroupDlg)
	DDX_Control(pDX, IDC_CALLQUEUECNT, m_CallQueueCntEdit);
	DDX_Control(pDX, IDC_SPIN2, m_QueueCapSpin);
	DDX_Control(pDX, IDC_STATIC9, ST9);
	DDX_Control(pDX, IDC_STATIC8, ST8);
	DDX_Control(pDX, IDC_STATIC7, ST7);
	DDX_Control(pDX, IDC_STATIC6, ST6);
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
	DDX_Control(pDX, IDC_EDIT3, m_OperCount);
	DDX_Control(pDX, IDC_CHECK3, m_DONOTUSEQUEUE);
	DDX_Control(pDX, IDC_CHECK2, m_USEQUEUE);
	DDX_Control(pDX, IDC_CHECK1, m_BLINK);
	DDX_Control(pDX, IDC_LIST1, m_SGList);
	DDX_Control(pDX, IDC_COMBO3, m_RINGCAT);
	DDX_Control(pDX, IDC_STATIC5, ST5);
	DDX_Control(pDX, IDC_LIST2, m_RMOList);
	DDX_Control(pDX, IDC_STATIC4, ST4);
	DDX_Control(pDX, IDC_STATIC3, ST3);
	DDX_Control(pDX, IDC_STATIC2, ST2);
	DDX_Control(pDX, IDC_STATIC1, ST1);
	DDX_Control(pDX, IDC_COMBO1, m_CASEMETHOD);
	DDX_Control(pDX, IDC_EDIT2, m_DESC);
	DDX_Control(pDX, IDC_EDIT1, m_GRName);
	DDX_Control(pDX, IDC_BUTTON5, m_COLOR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServiceGroupDlg, CDialog)
	//{{AFX_MSG_MAP(CServiceGroupDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServiceGroupDlg message handlers
BOOL CServiceGroupDlg::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	m_SGList.ResetContent();
	theApp.CACP.SendCommand(RMCMD_GETUIDSERGRPLIST);
	m_Spin.SetRange(0,12);
	m_QueueCapSpin.SetRange(0,12);	
	return CPropertyPage::OnSetActive();
}

void CServiceGroupDlg::SetSGList(TSNPData *TND)
{
unsigned __int32 size, ui32;
char buf[200];
TZSuperShortString str;
int k;

	(*TND) >> size;
	theApp.CSLD->CCB.ResetContent();
	theApp.CSLD->CCB.AddString("Not attached");
	theApp.CSLD->CCB.SetItemData(0,1);
	theApp.CRLD->m_FSGList.ResetContent();
	m_SGList.ResetContent();
	for (int i=0; i<size; i++)
	{
		(*TND) >> ui32 >> str;
		sprintf(buf, "[%d]  %s ", ui32, str.c_str());
		k = m_SGList.AddString(buf);
		if (k!=LB_ERR)
			m_SGList.SetItemData(k, ui32);
		sprintf(buf, "%s", str.c_str());
		theApp.CSLD->CCB.AddString(buf);
		theApp.CSLD->CCB.SetItemData(i+1, ui32);
		theApp.CRLD->m_FSGList.AddString(buf);
		theApp.CRLD->m_FSGList.SetItemData(i, ui32);
	};
}

void CServiceGroupDlg::SetSGProfile(TSNPData *TND)
{
	(*TND) >> SGID >> SGCaption >>
			SGDescription >> COLOR >> BlinkBanner >> SGSrchMthRngCat >> RMIDOrder >>
			UseQueue >> QueueType >> UsingQueueByOperatorCount >> OperatorCount;
	MembersToDialog();
	Update();
CRect rect;
	m_COLOR.GetWindowRect(&rect);
	this->ScreenToClient(&rect);
	RedrawWindow(rect);
	m_RMOList.GetWindowRect(&rect);
	this->ScreenToClient(&rect);
	RedrawWindow(rect);
}

void CServiceGroupDlg::MembersToDialog(void)
{
	m_GRName.SetWindowText(SGCaption.c_str());
	m_DESC.SetWindowText(SGDescription.c_str());
	m_BLINK.SetCheck(BlinkBanner);
	m_CASEMETHOD.SetCurSel(SGSrchMthRngCat&0xFF);
	m_RINGCAT.SetCurSel((SGSrchMthRngCat>>8)&0xFF);
	m_USEQUEUE.SetCheck(UseQueue);
	m_QueueCapSpin.SetPos(QueueType);
char buf[4];
	sprintf(buf, "%d", OperatorCount);
	m_OperCount.SetWindowText(buf);
	m_DONOTUSEQUEUE.SetCheck(UsingQueueByOperatorCount);
	sprintf(buf, "%d", QueueType);
	m_CallQueueCntEdit.SetWindowText(buf);
}

void CServiceGroupDlg::DialogToMembers(void)
{
char buf[260];
	m_GRName.GetWindowText(buf, 259);
	SGCaption = buf;
	m_DESC.GetWindowText(buf, 259);
	SGDescription = buf;
	SGSrchMthRngCat = m_CASEMETHOD.GetCurSel() | (m_RINGCAT.GetCurSel()<<8);
	BlinkBanner = m_BLINK.GetCheck()==1;
	RMIDOrder.Reset();
	for (int i=0; i<m_RMOList.GetCount(); i++)
		RMIDOrder.Add(m_RMOList.GetItemData(i));
	UseQueue = m_USEQUEUE.GetCheck()==1;
	QueueType = m_QueueCapSpin.GetPos();
	UsingQueueByOperatorCount = m_DONOTUSEQUEUE.GetCheck()==1;
	OperatorCount = m_Spin.GetPos();
}

void CServiceGroupDlg::Update(void)
{
bool GROUP1, GROUP2, GROUP3, GROUP4;

	if (SGID==0)
	{ GROUP1=false; GROUP2=false; GROUP3=false; GROUP4=false; }
	else
	{
		GROUP1 = true;
		if ((SGSrchMthRngCat&SGSM_SRCHMTHMASK)==SGSM_SUC)
			GROUP2 = true;
		else
			GROUP2 = false;
		if (m_USEQUEUE.GetCheck()==1)
		{
			GROUP3 = true;
			if (m_DONOTUSEQUEUE.GetCheck()==1)
				GROUP4 = true;
			else
				GROUP4 = false;
		}
		else
		{
			GROUP3 = false;
			GROUP4 = false;
		};
	};

	ST3.EnableWindow(GROUP1);
	ST2.EnableWindow(GROUP1);
	ST1.EnableWindow(GROUP1);
	ST5.EnableWindow(GROUP1);
	m_CASEMETHOD.EnableWindow(GROUP1);
	m_DESC.EnableWindow(GROUP1);
	m_GRName.EnableWindow(GROUP1);
	m_RINGCAT.EnableWindow(GROUP1);
	m_BLINK.EnableWindow(GROUP1);
	m_USEQUEUE.EnableWindow(GROUP1);

	ST8.EnableWindow(GROUP3);
	ST9.EnableWindow(GROUP3);
	m_DONOTUSEQUEUE.EnableWindow(GROUP3);
	m_CallQueueCntEdit.EnableWindow(GROUP3);
	m_QueueCapSpin.EnableWindow(GROUP3);

	m_Spin.EnableWindow(GROUP4);
	m_OperCount.EnableWindow(GROUP4);
	ST7.EnableWindow(GROUP4);
	ST6.EnableWindow(GROUP4);

	m_CASEMETHOD.SetCurSel(SGSrchMthRngCat&SGSM_SRCHMTHMASK);
	m_RINGCAT.SetCurSel((SGSrchMthRngCat&SGSM_CALLCATEGORYMASK)>>8);

	ST4.EnableWindow(GROUP2);
}

void CServiceGroupDlg::OnPaint()
{
	CPaintDC dc(this);
CRect rect;
	m_COLOR.GetWindowRect(&rect);
	this->ScreenToClient(&rect);
	dc.DrawEdge(rect, EDGE_SUNKEN, BF_RECT);
	rect.DeflateRect(2,2,2,2);
	dc.FillSolidRect(rect, COLOR);

	if (SGID==0 || (SGSrchMthRngCat&SGSM_SRCHMTHMASK)!=SGSM_SUC)
	{
		CPaintDC dc2(&m_RMOList);
		m_RMOList.GetClientRect(&rect);
		dc2.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
	};
}

BOOL CServiceGroupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	theApp.CACP.SendCommand(RMCMD_GETUIDSERGRPLIST);
	Update();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CServiceGroupDlg::OnButton2()
{
	SGID = 0xffffffff;
	Update();
}

void CServiceGroupDlg::OnSelchangeCombo1()
{
	SGSrchMthRngCat = (SGSrchMthRngCat&~SGSM_SRCHMTHMASK)|m_CASEMETHOD.GetCurSel();
	Update();
	CRect rect;
	m_RMOList.GetWindowRect(&rect);
	this->ScreenToClient(&rect);
	RedrawWindow(rect);
}

void CServiceGroupDlg::OnButton4() 
{
	DialogToMembers();
TSNPData *TND = new TSNPData;
	(*TND) << RMCMD_SETSERGRPPROFILE << SGID << SGID << SGCaption << 
			SGDescription << COLOR << BlinkBanner << SGSrchMthRngCat << RMIDOrder <<
			UseQueue << QueueType << UsingQueueByOperatorCount << OperatorCount << 
/**/		(unsigned)0 << (unsigned)0 << (unsigned)0 << (unsigned)0; /* for future using */
	theApp.CACP.SendMessage(TND);
	theApp.CACP.SendCommand(RMCMD_GETUIDSERGRPLIST);
}

void CServiceGroupDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
CRect rect;
	m_COLOR.GetWindowRect(&rect);
	this->ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
	CColorDialog CCD;
		if (CCD.DoModal()==IDOK)
		{
			COLOR = CCD.GetColor();
			this->RedrawWindow();
		};
		return;
	};
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CServiceGroupDlg::OnCheck2() 
{
	Update();
}

void CServiceGroupDlg::OnCheck3() 
{
	Update();
}

void CServiceGroupDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
char buf[4];
	sprintf(buf, "%d", pNMUpDown->iPos);
	m_OperCount.SetWindowText(buf);
	*pResult = 0;
}

void CServiceGroupDlg::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
char buf[4];
	sprintf(buf, "%d", pNMUpDown->iPos);
	m_CallQueueCntEdit.SetWindowText(buf);
	*pResult = 0;
}

void CServiceGroupDlg::OnSelchangeList1() 
{
int k = m_SGList.GetCurSel();
	if (k==-1) return;
unsigned __int32 ui32;
	ui32 = m_SGList.GetItemData(k);

TSNPData *TND = new TSNPData;

	(*TND) << RMCMD_GETSERGRPPROFILE << ui32;
	theApp.CACP.SendMessage(TND);
}
