; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServiceGroupDlg
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AdmCom.h"

ClassCount=5
Class1=CAdmComApp
Class2=CAdmComDlg

ResourceCount=6
Resource2=IDD_ADMCOM_DIALOG
Resource3=IDD_SERVICEGROUPSDLG
Resource1=IDR_MAINFRAME
Class3=CServiceGroupDlg
Resource4=IDD_RMOLISTDLG
Resource5=IDD_SLDLG
Class4=CRmoListDlg
Class5=CSLDLG
Resource6=IDD_ADMCOM_DIALOG (English (U.S.))

[CLS:CAdmComApp]
Type=0
HeaderFile=AdmCom.h
ImplementationFile=AdmCom.cpp
Filter=N

[CLS:CAdmComDlg]
Type=0
HeaderFile=AdmComDlg.h
ImplementationFile=AdmComDlg.cpp
Filter=D
LastObject=CAdmComDlg



[DLG:IDD_ADMCOM_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CAdmComDlg

[DLG:IDD_ADMCOM_DIALOG (English (U.S.))]
Type=1
Class=CAdmComDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_SERVICEGROUPSDLG]
Type=1
Class=CServiceGroupDlg
ControlCount=27
Control1=IDC_STATIC1,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_LIST1,listbox,1352728835
Control4=IDC_STATIC2,static,1342308352
Control5=IDC_EDIT2,edit,1350635716
Control6=IDC_COMBO1,combobox,1344339971
Control7=IDC_STATIC3,static,1342308352
Control8=IDC_STATIC,button,1342177287
Control9=IDC_LIST2,listbox,1352728835
Control10=IDC_STATIC4,static,1342308352
Control11=IDC_BUTTON2,button,1342242816
Control12=IDC_BUTTON3,button,1342242816
Control13=IDC_BUTTON4,button,1342242816
Control14=IDC_BUTTON5,button,1073807360
Control15=IDC_STATIC5,static,1342308352
Control16=IDC_COMBO3,combobox,1344339971
Control17=IDC_CHECK1,button,1342242819
Control18=IDC_CHECK2,button,1342242819
Control19=IDC_CHECK3,button,1342242819
Control20=IDC_STATIC6,static,1342308352
Control21=IDC_STATIC7,static,1342308352
Control22=IDC_SPIN1,msctls_updown32,1342177312
Control23=IDC_EDIT3,edit,1350631552
Control24=IDC_STATIC8,static,1342308352
Control25=IDC_SPIN2,msctls_updown32,1342177312
Control26=IDC_CALLQUEUECNT,edit,1350631552
Control27=IDC_STATIC9,static,1342308352

[CLS:CServiceGroupDlg]
Type=0
HeaderFile=ServiceGroupDlg.h
ImplementationFile=ServiceGroupDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT3
VirtualFilter=dWC

[DLG:IDD_RMOLISTDLG]
Type=1
Class=CRmoListDlg
ControlCount=21
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_LIST1,listbox,1352728835
Control3=IDC_STATIC1,static,1342308352
Control4=IDC_STATIC2,static,1342308352
Control5=IDC_EDIT2,edit,1350631556
Control6=IDC_COMBO1,combobox,1344339971
Control7=IDC_LIST2,listbox,1352728835
Control8=IDC_STATIC3,static,1342308352
Control9=IDC_STATIC4,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_CHECK1,button,1342242819
Control12=IDC_CHECK2,button,1342251011
Control13=IDC_CHECK3,button,1342251011
Control14=IDC_CHECK4,button,1342251011
Control15=IDC_BUTTON1,button,1342242816
Control16=IDC_BUTTON2,button,1342242816
Control17=IDC_BUTTON3,button,1342242816
Control18=IDC_BUTTON4,button,1342242816
Control19=IDC_STATIC5,static,1342308352
Control20=IDC_COMBO2,combobox,1344339971
Control21=IDC_LIST3,listbox,1084293377

[DLG:IDD_SLDLG]
Type=1
Class=CSLDLG
ControlCount=2
Control1=IDC_COMBO1,combobox,1075904515
Control2=IDC_EDIT1,edit,1082196096

[CLS:CRmoListDlg]
Type=0
HeaderFile=RmoListDlg.h
ImplementationFile=RmoListDlg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_LIST3
VirtualFilter=idWC

[CLS:CSLDLG]
Type=0
HeaderFile=SLDLG.h
ImplementationFile=SLDLG.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=idWC

