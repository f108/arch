; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFontEditor
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Editor.h"

ClassCount=9
Class1=CEditorApp
Class2=CEditorDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EDITOR_DIALOG
Resource4=IDD_FONTEDITOR
Resource5=IDD_DIALOG1
Class4=CBitmapView
Class5=CBannerView
Resource6=IDD_ABOUTBOX (English (U.S.))
Class6=CFontEditor
Resource7=IDD_ADDNEWFONT
Class7=CAddNewFontDlg
Class8=CMatrixView
Resource8=IDD_EDITOR_DIALOG (English (U.S.))
Class9=CSymbolEditor
Resource9=IDD_SMBEDITOR

[CLS:CEditorApp]
Type=0
HeaderFile=Editor.h
ImplementationFile=Editor.cpp
Filter=N

[CLS:CEditorDlg]
Type=0
HeaderFile=EditorDlg.h
ImplementationFile=EditorDlg.cpp
Filter=D
LastObject=CEditorDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=EditorDlg.h
ImplementationFile=EditorDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_EDITOR_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CEditorDlg

[DLG:IDD_EDITOR_DIALOG (English (U.S.))]
Type=1
Class=CEditorDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG1]
Type=1
Class=CBannerView
ControlCount=1
Control1=IDC_CUSTOM1,BitmapView,1342242816

[CLS:CBitmapView]
Type=0
HeaderFile=BitmapView.h
ImplementationFile=BitmapView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CBitmapView
VirtualFilter=VWC

[CLS:CBannerView]
Type=0
HeaderFile=BannerView.h
ImplementationFile=BannerView.cpp
BaseClass=CDialog
Filter=D
LastObject=CBannerView
VirtualFilter=dWC

[DLG:IDD_FONTEDITOR]
Type=1
Class=CFontEditor
ControlCount=7
Control1=IDC_COMBO1,combobox,1344340226
Control2=IDC_STATIC,static,1342308352
Control3=IDC_CUSTOM1,MatrixView,1342242816
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_EDIT1,edit,1342244992
Control7=IDC_BUTTON3,button,1342242816

[CLS:CFontEditor]
Type=0
HeaderFile=FontEditor.h
ImplementationFile=FontEditor.cpp
BaseClass=CDialog
Filter=D
LastObject=CFontEditor
VirtualFilter=dWC

[DLG:IDD_ADDNEWFONT]
Type=1
Class=CAddNewFontDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[CLS:CAddNewFontDlg]
Type=0
HeaderFile=AddNewFontDlg.h
ImplementationFile=AddNewFontDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CMatrixView]
Type=0
HeaderFile=MatrixView.h
ImplementationFile=MatrixView.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CMatrixView

[DLG:IDD_SMBEDITOR]
Type=1
Class=CSymbolEditor
ControlCount=3
Control1=IDC_CUSTOM1,MatrixView,1342242816
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_EDIT1,edit,1342244992

[CLS:CSymbolEditor]
Type=0
HeaderFile=SymbolEditor.h
ImplementationFile=SymbolEditor.cpp
BaseClass=CDialog
Filter=D
LastObject=CSymbolEditor
VirtualFilter=dWC

