# Microsoft Developer Studio Project File - Name="wavfrag" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wavfrag - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wavfrag.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wavfrag.mak" CFG="wavfrag - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wavfrag - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "wavfrag - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wavfrag - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/work" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wflib.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../common/work" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wflibd.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "wavfrag - Win32 Release"
# Name "wavfrag - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3DDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\3DDlg.h
# End Source File
# Begin Source File

SOURCE=.\3DPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\3DPlot.h
# End Source File
# Begin Source File

SOURCE=.\4D.cpp
# End Source File
# Begin Source File

SOURCE=.\4D.h
# End Source File
# Begin Source File

SOURCE=.\4DDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\4DDlg.h
# End Source File
# Begin Source File

SOURCE=.\ActionTab.cpp
# End Source File
# Begin Source File

SOURCE=.\ComColl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComConf.cpp
# End Source File
# Begin Source File

SOURCE=.\Command.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\dsp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\FileDialogST.cpp
# End Source File
# Begin Source File

SOURCE=.\Focus.cpp
# End Source File
# Begin Source File

SOURCE=.\FragCollTab.cpp
# End Source File
# Begin Source File

SOURCE=.\FragTab.cpp
# End Source File
# Begin Source File

SOURCE=.\gettext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\GrayDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\IntArr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\label.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\Led.cpp
# End Source File
# Begin Source File

SOURCE=.\LightBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LightBoxDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\LogWin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\memdc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\Mixer.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\multimon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\mxpad.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\PersistDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\PersistInt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\PersistStr.cpp
# End Source File
# Begin Source File

SOURCE=.\Phonames.cpp
# End Source File
# Begin Source File

SOURCE=.\PickDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\PlaySound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\Plot.cpp
# End Source File
# Begin Source File

SOURCE=.\PlotDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\Popup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\RecordSound.cpp
# End Source File
# Begin Source File

SOURCE=.\SelList.cpp
# End Source File
# Begin Source File

SOURCE=.\SendKeys.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowPic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\SimpleGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\Status.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\common\work\Support.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\TextMode.cpp
# End Source File
# Begin Source File

SOURCE=.\transprog.cpp
# End Source File
# Begin Source File

SOURCE=.\UserTab.cpp
# End Source File
# Begin Source File

SOURCE=.\Vis.cpp
# End Source File
# Begin Source File

SOURCE=.\VisDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WavCmp.cpp
# End Source File
# Begin Source File

SOURCE=.\WavDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\waveEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\wavfrag.cpp
# End Source File
# Begin Source File

SOURCE=.\wavfragDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\xButton.cpp
# End Source File
# Begin Source File

SOURCE=.\xProgCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\xPtrArr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\XrayM.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\work\xRect.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ActionTab.h
# End Source File
# Begin Source File

SOURCE=.\ComColl.h
# End Source File
# Begin Source File

SOURCE=.\ComConf.h
# End Source File
# Begin Source File

SOURCE=.\Command.h
# End Source File
# Begin Source File

SOURCE=.\DicRec.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\dsp.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\FileDialogST.h
# End Source File
# Begin Source File

SOURCE=.\Focus.h
# End Source File
# Begin Source File

SOURCE=.\FragCollTab.h
# End Source File
# Begin Source File

SOURCE=.\FragTab.h
# End Source File
# Begin Source File

SOURCE=.\gettext.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\GrayDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\intarr.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\label.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\Led.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\LogWin.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\memdc.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\misc.h
# End Source File
# Begin Source File

SOURCE=.\Mixer.h
# End Source File
# Begin Source File

SOURCE=.\MsgBox.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\multimon.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\mxpad.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\PersistDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\PersistInt.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\PersistStr.h
# End Source File
# Begin Source File

SOURCE=.\Phonames.h
# End Source File
# Begin Source File

SOURCE=.\PickDlg.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\PlaySound.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\Plot.h
# End Source File
# Begin Source File

SOURCE=.\PlotDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\Popup.h
# End Source File
# Begin Source File

SOURCE=.\Recog.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\RecordSound.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\sellist.h
# End Source File
# Begin Source File

SOURCE=.\SendKeys.h
# End Source File
# Begin Source File

SOURCE=.\ShowPic.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\SimpleGrid.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\soundpar.h
# End Source File
# Begin Source File

SOURCE=.\Status.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\Support.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\TextMode.h
# End Source File
# Begin Source File

SOURCE=.\transprog.h
# End Source File
# Begin Source File

SOURCE=.\UserTab.h
# End Source File
# Begin Source File

SOURCE=.\Vis.h
# End Source File
# Begin Source File

SOURCE=.\VisDlg.h
# End Source File
# Begin Source File

SOURCE=.\WavCmp.h
# End Source File
# Begin Source File

SOURCE=.\WavDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\waveEdit.h
# End Source File
# Begin Source File

SOURCE=.\wavfrag.h
# End Source File
# Begin Source File

SOURCE=.\wavfragDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\xButton.h
# End Source File
# Begin Source File

SOURCE=.\xProgCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\xPtrArr.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\XrayM.h
# End Source File
# Begin Source File

SOURCE=..\..\common\work\xRect.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\mic.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wavfrag.ico
# End Source File
# Begin Source File

SOURCE=.\wavfrag.rc
# End Source File
# Begin Source File

SOURCE=.\res\wavfrag.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section wavfrag : {1C281913-E868-4055-A617-33C6DCE6C7AA}
# 	2:11:transprog.h:transprog.h
# 	2:17:CLASS: CTransProg:CTransProg
# 	2:13:transprog.cpp:transprog.cpp
# 	2:19:Application Include:wavfrag.h
# End Section
# Section wavfrag : {2DD8112B-030D-442E-819D-06746B1CFB6F}
# 	1:11:IDD_DIALOG9:108
# 	2:16:Resource Include:resource.h
# 	2:11:IDD_DIALOG9:IDD_DIALOG9
# 	2:10:Status.cpp:Status.cpp
# 	2:10:ENUM: enum:enum
# 	2:14:CLASS: CStatus:CStatus
# 	2:19:Application Include:wavfrag.h
# 	2:8:Status.h:Status.h
# End Section
# Section wavfrag : {8C599843-70B3-409F-83DE-C376D7261AD0}
# 	1:11:IDD_DIALOG2:104
# 	2:16:Resource Include:resource.h
# 	2:14:CLASS: PlotDlg:PlotDlg
# 	2:11:PlotDlg.cpp:PlotDlg.cpp
# 	2:9:PlotDlg.h:PlotDlg.h
# 	2:10:ENUM: enum:enum
# 	2:11:IDD_DIALOG2:IDD_DIALOG2
# 	2:19:Application Include:wavfrag.h
# End Section
# Section wavfrag : {293635F9-516C-4EE7-BAA9-F5ED385FDD03}
# 	1:11:IDD_DIALOG6:110
# 	2:16:Resource Include:resource.h
# 	2:9:PickDlg.h:PickDlg.h
# 	2:10:ENUM: enum:enum
# 	2:15:CLASS: CPickDlg:CPickDlg
# 	2:11:PickDlg.cpp:PickDlg.cpp
# 	2:19:Application Include:wavfrag.h
# 	2:11:IDD_DIALOG6:IDD_DIALOG6
# End Section
# Section wavfrag : {DDCCE12A-3617-4ADE-BFC6-26E515442951}
# 	2:10:WavCmp.cpp:WavCmp.cpp
# 	2:14:CLASS: CWavCmp:CWavCmp
# 	2:8:WavCmp.h:WavCmp.h
# 	2:19:Application Include:wavfrag.h
# End Section
# Section wavfrag : {1411B949-1161-4D98-AACC-AE53100759B2}
# 	1:8:IDD_MBOX:109
# 	2:16:Resource Include:resource.h
# 	2:8:MsgBox.h:MsgBox.h
# 	2:14:CLASS: CMsgBox:CMsgBox
# 	2:8:IDD_MBOX:IDD_MBOX
# 	2:10:MsgBox.cpp:MsgBox.cpp
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:wavfrag.h
# End Section
# Section wavfrag : {2633AA80-C056-4B78-9709-59265AFC7166}
# 	2:5:Fft.h:Fft1.h
# 	2:16:TYPEDEF: Complex:Complex
# 	2:7:Fft.cpp:Fft1.cpp
# 	2:19:Application Include:wavfrag.h
# 	2:11:CLASS: CFft:CFft
# End Section
# Section wavfrag : {6A6D725C-F36F-4A25-8BBA-F9B79D9E98E1}
# 	2:10:DicRec.cpp:DicRec.cpp
# 	2:14:CLASS: CDicRec:CDicRec
# 	2:19:Application Include:wavfrag.h
# 	2:8:DicRec.h:DicRec.h
# End Section
# Section wavfrag : {D2975035-AC35-4B05-9882-F21B9D1898DE}
# 	2:11:FftBuff.cpp:FftBuff1.cpp
# 	2:9:FftBuff.h:FftBuff1.h
# 	2:15:CLASS: CFftBuff:CFftBuff
# 	2:19:Application Include:wavfrag.h
# End Section
# Section wavfrag : {9E014C5D-B5A9-4902-9448-5ED0790E1D22}
# 	2:5:Vis.h:Vis.h
# 	2:7:Vis.cpp:Vis.cpp
# 	2:11:CLASS: CVis:CVis
# 	2:19:Application Include:wavfrag.h
# End Section
# Section wavfrag : {0DBED2B8-6202-438E-A2F6-9B709CD27A97}
# 	2:11:xProgCtrl.h:xProgCtrl.h
# 	2:17:CLASS: CxProgCtrl:CxProgCtrl
# 	2:19:Application Include:wavfrag.h
# 	2:13:xProgCtrl.cpp:xProgCtrl.cpp
# End Section
# Section wavfrag : {E67C1789-50E3-4048-94CC-0B7DA6E5B7AA}
# 	1:11:IDD_DIALOG3:105
# 	2:16:Resource Include:resource.h
# 	2:8:VisDlg.h:VisDlg.h
# 	2:10:ENUM: enum:enum
# 	2:10:VisDlg.cpp:VisDlg.cpp
# 	2:11:IDD_DIALOG3:IDD_DIALOG3
# 	2:14:CLASS: CVisDlg:CVisDlg
# 	2:19:Application Include:wavfrag.h
# End Section
