# Microsoft Developer Studio Project File - Name="TestClientSrc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestClientSrc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestClientSrc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestClientSrc.mak" CFG="TestClientSrc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestClientSrc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestClientSrc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestClientSrc - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\TestClientBin"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\src" /I "..\include" /I "..\..\Include\DcmProc" /I "..\..\Include\NFC\include" /I "..\..\include\NFC\include\NDicomUI20" /I "..\..\include\NFC\include\dcmtk352" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib DcmProc.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /debug /machine:I386 /nodefaultlib:"libcmt.lib" /out:"..\TestClientBin/PATestClient.exe" /libpath:"..\lib" /libpath:"..\..\lib\DcmProc"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy "..\TestClientbin\PATestClient.exe" "..\bin"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TestClientSrc - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\TestClientBin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "..\src" /I "..\include" /I "..\..\Include\NFC\include" /I "..\..\include\NFC\include\NDicomUI20" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt.lib" /out:"..\TestClientBin/PATestClient.exe" /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "TestClientSrc - Win32 Release"
# Name "TestClientSrc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BSTROpt.cpp
# End Source File
# Begin Source File

SOURCE=.\BurnDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BurnJobDetailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BurnPatientInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DcmReadDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportJobDetailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PAGeneralDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PASink.cpp
# End Source File
# Begin Source File

SOURCE=.\PatientAdminDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SendJobDetailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesImagesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestClientSrc.cpp
# End Source File
# Begin Source File

SOURCE=.\TestClientSrc.rc
# End Source File
# Begin Source File

SOURCE=.\TestClientSrcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TransferDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WlMppsDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BSTROpt.h
# End Source File
# Begin Source File

SOURCE=.\BurnDlg.h
# End Source File
# Begin Source File

SOURCE=.\BurnJobDetailDlg.h
# End Source File
# Begin Source File

SOURCE=.\BurnPatientInfo.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\DcmReadDlg.h
# End Source File
# Begin Source File

SOURCE=.\DiscImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImageDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImportJobDetailDlg.h
# End Source File
# Begin Source File

SOURCE=.\PAGeneralDlg.h
# End Source File
# Begin Source File

SOURCE=.\PASink.h
# End Source File
# Begin Source File

SOURCE=.\PatientAdminDlg.h
# End Source File
# Begin Source File

SOURCE=.\PrintDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReportCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SendJobDetailDlg.h
# End Source File
# Begin Source File

SOURCE=.\SeriesImagesDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServerDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestClientSrc.h
# End Source File
# Begin Source File

SOURCE=.\TestClientSrcDlg.h
# End Source File
# Begin Source File

SOURCE=.\TransferDlg.h
# End Source File
# Begin Source File

SOURCE=.\WlMppsDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_u.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CheckBoxIcon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Desktop.ico
# End Source File
# Begin Source File

SOURCE=.\res\Desktop_13.bmp
# End Source File
# Begin Source File

SOURCE=".\res\FauxS-36.ico"
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_top.ico
# End Source File
# Begin Source File

SOURCE=.\res\Project2.ico
# End Source File
# Begin Source File

SOURCE=.\res\reg.ico
# End Source File
# Begin Source File

SOURCE=.\res\SDPA.ico
# End Source File
# Begin Source File

SOURCE=.\res\SDPA_13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TestClientSrc.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestClientSrc.rc2
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UnSDPA.ico
# End Source File
# Begin Source File

SOURCE=.\res\UnSDPA_13.bmp
# End Source File
# End Group
# Begin Group "IDL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PATestClientExt.idl

!IF  "$(CFG)" == "TestClientSrc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PATestClientExt.idl

"^_^" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del temp.c 
	midl /env win32 /Oicf /pack 8 /dlldata temp.c   /I "..\..\IDL\DB" /I "..\..\IDL\IS" /I "..\..\IDL\Printing&Archiving" /I "..\idl" /I " ..\..\IDL\ASBasis" /h "PATestClientLibExt_i.h" /iid "PATestClientLibExt_i.c" "PATestClientExt.idl" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TestClientSrc - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
