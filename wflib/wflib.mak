# Microsoft Developer Studio Generated NMAKE File, Based on wflib.dsp
!IF "$(CFG)" == ""
CFG=wflib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to wflib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "wflib - Win32 Release" && "$(CFG)" != "wflib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "wflib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\wflib.dll"


CLEAN :
	-@erase "$(INTDIR)\Contain.obj"
	-@erase "$(INTDIR)\dsp.obj"
	-@erase "$(INTDIR)\Fft.obj"
	-@erase "$(INTDIR)\FftBuff.obj"
	-@erase "$(INTDIR)\Frag.obj"
	-@erase "$(INTDIR)\FragColl.obj"
	-@erase "$(INTDIR)\IntArr.obj"
	-@erase "$(INTDIR)\mxpad.obj"
	-@erase "$(INTDIR)\Recog.obj"
	-@erase "$(INTDIR)\RecordSound.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Support.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wflib.obj"
	-@erase "$(INTDIR)\wflib.pch"
	-@erase "$(INTDIR)\wflib.res"
	-@erase "$(OUTDIR)\wflib.dll"
	-@erase "$(OUTDIR)\wflib.exp"
	-@erase "$(OUTDIR)\wflib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../../common/work" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\wflib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wflib.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wflib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\wflib.pdb" /machine:I386 /def:".\wflib.def" /out:"$(OUTDIR)\wflib.dll" /implib:"$(OUTDIR)\wflib.lib" 
DEF_FILE= \
	".\wflib.def"
LINK32_OBJS= \
	"$(INTDIR)\Contain.obj" \
	"$(INTDIR)\dsp.obj" \
	"$(INTDIR)\Fft.obj" \
	"$(INTDIR)\FftBuff.obj" \
	"$(INTDIR)\Frag.obj" \
	"$(INTDIR)\FragColl.obj" \
	"$(INTDIR)\IntArr.obj" \
	"$(INTDIR)\mxpad.obj" \
	"$(INTDIR)\Recog.obj" \
	"$(INTDIR)\RecordSound.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Support.obj" \
	"$(INTDIR)\wflib.obj" \
	"$(INTDIR)\wflib.res"

"$(OUTDIR)\wflib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\wflib.dll"
   copy Release\wflib.dll  ..\Release
	copy Release\wflib.lib ..
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "wflib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\wflib.dll"


CLEAN :
	-@erase "$(INTDIR)\Contain.obj"
	-@erase "$(INTDIR)\dsp.obj"
	-@erase "$(INTDIR)\Fft.obj"
	-@erase "$(INTDIR)\FftBuff.obj"
	-@erase "$(INTDIR)\Frag.obj"
	-@erase "$(INTDIR)\FragColl.obj"
	-@erase "$(INTDIR)\IntArr.obj"
	-@erase "$(INTDIR)\mxpad.obj"
	-@erase "$(INTDIR)\Recog.obj"
	-@erase "$(INTDIR)\RecordSound.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Support.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wflib.obj"
	-@erase "$(INTDIR)\wflib.pch"
	-@erase "$(INTDIR)\wflib.res"
	-@erase "$(OUTDIR)\wflib.dll"
	-@erase "$(OUTDIR)\wflib.exp"
	-@erase "$(OUTDIR)\wflib.ilk"
	-@erase "$(OUTDIR)\wflib.lib"
	-@erase "$(OUTDIR)\wflib.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../common/work" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\wflib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wflib.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wflib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\wflib.pdb" /debug /machine:I386 /def:".\wflib.def" /out:"$(OUTDIR)\wflib.dll" /implib:"$(OUTDIR)\wflib.lib" /pdbtype:sept 
DEF_FILE= \
	".\wflib.def"
LINK32_OBJS= \
	"$(INTDIR)\Contain.obj" \
	"$(INTDIR)\dsp.obj" \
	"$(INTDIR)\Fft.obj" \
	"$(INTDIR)\FftBuff.obj" \
	"$(INTDIR)\Frag.obj" \
	"$(INTDIR)\FragColl.obj" \
	"$(INTDIR)\IntArr.obj" \
	"$(INTDIR)\mxpad.obj" \
	"$(INTDIR)\Recog.obj" \
	"$(INTDIR)\RecordSound.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Support.obj" \
	"$(INTDIR)\wflib.obj" \
	"$(INTDIR)\wflib.res"

"$(OUTDIR)\wflib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\wflib.dll"
   copy Debug\wflib.dll  ..\Debug
	copy Debug\wflib.lib  ..\wflibd.lib
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("wflib.dep")
!INCLUDE "wflib.dep"
!ELSE 
!MESSAGE Warning: cannot find "wflib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "wflib - Win32 Release" || "$(CFG)" == "wflib - Win32 Debug"
SOURCE=.\Contain.cpp

"$(INTDIR)\Contain.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"


SOURCE=..\..\..\common\work\dsp.cpp

"$(INTDIR)\dsp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Fft.cpp

"$(INTDIR)\Fft.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"


SOURCE=.\FftBuff.cpp

"$(INTDIR)\FftBuff.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"


SOURCE=.\Frag.cpp

"$(INTDIR)\Frag.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"


SOURCE=.\FragColl.cpp

"$(INTDIR)\FragColl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"


SOURCE=..\..\..\common\work\IntArr.cpp

"$(INTDIR)\IntArr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\common\work\mxpad.cpp

"$(INTDIR)\mxpad.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Recog.cpp

"$(INTDIR)\Recog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"


SOURCE=..\..\..\common\work\RecordSound.cpp

"$(INTDIR)\RecordSound.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "wflib - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../../common/work" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\wflib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wflib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "wflib - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../common/work" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\wflib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wflib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\common\work\Support.cpp

"$(INTDIR)\Support.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\wflib.cpp

"$(INTDIR)\wflib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wflib.pch"


SOURCE=.\wflib.rc

"$(INTDIR)\wflib.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

