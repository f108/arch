# Microsoft Developer Studio Project File - Name="AdmCom" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AdmCom - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AdmCom.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AdmCom.mak" CFG="AdmCom - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AdmCom - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AdmCom - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AdmCom - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "AdmCom - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AdmCom - Win32 Release"
# Name "AdmCom - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdmClientPipe.cpp
# End Source File
# Begin Source File

SOURCE=.\AdmCom.cpp
# End Source File
# Begin Source File

SOURCE=.\AdmCom.rc
# End Source File
# Begin Source File

SOURCE=.\AdmComDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RmoListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SLDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AdmClientPipe.h
# End Source File
# Begin Source File

SOURCE=.\AdmCom.h
# End Source File
# Begin Source File

SOURCE=.\AdmComDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RmoListDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServiceGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\SLDLG.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AdmCom.ico
# End Source File
# Begin Source File

SOURCE=.\res\AdmCom.rc2
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# End Group
# Begin Group "ClientHelpers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\TestClientPipe\ClientNamedPipe.cpp
# End Source File
# Begin Source File

SOURCE=..\TestClientPipe\ClientNamedPipe.h
# End Source File
# End Group
# Begin Group "Helpers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SRVCOMDEFINES.h
# End Source File
# Begin Source File

SOURCE=..\TBinaryData.cpp
# End Source File
# Begin Source File

SOURCE=..\TFixedSizeBinaryData.hxx
# End Source File
# Begin Source File

SOURCE=..\Thread.cpp
# End Source File
# Begin Source File

SOURCE=..\Thread.h
# End Source File
# Begin Source File

SOURCE=..\TUIList.cpp
# End Source File
# Begin Source File

SOURCE=..\TUIList.h
# End Source File
# Begin Source File

SOURCE=..\TZSSString.cpp
# End Source File
# Begin Source File

SOURCE=..\TZSSString.h
# End Source File
# Begin Source File

SOURCE=..\WSDEFINES.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
