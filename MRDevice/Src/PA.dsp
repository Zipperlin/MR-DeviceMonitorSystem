# Microsoft Developer Studio Project File - Name="PA" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PA - Win32 Unicode Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PA.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PA.mak" CFG="PA - Win32 Unicode Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PA - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "PA - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PA - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "..\..\include\ASBasis" /I "..\include" /I "..\..\include\Language" /I "..\..\include\Printing&Archiving" /I "..\..\include\Printing&Archiving\include" /I "..\..\Include\Printing&Archiving\include\NDicomUI20" /I "..\..\include\Printing&Archiving\include\dcmtk352" /I "..\..\include\DVDBurner" /D "_DEBUG" /D "_WIN32_DCOM" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD MTL /I "..\idl" /Oicf
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ASBasis.lib NDicomUI20d.lib dcmtk352mfc_d.lib DVDBurner.lib DcmProc.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt.lib" /out:"..\Bin/PrintingArchiving_ud.exe" /pdbtype:sept /libpath:"..\..\lib\ASBasis" /libpath:"..\lib" /libpath:"..\..\lib\Printing&Archiving" /libpath:"..\..\lib\DVDBurner"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
IntDir=.\Unicode_Debug
OutDir=.\..\Bin
TargetPath=\Workspace\N Series\SourceCode\Win 7\CronusDR\PrintingArchiving\Bin\PrintingArchiving_ud.exe
InputPath=\Workspace\N Series\SourceCode\Win 7\CronusDR\PrintingArchiving\Bin\PrintingArchiving_ud.exe
SOURCE="$(InputPath)"

"$(OutDir)\PA.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	if not errorlevel 0 goto ERROR 
	if errorlevel 1 goto ERROR 
	echo custom build step trigger > "$(IntDir)\PA.trg" 
	echo Generate Proxy-stub DLL 
	nmake -f PAps.mk 
	copy PAps.dll $(OutDir) 
	regsvr32 /s PAps.dll 
	goto END 
	:ERROR 
	echo Server Registration Failed 
	:END 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "PA - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "PA___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "PA___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\include\ASBasis" /I "..\include" /I "..\include\dcmtk352" /I "..\include\NDicomUI20" /D "_DEBUG" /D "_WIN32_DCOM" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /I "..\include" /I "..\..\include\ASBasis" /I "..\..\include\UserGuidanceRes" /I "..\..\include\DcmProc" /I "..\..\include\PrintingArchiving" /I "..\..\Include\NFC\include" /I "..\..\include\NFC\include\NDicomUI20" /I "..\..\include\NFC\include\dcmtk352" /I "..\..\include\DVDBurner" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /D "_WIN32_DCOM" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /I "..\idl" /Oicf
# ADD MTL /I "..\idl" /Oicf
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /fo"Unicode_Release/PrintingArchiving.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ASBasis.lib NDicomUI20d.lib dcmtk352mfc_d.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /map /debug /machine:I386 /out:"..\Bin/PA_ud.exe" /pdbtype:sept /libpath:"..\..\lib\ASBasis" /libpath:"..\lib" /libpath:"..\bin"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ASBasis.lib DVDBurner.lib DcmProc.lib ws2_32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /map:"..\bin/PrintingArchiving_ur.map" /debug /machine:I386 /out:"..\Bin/PrintingArchiving_ur.exe" /pdbtype:sept /libpath:"..\..\Lib\DcmProc" /libpath:"..\..\lib\ASBasis" /libpath:"..\lib" /libpath:"..\..\lib\Printing&Archiving" /libpath:"..\..\lib\DVDBurner"
# SUBTRACT LINK32 /pdb:none /incremental:no
# Begin Custom Build - Performing registration
IntDir=.\Unicode_Release
OutDir=.\..\bin
TargetPath=\Workspace\N Series\SourceCode\Win 7\CronusDR\PrintingArchiving\Bin\PrintingArchiving_ur.exe
InputPath=\Workspace\N Series\SourceCode\Win 7\CronusDR\PrintingArchiving\Bin\PrintingArchiving_ur.exe
SOURCE="$(InputPath)"

"$(OutDir)\PrintingArchiving_ur.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	if not errorlevel 0 goto ERROR 
	if errorlevel 1 goto ERROR 
	echo custom build step trigger > "$(IntDir)\PA.trg" 
	echo Generate Proxy-stub DLL 
	nmake -f PAps.mk 
	copy PAps.dll $(OutDir) 
	regsvr32 /s PAps.dll 
	goto END 
	:ERROR 
	echo Server Registration Failed 
	:END 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "PA - Win32 Unicode Debug"
# Name "PA - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ado.cpp
# End Source File
# Begin Source File

SOURCE=.\BSTROpt.cpp
# End Source File
# Begin Source File

SOURCE=.\Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Burner.cpp
# End Source File
# Begin Source File

SOURCE=.\DBController.cpp
# End Source File
# Begin Source File

SOURCE=.\DBDatabaseBasisOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\DBDatabaseOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\DBSink.cpp
# End Source File
# Begin Source File

SOURCE=.\DBStructInitor.cpp
# End Source File
# Begin Source File

SOURCE=.\DcmPartner.cpp
# End Source File
# Begin Source File

SOURCE=.\DirHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscImport.cpp
# End Source File
# Begin Source File

SOURCE=.\FCPartner.cpp
# End Source File
# Begin Source File

SOURCE=.\FilePicker.cpp
# End Source File
# Begin Source File

SOURCE=.\FireMsgQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\FireMsgQueueMng.cpp
# End Source File
# Begin Source File

SOURCE=.\IDPathGen.cpp
# End Source File
# Begin Source File

SOURCE=.\IniOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\ISController.cpp
# End Source File
# Begin Source File

SOURCE=.\JobHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\JobQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\LanguageIniOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\MPPSIniOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\PA.cpp
# End Source File
# Begin Source File

SOURCE=.\PA.rc
# End Source File
# Begin Source File

SOURCE=.\PAATL.cpp
# End Source File
# Begin Source File

SOURCE=.\PADataBaseOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\PAEvent.h
# End Source File
# Begin Source File

SOURCE=.\PAJob.cpp
# End Source File
# Begin Source File

SOURCE=.\PQSink.cpp
# End Source File
# Begin Source File

SOURCE=.\Printing.cpp
# End Source File
# Begin Source File

SOURCE=.\SpaceEstimator.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemEventProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemEventProxy.h
# End Source File
# Begin Source File

SOURCE=.\Transfer.cpp
# End Source File
# Begin Source File

SOURCE=.\TransferXMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\UserGuidanceOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\WlMpps.cpp
# End Source File
# Begin Source File

SOURCE=.\WorklistIniOpt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ado.h
# End Source File
# Begin Source File

SOURCE=.\BSTROpt.h
# End Source File
# Begin Source File

SOURCE=.\Buffer.h
# End Source File
# Begin Source File

SOURCE=.\Burner.h
# End Source File
# Begin Source File

SOURCE=.\DBController.h
# End Source File
# Begin Source File

SOURCE=.\DBDatabaseBasisOpt.h
# End Source File
# Begin Source File

SOURCE=.\DBDatabaseOpt.h
# End Source File
# Begin Source File

SOURCE=.\DBSink.h
# End Source File
# Begin Source File

SOURCE=.\DBStructInitor.h
# End Source File
# Begin Source File

SOURCE=.\DcmPartner.h
# End Source File
# Begin Source File

SOURCE=.\DirHandler.h
# End Source File
# Begin Source File

SOURCE=.\DiscImport.h
# End Source File
# Begin Source File

SOURCE=.\FCPartner.h
# End Source File
# Begin Source File

SOURCE=.\FilePicker.h
# End Source File
# Begin Source File

SOURCE=.\FireMsgQueue.h
# End Source File
# Begin Source File

SOURCE=.\FireMsgQueueMng.h
# End Source File
# Begin Source File

SOURCE=.\IDPathGen.h
# End Source File
# Begin Source File

SOURCE=.\IniOpt.h
# End Source File
# Begin Source File

SOURCE=.\ISController.h
# End Source File
# Begin Source File

SOURCE=.\JobHandler.h
# End Source File
# Begin Source File

SOURCE=.\JobQueue.h
# End Source File
# Begin Source File

SOURCE=.\LanguageIniOpt.h
# End Source File
# Begin Source File

SOURCE=.\MPPSIniOpt.h
# End Source File
# Begin Source File

SOURCE=.\PAATL.h
# End Source File
# Begin Source File

SOURCE=.\PADataBaseOpt.h
# End Source File
# Begin Source File

SOURCE=.\PAJob.h
# End Source File
# Begin Source File

SOURCE=.\PALibConnectionPoint.h
# End Source File
# Begin Source File

SOURCE=.\PQSink.h
# End Source File
# Begin Source File

SOURCE=.\Printing.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SpaceEstimator.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Transfer.h
# End Source File
# Begin Source File

SOURCE=.\TransferXMLParser.h
# End Source File
# Begin Source File

SOURCE=.\UserGuidanceOpt.h
# End Source File
# Begin Source File

SOURCE=.\WlMpps.h
# End Source File
# Begin Source File

SOURCE=.\WorklistIniOpt.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\PA.rgs
# End Source File
# End Group
# Begin Group "IDL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\idl\PALib.idl

!IF  "$(CFG)" == "PA - Win32 Unicode Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=..\idl\PALib.idl

BuildCmds= \
	del dlldata.c \
	midl /env win32 /Oicf /pack 8 /I "..\idl" /I "..\..\IDL\DB" /I "..\..\IDL\ASBasis" /h "PALib_i.h" /iid "PALib_i.c" "PALib.idl" \
	

".\PALib_i.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PALib_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "PA - Win32 Unicode Release"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=..\idl\PALib.idl

BuildCmds= \
	del dlldata.c \
	midl /env win32 /Oicf /pack 8 /I "..\idl" /I "..\..\IDL\DB" /I "..\..\IDL\ASBasis" /h "PALib_i.h" /iid "PALib_i.c" "PALib.idl" \
	

".\PALib_i.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PALib_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\idl\PALibExt.idl

!IF  "$(CFG)" == "PA - Win32 Unicode Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=..\idl\PALibExt.idl

BuildCmds= \
	del temp.c \
	midl /env win32 /Oicf /pack 8 /dlldata temp.c   /I  "..\..\IDL\DB" /I  "..\..\idl\db"  /I "..\idl" /I " ..\..\IDL\ASBasis" /h "PALibExt_i.h" /iid "PALibExt_i.c" "PALibExt.idl" \
	

".\PALibExt_i.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PALibExt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "PA - Win32 Unicode Release"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=..\idl\PALibExt.idl

BuildCmds= \
	del temp.c \
	midl /env win32 /Oicf /pack 8 /dlldata temp.c   /I  "..\..\IDL\DB" /I  "..\..\IDL\IS" /I  "..\..\IDL\Acq"  /I "..\idl" /I " ..\..\IDL\ASBasis" /I  "..\..\IDL\SystemEventDB" /h "PALibExt_i.h" /iid "PALibExt_i.c" "PALibExt.idl" \
	

".\PALibExt_i.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PALibExt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\IDL\PrintQueueManager.idl

!IF  "$(CFG)" == "PA - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "PA - Win32 Unicode Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=..\IDL\PrintQueueManager.idl

BuildCmds= \
	del PrintQueueManager.c \
	midl /env win32 /Oicf /pack 8 /dlldata PrintQueueManager.c   /I "..\idl" /h "PrintQueueManager_i.h" /iid "PrintQueueManager_i.c" "PrintQueueManager.idl" \
	

".\PrintQueueManager_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PrintQueueManager_i.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
