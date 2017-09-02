# Microsoft Developer Studio Generated NMAKE File, Based on wavfrag.dsp
!IF "$(CFG)" == ""
CFG=wavfrag - Win32 Debug
!MESSAGE No configuration specified. Defaulting to wavfrag - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "wavfrag - Win32 Release" && "$(CFG)" != "wavfrag - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "wavfrag - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\wavfrag.exe"


CLEAN :
	-@erase "$(INTDIR)\ComColl.obj"
	-@erase "$(INTDIR)\ComConf.obj"
	-@erase "$(INTDIR)\Command.obj"
	-@erase "$(INTDIR)\dsp.obj"
	-@erase "$(INTDIR)\FileDialogST.obj"
	-@erase "$(INTDIR)\FreqScan.obj"
	-@erase "$(INTDIR)\GetText.obj"
	-@erase "$(INTDIR)\GrayDlg.obj"
	-@erase "$(INTDIR)\IntArr.obj"
	-@erase "$(INTDIR)\label.obj"
	-@erase "$(INTDIR)\Led.obj"
	-@erase "$(INTDIR)\LightBoxDlg.obj"
	-@erase "$(INTDIR)\LogWin.obj"
	-@erase "$(INTDIR)\memdc.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\Mixer.obj"
	-@erase "$(INTDIR)\MsgBox.obj"
	-@erase "$(INTDIR)\mxpad.obj"
	-@erase "$(INTDIR)\PersistDlg.obj"
	-@erase "$(INTDIR)\PersistInt.obj"
	-@erase "$(INTDIR)\PersistStr.obj"
	-@erase "$(INTDIR)\Picture.obj"
	-@erase "$(INTDIR)\PlaySound.obj"
	-@erase "$(INTDIR)\Plot.obj"
	-@erase "$(INTDIR)\PlotDlg.obj"
	-@erase "$(INTDIR)\Popup.obj"
	-@erase "$(INTDIR)\RecordSound.obj"
	-@erase "$(INTDIR)\SendKeys.obj"
	-@erase "$(INTDIR)\ShowPic.obj"
	-@erase "$(INTDIR)\SimpleGrid.obj"
	-@erase "$(INTDIR)\Status.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Support.obj"
	-@erase "$(INTDIR)\TextMode.obj"
	-@erase "$(INTDIR)\transprog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vis.obj"
	-@erase "$(INTDIR)\VisDlg.obj"
	-@erase "$(INTDIR)\waveEdit.obj"
	-@erase "$(INTDIR)\wavfrag.obj"
	-@erase "$(INTDIR)\wavfrag.pch"
	-@erase "$(INTDIR)\wavfrag.res"
	-@erase "$(INTDIR)\wavfragDlg.obj"
	-@erase "$(INTDIR)\xButton.obj"
	-@erase "$(INTDIR)\xProgCtrl.obj"
	-@erase "$(INTDIR)\xPtrArr.obj"
	-@erase "$(INTDIR)\XrayM.obj"
	-@erase "$(INTDIR)\xRect.obj"
	-@erase "$(OUTDIR)\wavfrag.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../common/work" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\wavfrag.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wavfrag.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wavfrag.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wflib.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\wavfrag.pdb" /machine:I386 /out:"$(OUTDIR)\wavfrag.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ComColl.obj" \
	"$(INTDIR)\ComConf.obj" \
	"$(INTDIR)\Command.obj" \
	"$(INTDIR)\dsp.obj" \
	"$(INTDIR)\FileDialogST.obj" \
	"$(INTDIR)\FreqScan.obj" \
	"$(INTDIR)\GetText.obj" \
	"$(INTDIR)\GrayDlg.obj" \
	"$(INTDIR)\IntArr.obj" \
	"$(INTDIR)\label.obj" \
	"$(INTDIR)\Led.obj" \
	"$(INTDIR)\LightBoxDlg.obj" \
	"$(INTDIR)\LogWin.obj" \
	"$(INTDIR)\memdc.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\Mixer.obj" \
	"$(INTDIR)\MsgBox.obj" \
	"$(INTDIR)\mxpad.obj" \
	"$(INTDIR)\PersistDlg.obj" \
	"$(INTDIR)\PersistInt.obj" \
	"$(INTDIR)\PersistStr.obj" \
	"$(INTDIR)\Picture.obj" \
	"$(INTDIR)\PlaySound.obj" \
	"$(INTDIR)\Plot.obj" \
	"$(INTDIR)\PlotDlg.obj" \
	"$(INTDIR)\Popup.obj" \
	"$(INTDIR)\RecordSound.obj" \
	"$(INTDIR)\SendKeys.obj" \
	"$(INTDIR)\ShowPic.obj" \
	"$(INTDIR)\SimpleGrid.obj" \
	"$(INTDIR)\Status.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Support.obj" \
	"$(INTDIR)\TextMode.obj" \
	"$(INTDIR)\transprog.obj" \
	"$(INTDIR)\Vis.obj" \
	"$(INTDIR)\VisDlg.obj" \
	"$(INTDIR)\waveEdit.obj" \
	"$(INTDIR)\wavfrag.obj" \
	"$(INTDIR)\wavfragDlg.obj" \
	"$(INTDIR)\xButton.obj" \
	"$(INTDIR)\xProgCtrl.obj" \
	"$(INTDIR)\xPtrArr.obj" \
	"$(INTDIR)\XrayM.obj" \
	"$(INTDIR)\xRect.obj" \
	"$(INTDIR)\wavfrag.res"

"$(OUTDIR)\wavfrag.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\wavfrag.exe" "$(OUTDIR)\wavfrag.bsc"


CLEAN :
	-@erase "$(INTDIR)\ComColl.obj"
	-@erase "$(INTDIR)\ComColl.sbr"
	-@erase "$(INTDIR)\ComConf.obj"
	-@erase "$(INTDIR)\ComConf.sbr"
	-@erase "$(INTDIR)\Command.obj"
	-@erase "$(INTDIR)\Command.sbr"
	-@erase "$(INTDIR)\dsp.obj"
	-@erase "$(INTDIR)\dsp.sbr"
	-@erase "$(INTDIR)\FileDialogST.obj"
	-@erase "$(INTDIR)\FileDialogST.sbr"
	-@erase "$(INTDIR)\FreqScan.obj"
	-@erase "$(INTDIR)\FreqScan.sbr"
	-@erase "$(INTDIR)\GetText.obj"
	-@erase "$(INTDIR)\GetText.sbr"
	-@erase "$(INTDIR)\GrayDlg.obj"
	-@erase "$(INTDIR)\GrayDlg.sbr"
	-@erase "$(INTDIR)\IntArr.obj"
	-@erase "$(INTDIR)\IntArr.sbr"
	-@erase "$(INTDIR)\label.obj"
	-@erase "$(INTDIR)\label.sbr"
	-@erase "$(INTDIR)\Led.obj"
	-@erase "$(INTDIR)\Led.sbr"
	-@erase "$(INTDIR)\LightBoxDlg.obj"
	-@erase "$(INTDIR)\LightBoxDlg.sbr"
	-@erase "$(INTDIR)\LogWin.obj"
	-@erase "$(INTDIR)\LogWin.sbr"
	-@erase "$(INTDIR)\memdc.obj"
	-@erase "$(INTDIR)\memdc.sbr"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.sbr"
	-@erase "$(INTDIR)\Mixer.obj"
	-@erase "$(INTDIR)\Mixer.sbr"
	-@erase "$(INTDIR)\MsgBox.obj"
	-@erase "$(INTDIR)\MsgBox.sbr"
	-@erase "$(INTDIR)\mxpad.obj"
	-@erase "$(INTDIR)\mxpad.sbr"
	-@erase "$(INTDIR)\PersistDlg.obj"
	-@erase "$(INTDIR)\PersistDlg.sbr"
	-@erase "$(INTDIR)\PersistInt.obj"
	-@erase "$(INTDIR)\PersistInt.sbr"
	-@erase "$(INTDIR)\PersistStr.obj"
	-@erase "$(INTDIR)\PersistStr.sbr"
	-@erase "$(INTDIR)\Picture.obj"
	-@erase "$(INTDIR)\Picture.sbr"
	-@erase "$(INTDIR)\PlaySound.obj"
	-@erase "$(INTDIR)\PlaySound.sbr"
	-@erase "$(INTDIR)\Plot.obj"
	-@erase "$(INTDIR)\Plot.sbr"
	-@erase "$(INTDIR)\PlotDlg.obj"
	-@erase "$(INTDIR)\PlotDlg.sbr"
	-@erase "$(INTDIR)\Popup.obj"
	-@erase "$(INTDIR)\Popup.sbr"
	-@erase "$(INTDIR)\RecordSound.obj"
	-@erase "$(INTDIR)\RecordSound.sbr"
	-@erase "$(INTDIR)\SendKeys.obj"
	-@erase "$(INTDIR)\SendKeys.sbr"
	-@erase "$(INTDIR)\ShowPic.obj"
	-@erase "$(INTDIR)\ShowPic.sbr"
	-@erase "$(INTDIR)\SimpleGrid.obj"
	-@erase "$(INTDIR)\SimpleGrid.sbr"
	-@erase "$(INTDIR)\Status.obj"
	-@erase "$(INTDIR)\Status.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Support.obj"
	-@erase "$(INTDIR)\Support.sbr"
	-@erase "$(INTDIR)\TextMode.obj"
	-@erase "$(INTDIR)\TextMode.sbr"
	-@erase "$(INTDIR)\transprog.obj"
	-@erase "$(INTDIR)\transprog.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Vis.obj"
	-@erase "$(INTDIR)\Vis.sbr"
	-@erase "$(INTDIR)\VisDlg.obj"
	-@erase "$(INTDIR)\VisDlg.sbr"
	-@erase "$(INTDIR)\waveEdit.obj"
	-@erase "$(INTDIR)\waveEdit.sbr"
	-@erase "$(INTDIR)\wavfrag.obj"
	-@erase "$(INTDIR)\wavfrag.pch"
	-@erase "$(INTDIR)\wavfrag.res"
	-@erase "$(INTDIR)\wavfrag.sbr"
	-@erase "$(INTDIR)\wavfragDlg.obj"
	-@erase "$(INTDIR)\wavfragDlg.sbr"
	-@erase "$(INTDIR)\xButton.obj"
	-@erase "$(INTDIR)\xButton.sbr"
	-@erase "$(INTDIR)\xProgCtrl.obj"
	-@erase "$(INTDIR)\xProgCtrl.sbr"
	-@erase "$(INTDIR)\xPtrArr.obj"
	-@erase "$(INTDIR)\xPtrArr.sbr"
	-@erase "$(INTDIR)\XrayM.obj"
	-@erase "$(INTDIR)\XrayM.sbr"
	-@erase "$(INTDIR)\xRect.obj"
	-@erase "$(INTDIR)\xRect.sbr"
	-@erase "$(OUTDIR)\wavfrag.bsc"
	-@erase "$(OUTDIR)\wavfrag.exe"
	-@erase "$(OUTDIR)\wavfrag.ilk"
	-@erase "$(OUTDIR)\wavfrag.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../common/work" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wavfrag.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wavfrag.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wavfrag.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ComColl.sbr" \
	"$(INTDIR)\ComConf.sbr" \
	"$(INTDIR)\Command.sbr" \
	"$(INTDIR)\dsp.sbr" \
	"$(INTDIR)\FileDialogST.sbr" \
	"$(INTDIR)\FreqScan.sbr" \
	"$(INTDIR)\GetText.sbr" \
	"$(INTDIR)\GrayDlg.sbr" \
	"$(INTDIR)\IntArr.sbr" \
	"$(INTDIR)\label.sbr" \
	"$(INTDIR)\Led.sbr" \
	"$(INTDIR)\LightBoxDlg.sbr" \
	"$(INTDIR)\LogWin.sbr" \
	"$(INTDIR)\memdc.sbr" \
	"$(INTDIR)\misc.sbr" \
	"$(INTDIR)\Mixer.sbr" \
	"$(INTDIR)\MsgBox.sbr" \
	"$(INTDIR)\mxpad.sbr" \
	"$(INTDIR)\PersistDlg.sbr" \
	"$(INTDIR)\PersistInt.sbr" \
	"$(INTDIR)\PersistStr.sbr" \
	"$(INTDIR)\Picture.sbr" \
	"$(INTDIR)\PlaySound.sbr" \
	"$(INTDIR)\Plot.sbr" \
	"$(INTDIR)\PlotDlg.sbr" \
	"$(INTDIR)\Popup.sbr" \
	"$(INTDIR)\RecordSound.sbr" \
	"$(INTDIR)\SendKeys.sbr" \
	"$(INTDIR)\ShowPic.sbr" \
	"$(INTDIR)\SimpleGrid.sbr" \
	"$(INTDIR)\Status.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Support.sbr" \
	"$(INTDIR)\TextMode.sbr" \
	"$(INTDIR)\transprog.sbr" \
	"$(INTDIR)\Vis.sbr" \
	"$(INTDIR)\VisDlg.sbr" \
	"$(INTDIR)\waveEdit.sbr" \
	"$(INTDIR)\wavfrag.sbr" \
	"$(INTDIR)\wavfragDlg.sbr" \
	"$(INTDIR)\xButton.sbr" \
	"$(INTDIR)\xProgCtrl.sbr" \
	"$(INTDIR)\xPtrArr.sbr" \
	"$(INTDIR)\XrayM.sbr" \
	"$(INTDIR)\xRect.sbr"

"$(OUTDIR)\wavfrag.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=wflibd.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\wavfrag.pdb" /debug /machine:I386 /out:"$(OUTDIR)\wavfrag.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ComColl.obj" \
	"$(INTDIR)\ComConf.obj" \
	"$(INTDIR)\Command.obj" \
	"$(INTDIR)\dsp.obj" \
	"$(INTDIR)\FileDialogST.obj" \
	"$(INTDIR)\FreqScan.obj" \
	"$(INTDIR)\GetText.obj" \
	"$(INTDIR)\GrayDlg.obj" \
	"$(INTDIR)\IntArr.obj" \
	"$(INTDIR)\label.obj" \
	"$(INTDIR)\Led.obj" \
	"$(INTDIR)\LightBoxDlg.obj" \
	"$(INTDIR)\LogWin.obj" \
	"$(INTDIR)\memdc.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\Mixer.obj" \
	"$(INTDIR)\MsgBox.obj" \
	"$(INTDIR)\mxpad.obj" \
	"$(INTDIR)\PersistDlg.obj" \
	"$(INTDIR)\PersistInt.obj" \
	"$(INTDIR)\PersistStr.obj" \
	"$(INTDIR)\Picture.obj" \
	"$(INTDIR)\PlaySound.obj" \
	"$(INTDIR)\Plot.obj" \
	"$(INTDIR)\PlotDlg.obj" \
	"$(INTDIR)\Popup.obj" \
	"$(INTDIR)\RecordSound.obj" \
	"$(INTDIR)\SendKeys.obj" \
	"$(INTDIR)\ShowPic.obj" \
	"$(INTDIR)\SimpleGrid.obj" \
	"$(INTDIR)\Status.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Support.obj" \
	"$(INTDIR)\TextMode.obj" \
	"$(INTDIR)\transprog.obj" \
	"$(INTDIR)\Vis.obj" \
	"$(INTDIR)\VisDlg.obj" \
	"$(INTDIR)\waveEdit.obj" \
	"$(INTDIR)\wavfrag.obj" \
	"$(INTDIR)\wavfragDlg.obj" \
	"$(INTDIR)\xButton.obj" \
	"$(INTDIR)\xProgCtrl.obj" \
	"$(INTDIR)\xPtrArr.obj" \
	"$(INTDIR)\XrayM.obj" \
	"$(INTDIR)\xRect.obj" \
	"$(INTDIR)\wavfrag.res"

"$(OUTDIR)\wavfrag.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("wavfrag.dep")
!INCLUDE "wavfrag.dep"
!ELSE 
!MESSAGE Warning: cannot find "wavfrag.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "wavfrag - Win32 Release" || "$(CFG)" == "wavfrag - Win32 Debug"
SOURCE=.\ComColl.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\ComColl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\ComColl.obj"	"$(INTDIR)\ComColl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\ComConf.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\ComConf.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\ComConf.obj"	"$(INTDIR)\ComConf.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\Command.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Command.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Command.obj"	"$(INTDIR)\Command.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\dsp.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\dsp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\dsp.obj"	"$(INTDIR)\dsp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\FileDialogST.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\FileDialogST.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\FileDialogST.obj"	"$(INTDIR)\FileDialogST.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\FreqScan.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\FreqScan.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\FreqScan.obj"	"$(INTDIR)\FreqScan.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\GetText.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\GetText.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\GetText.obj"	"$(INTDIR)\GetText.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\GrayDlg.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\GrayDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\GrayDlg.obj"	"$(INTDIR)\GrayDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\IntArr.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\IntArr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\IntArr.obj"	"$(INTDIR)\IntArr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\label.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\label.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\label.obj"	"$(INTDIR)\label.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\Led.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Led.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Led.obj"	"$(INTDIR)\Led.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\LightBoxDlg.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\LightBoxDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\LightBoxDlg.obj"	"$(INTDIR)\LightBoxDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\LogWin.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\LogWin.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\LogWin.obj"	"$(INTDIR)\LogWin.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\memdc.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\memdc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\memdc.obj"	"$(INTDIR)\memdc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\misc.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\misc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\misc.obj"	"$(INTDIR)\misc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Mixer.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Mixer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Mixer.obj"	"$(INTDIR)\Mixer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\MsgBox.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\MsgBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\MsgBox.obj"	"$(INTDIR)\MsgBox.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\mxpad.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\mxpad.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\mxpad.obj"	"$(INTDIR)\mxpad.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\PersistDlg.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\PersistDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\PersistDlg.obj"	"$(INTDIR)\PersistDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\PersistInt.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\PersistInt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\PersistInt.obj"	"$(INTDIR)\PersistInt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\PersistStr.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\PersistStr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\PersistStr.obj"	"$(INTDIR)\PersistStr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Picture.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Picture.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Picture.obj"	"$(INTDIR)\Picture.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\PlaySound.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\PlaySound.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\PlaySound.obj"	"$(INTDIR)\PlaySound.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\Plot.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Plot.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Plot.obj"	"$(INTDIR)\Plot.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\PlotDlg.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\PlotDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\PlotDlg.obj"	"$(INTDIR)\PlotDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\Popup.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Popup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Popup.obj"	"$(INTDIR)\Popup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\RecordSound.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\RecordSound.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\RecordSound.obj"	"$(INTDIR)\RecordSound.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SendKeys.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\SendKeys.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\SendKeys.obj"	"$(INTDIR)\SendKeys.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\ShowPic.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\ShowPic.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\ShowPic.obj"	"$(INTDIR)\ShowPic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\SimpleGrid.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\SimpleGrid.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\SimpleGrid.obj"	"$(INTDIR)\SimpleGrid.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Status.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Status.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Status.obj"	"$(INTDIR)\Status.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../common/work" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\wavfrag.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wavfrag.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../common/work" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wavfrag.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\wavfrag.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\common\work\Support.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Support.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Support.obj"	"$(INTDIR)\Support.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\TextMode.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\TextMode.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\TextMode.obj"	"$(INTDIR)\TextMode.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\transprog.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\transprog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\transprog.obj"	"$(INTDIR)\transprog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\Vis.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\Vis.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\Vis.obj"	"$(INTDIR)\Vis.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\VisDlg.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\VisDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\VisDlg.obj"	"$(INTDIR)\VisDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\waveEdit.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\waveEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\waveEdit.obj"	"$(INTDIR)\waveEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\wavfrag.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\wavfrag.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\wavfrag.obj"	"$(INTDIR)\wavfrag.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=.\wavfragDlg.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\wavfragDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\wavfragDlg.obj"	"$(INTDIR)\wavfragDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\xButton.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\xButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\xButton.obj"	"$(INTDIR)\xButton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\xProgCtrl.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\xProgCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\xProgCtrl.obj"	"$(INTDIR)\xProgCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"


!ENDIF 

SOURCE=..\..\common\work\xPtrArr.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\xPtrArr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\xPtrArr.obj"	"$(INTDIR)\xPtrArr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\XrayM.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\XrayM.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\XrayM.obj"	"$(INTDIR)\XrayM.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\work\xRect.cpp

!IF  "$(CFG)" == "wavfrag - Win32 Release"


"$(INTDIR)\xRect.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "wavfrag - Win32 Debug"


"$(INTDIR)\xRect.obj"	"$(INTDIR)\xRect.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wavfrag.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\wavfrag.rc

"$(INTDIR)\wavfrag.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

