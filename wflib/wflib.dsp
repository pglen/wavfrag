# Microsoft Developer Studio Project File - Name="wflib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=wflib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wflib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wflib.mak" CFG="wflib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wflib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wflib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wflib - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../common/work" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\wflib.dll  ..\Release	copy Release\wflib.lib ..
# End Special Build Tool

!ELSEIF  "$(CFG)" == "wflib - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../common/work" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\wflib.dll  ..\Debug	copy Debug\wflib.lib  ..\wflibd.lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "wflib - Win32 Release"
# Name "wflib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AnalProc.cpp
# End Source File
# Begin Source File

SOURCE=.\AnalRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrIntArr.cpp
# End Source File
# Begin Source File

SOURCE=.\CmpRes.cpp
# End Source File
# Begin Source File

SOURCE=.\Contain.cpp
# End Source File
# Begin Source File

SOURCE=.\ContainArr.cpp
# End Source File
# Begin Source File

SOURCE=.\ContColl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\dsp.cpp
# End Source File
# Begin Source File

SOURCE=.\Fft.cpp
# End Source File
# Begin Source File

SOURCE=.\FftBuff.cpp
# End Source File
# Begin Source File

SOURCE=.\Frag.cpp

!IF  "$(CFG)" == "wflib - Win32 Release"

!ELSEIF  "$(CFG)" == "wflib - Win32 Debug"

# ADD CPP /FAs

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FragColl.cpp
# End Source File
# Begin Source File

SOURCE=.\FragCollArr.cpp
# End Source File
# Begin Source File

SOURCE=.\FragUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\IntArr.cpp
# End Source File
# Begin Source File

SOURCE=.\IntArrRec.cpp
# End Source File
# Begin Source File

SOURCE=.\LevenStein.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\mxpad.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\RecordSound.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StrDiff.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\Support.cpp
# End Source File
# Begin Source File

SOURCE=.\wflib.cpp
# End Source File
# Begin Source File

SOURCE=.\wflib.def
# End Source File
# Begin Source File

SOURCE=.\xRecog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AnalProc.h
# End Source File
# Begin Source File

SOURCE=.\AnalRes.h
# End Source File
# Begin Source File

SOURCE=.\ArrIntArr.h
# End Source File
# Begin Source File

SOURCE=.\CmpRes.h
# End Source File
# Begin Source File

SOURCE=.\Contain.h
# End Source File
# Begin Source File

SOURCE=.\ContainArr.h
# End Source File
# Begin Source File

SOURCE=.\ContColl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\dsp.h
# End Source File
# Begin Source File

SOURCE=.\Fft.h
# End Source File
# Begin Source File

SOURCE=.\FftBuff.h
# End Source File
# Begin Source File

SOURCE=.\Frag.h
# End Source File
# Begin Source File

SOURCE=.\FragColl.h
# End Source File
# Begin Source File

SOURCE=.\FragCollArr.h
# End Source File
# Begin Source File

SOURCE=.\FragUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\intarr.h
# End Source File
# Begin Source File

SOURCE=.\IntArrRec.h
# End Source File
# Begin Source File

SOURCE=.\LevenStein.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\mxpad.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\RecordSound.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StrDiff.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\work\Support.h
# End Source File
# Begin Source File

SOURCE=.\wflib.h
# End Source File
# Begin Source File

SOURCE=.\xRecog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\wflib.rc
# End Source File
# Begin Source File

SOURCE=.\res\wflib.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section wflib : {4B9DFD79-C792-492B-A27D-BB3D284B4E76}
# 	2:17:CLASS: LevenStein:LevenStein
# 	2:14:LevenStein.cpp:LevenStein.cpp
# 	2:12:LevenStein.h:LevenStein.h
# 	2:15:CLASS: Distance:Distance
# 	2:19:Application Include:wflib.h
# End Section
# Section wflib : {E29D761F-3530-4FC7-AC2F-4427CD4B5398}
# 	2:12:FreqScan.cpp:FreqScan.cpp
# 	2:16:CLASS: CFreqScan:CFreqScan
# 	2:10:FreqScan.h:FreqScan.h
# 	2:19:Application Include:wflib.h
# End Section
