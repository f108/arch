// RmoListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdmCom.h"
#include "RmoListDlg.h"

#include "..\WSDEFINES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRmoListDlg property page

IMPLEMENT_DYNCREATE(CRmoListDlg, CPropertyPage)

CRmoListDlg::CRmoListDlg() : CPropertyPage(CRmoListDlg::IDD)
{
	//{{AFX_DATA_INIT(CRmoListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Attr = 0;
	RMLineNumber = 0;
	RMOUID = 0;
}

CRmoListDlg::~CRmoListDlg()
{
}

void CRmoListDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRmoListDlg)
	DDX_Control(pDX, IDC_LIST3, m_FSGList);
	DDX_Control(pDX, IDC_STATIC5, ST5);
	DDX_Control(pDX, IDC_STATIC4, ST4);
	DDX_Control(pDX, IDC_STATIC3, ST3);
	DDX_Control(pDX, IDC_STATIC2, ST2);
	DDX_Control(pDX, IDC_STATIC1, ST1);
	DDX_Control(pDX, IDC_EDIT2, m_Desc);
	DDX_Control(pDX, IDC_BUTTON4, m_ChangeSGList);
	DDX_Control(pDX, IDC_LIST2, m_SGList);
	DDX_Control(pDX, IDC_COMBO2, m_LNumber);
	DDX_Control(pDX, IDC_CHECK1, m_DIS);
	DDX_Control(pDX, IDC_CHECK4, m_COMMCNG);
	DDX_Control(pDX, IDC_CHECK3, m_SRGPCNG);
	DDX_Control(pDX, IDC_CHECK2, m_USERCNG);
	DDX_Control(pDX, IDC_COMBO1, m_Category);
	DDX_Control(pDX, IDC_EDIT1, m_ComputerName);
	DDX_Control(pDX, IDC_LIST1, m_RMOList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRmoListDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CRmoListDlg)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_CHECK1, SetModifyKey)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_LBN_DBLCLK(IDC_LIST3, OnDblclkList3)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_CHECK2, SetModifyKey)
	ON_BN_CLICKED(IDC_CHECK3, SetModifyKey)
	ON_BN_CLICKED(IDC_CHECK4, SetModifyKey)
	ON_CBN_SELCHANGE(IDC_COMBO2, SetModifyKey)
	ON_EN_CHANGE(IDC_EDIT1, SetModifyKey)
	ON_EN_CHANGE(IDC_EDIT2, SetModifyKey)
	ON_LBN_KILLFOCUS(IDC_LIST3, OnKillfocusList3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRmoListDlg message handlers

BOOL CRmoListDlg::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_RMOList.ResetContent();
	theApp.CACP.SendCommand(RMCMD_GETUIDUSERLIST);
	
	return CPropertyPage::OnSetActive();
}

void CRmoListDlg::SetRmoList(TSNPData *TND)
{
unsigned __int32 size, ui32, ui32_2;
char buf[200];
TZSuperShortString str;
int k;

	(*TND) >> size;
	for (int i=0; i<size; i++)
	{
		(*TND) >> ui32 >> str >> ui32_2;
		sprintf(buf, "%d %s ", ui32, str.c_str());
		switch (ui32_2&RMOA_CATEGORYMASK)
		{
			case RMOA_OPERATOR: strcat(buf, " [OPR]"); break;
			case RMOA_SUPERVISOR: strcat(buf, " [SPV]"); break;
			case RMOA_ADMINISTRATOR: strcat(buf, " [ADM]"); break;
		};
		k = m_RMOList.AddString(buf);
		if (k!=LB_ERR)
			m_RMOList.SetItemData(k, ui32);
	};
}

void CRmoListDlg::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
int k = m_RMOList.GetCurSel();
	if (k==-1) return;
unsigned __int32 ui32;
	ui32 = m_RMOList.GetItemData(k);

TSNPData *TND = new TSNPData;

	(*TND) << RMCMD_GETUSERPROFILE << ui32;
	theApp.CACP.SendMessage(TND);
}

void CRmoListDlg::SetRmoProfile(TSNPData *TND)
{
	(*TND) >> RMOUID >> ComputerName >> Attr >> UIL >> RMLineNumber;
	m_ComputerName.SetWindowText(ComputerName.c_str());
	m_Category.SetCurSel((Attr&RMOA_CATEGORYMASK)>>16);
	m_USERCNG.SetCheck((Attr&RMOA_CANCHNGUSERPF)!=0);
	m_SRGPCNG.SetCheck((Attr&RMOA_CANCHNGSERGPF)!=0);
	m_COMMCNG.SetCheck((Attr&RMOA_CANCHNGCOMPRF)!=0);
	m_DIS.SetCheck((Attr&RMOA_DISABLE)!=0);
	m_LNumber.SetCurSel(RMLineNumber);
	m_SGList.ResetContent();
int i,j,k;
char buf[200];
	for (i=0; i<UIL.GetSize(); i++)
	{
		for (j=0; j<m_FSGList.GetCount(); j++)
		{
			if (m_FSGList.GetItemData(j)==UIL[i])
			{
				m_FSGList.GetText(j, buf);
				k = m_SGList.AddString(buf);
				m_SGList.SetItemData(k, UIL[i]);
				break;
			};
		};
		if (j<m_FSGList.GetCount()) continue;
		sprintf(buf, "[%d]", UIL[i]);
		k = m_SGList.AddString(buf);
		m_SGList.SetItemData(k, UIL[i]);
	};
	Update();
}

void CRmoListDlg::Update(void)
{
bool GROUP1, GROUP2, GROUP3;

	if (RMOUID==0)
	{
		GROUP1=false; GROUP2=false; GROUP3=false;
	}
	else
	{
		GROUP1=true;
		switch (Attr&RMOA_CATEGORYMASK)
		{
			case RMOA_OPERATOR:
				GROUP2=true;
				GROUP3=false;
				break;
			case RMOA_SUPERVISOR:
				GROUP2=false;
				GROUP3=false;
				break;
			case RMOA_ADMINISTRATOR:
				GROUP2=false;
				GROUP3=true;
				break;
		};
	};

	ST3.EnableWindow(GROUP1);
	ST2.EnableWindow(GROUP1);
	ST1.EnableWindow(GROUP1);
	m_Desc.EnableWindow(GROUP1);
	m_Category.EnableWindow(GROUP1);
	m_ComputerName.EnableWindow(GROUP1);
	m_DIS.EnableWindow(GROUP1);

	ST5.EnableWindow(GROUP2);
	ST4.EnableWindow(GROUP2);
	m_ChangeSGList.EnableWindow(GROUP2);
	m_SGList.EnableWindow(GROUP2);
	m_LNumber.EnableWindow(GROUP2);


	m_COMMCNG.EnableWindow(GROUP3);
	m_SRGPCNG.EnableWindow(GROUP3);
	m_USERCNG.EnableWindow(GROUP3);

	if (!GROUP2)
	{
		CRect rect;
		m_SGList.GetWindowRect(&rect);
		this->ScreenToClient(&rect);
		RedrawWindow(rect);
	};
}

void CRmoListDlg::OnSelchangeCombo1()
{
int k=m_Category.GetCurSel();
	if (k==-1) return;
	Attr = (Attr&~RMOA_CATEGORYMASK) | (k<<16);
	Update();
}

BOOL CRmoListDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
//	m_FSGList.ModifyStyle(0, WS_BORDER);
	Update();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRmoListDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (RMOUID==0 || ((Attr&RMOA_CATEGORYMASK)!=RMOA_OPERATOR))
	{
		CRect rect;
		CPaintDC dc2(&m_SGList);
		m_SGList.GetClientRect(&rect);
		dc2.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
	};
}

void CRmoListDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here

	RMOUID = 0xffffffff;
	ComputerName = "";
	Attr = 0;
	RMLineNumber = 0;
	UIL.Reset();
	m_ComputerName.SetWindowText(ComputerName.c_str());
	m_Category.SetCurSel((Attr&RMOA_CATEGORYMASK)>>16);
	m_USERCNG.SetCheck((Attr&RMOA_CANCHNGUSERPF)!=0);
	m_SRGPCNG.SetCheck((Attr&RMOA_CANCHNGSERGPF)!=0);
	m_COMMCNG.SetCheck((Attr&RMOA_CANCHNGCOMPRF)!=0);
	m_DIS.SetCheck((Attr&RMOA_DISABLE)!=0);
	m_LNumber.SetCurSel(RMLineNumber-1);
	Update();	
}

void CRmoListDlg::SetModifyKey()
{
//	SetModified(TRUE);
}

BOOL CRmoListDlg::OnApply() 
{
CString str;
	m_ComputerName.GetWindowText(str);
	ComputerName = (const char*)str;
	UIL.Reset();
unsigned __int32 k;
	for(int i=0; i<m_SGList.GetCount(); i++)
	{
		k = m_SGList.GetItemData(i);
		UIL.Add(k);
	};
	RMLineNumber = m_LNumber.GetCurSel();

	Attr = (m_Category.GetCurSel()&0x03)<<16;
	if (m_USERCNG.GetCheck()==1) Attr|=RMOA_CANCHNGUSERPF;
	if (m_SRGPCNG.GetCheck()==1) Attr|=RMOA_CANCHNGSERGPF;
	if (m_COMMCNG.GetCheck()==1) Attr|=RMOA_CANCHNGCOMPRF;
	if (m_DIS.GetCheck()==1) Attr|=RMOA_DISABLE;

	// TODO: Add your specialized code here and/or call the base class
TSNPData *TND = new TSNPData;

	(*TND) << RMCMD_SETUSERPROFILE << RMOUID << RMOUID << ComputerName << Attr << UIL << RMLineNumber;
	theApp.CACP.SendMessage(TND);
	
	return CPropertyPage::OnApply();
}

void CRmoListDlg::OnButton4() 
{
	m_FSGList.ShowWindow(SW_SHOW);
	m_FSGList.ModifyStyleEx(0, WS_EX_WINDOWEDGE);

}

void CRmoListDlg::OnDblclkList3() 
{
int k=m_FSGList.GetCurSel();
	if (k==-1) return;
unsigned SGUID = m_FSGList.GetItemData(k);
	for (int i=0; i<m_SGList.GetCount(); i++)
		if (m_SGList.GetItemData(i)==SGUID)
		{
			m_SGList.DeleteString(i);
			return;
		};
char buf[200];
	m_FSGList.GetText(k, buf);
	k = m_SGList.AddString(buf);
	m_SGList.SetItemData(k, SGUID);
}

void CRmoListDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	OnApply();
}

void CRmoListDlg::OnKillfocusList3() 
{
	// TODO: Add your control notification handler code here
	m_FSGList.ShowWindow(SW_HIDE);	
}
