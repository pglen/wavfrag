;///////////////////////////////////////////////////////////////////////////
;//

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;Name and file

  Name "WavFrag"

;--------------------------------
;Build target selection

    !echo "------------------------"
    !echo "Build WavFrag Original Version"

    OutFile ".\bin\wfsetup.exe"
    !define BANNER  "logo.jpg"

    ;Default installation folder
    InstallDir "$PROGRAMFILES\WavFrag"

    BrandingText " WavFrag Recog "

    ;Get installation folder from registry if available
    InstallDirRegKey HKCU "Software\WavFrag" ""

VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "WavFrag Voice Recognition"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "RobotMonkeySoftware LLC"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© RobotMonkeySoftware LLC, 2010"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "Voice Recognition Engine Demo"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "1,0"

VIProductVersion "1.0.0.0"

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "License.txt"
  
  ;!insertmacro MUI_PAGE_COMPONENTS

  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !define 	 	MUI_FINISHPAGE_RUN $PROGRAMFILES\WavFrag\WavFrag.exe
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

    !insertmacro MUI_LANGUAGE "English"
	;RequestExecutionLevel user

    icon WavFrag.ico
    uninstallicon WavFrag.ico

; -------------------------------------------------------------------------
;Installer Sections

Section "Install WavFrag Code" SecCode

    SetShellVarContext all

    SetOutPath "$INSTDIR"

    File  /oname=WavFrag.exe ..\Release\WavFrag.exe
	File  /oname=wflib.dll 	..\wflib\Release\wflib.dll
	File  /oname=wflib.lib 	..\wflib\Release\wflib.lib
	File  /oname=wflib.h 	..\wflib\wflib.h
	
    File  Readme.txt
    File  License.txt
    
	;File  /r /x ".svn" /x "*.cpt" /x "*.xcpt" /x "_autosave" "..\wav"
	
    CreateDirectory "html"
	File  /r /x ".svn" /x "*.cpt" /x "*.xcpt" /x "_autosave" /x cpt /x rtf "..\html"
    
	;MessageBox MB_OK $APPDATA
	; --------------------------------------------------------------------
	CreateDirectory "$APPDATA\WavFrag"
	SetOutPath "$APPDATA\WavFrag"
	File  /oname=WavFrag.wfc ..\WavFrag.wfc

	CreateDirectory "stock"
	File  /r /x ".svn" /x "*.cpt" /x "*.xcpt" /x "_autosave" /x "raw" "..\stock"
	
	CreateDirectory "wav"
	SetOutPath "$APPDATA\WavFrag\wav"
	File /r /x ".svn" /x "*.cpt" /x "*.xcpt" /x "_autosave" /x "raw" "..\wavstock\*.*"
	
	SetOutPath "$APPDATA\WavFrag"
	CreateDirectory "history"
	
	SetOutPath "$INSTDIR"

	; Install system specific items
    ;SetOutPath "$SYSDIR"

    ; ---------------------------------------------------------------------
    ;SetOutPath $INSTDIR

    CreateDirectory $SMPROGRAMS\WavFrag
    CreateShortCut "$SENDTO\WavFrag.lnk" "$INSTDIR\WavFrag.exe"
    CreateShortCut "$SMPROGRAMS\WavFrag\WavFrag.lnk" "$INSTDIR\WavFrag.exe" "" \
                    "$INSTDIR\WavFrag.exe" 0  SW_SHOWNORMAL  "ALT|CONTROL|D"

    CreateShortCut "$QUICKLAUNCH\WavFrag.lnk" "$INSTDIR\WavFrag.exe"

;    CreateShortCut "$SMPROGRAMS\WavFrag\WavFrag Web Site.lnk" "http://www.robotmonkeysoftware.com/wavfrag" "" \
;                    "" 0  SW_SHOWNORMAL 

    CreateDirectory $SMPROGRAMS\WavFrag\Documents
    CreateShortCut "$SMPROGRAMS\WavFrag\Documents\Readme.lnk" "$INSTDIR\Readme.txt"
    CreateShortCut "$SMPROGRAMS\WavFrag\Documents\HTML Documentation.lnk" "$INSTDIR\html\index.html"

;    CreateShortCut "$SMPROGRAMS\WavFrag\Documents\Quick Start.lnk" "$INSTDIR\Quick_Start.doc"

    CreateDirectory $SMPROGRAMS\WavFrag\Tools
    CreateShortCut "$SMPROGRAMS\WavFrag\Tools\Uninstall.lnk" "$INSTDIR\Uninstall.exe" \
                    "$INSTDIR\WavFrag.exe"

;    CreateShortCut "$SMPROGRAMS\WavFrag\Tools\License.lnk" "$INSTDIR\License.txt"
;    CreateShortCut "$DESKTOP\WavFrag.lnk" "$INSTDIR\WavFrag.exe"

    ;Store installation folder
    WriteRegStr HKCU "Software\WavFrag" "" $INSTDIR

    ; ---------------------------------------------------------------------
    ;Register WavFrag file as .WavFrag handler

    ;WriteRegStr HKCR ".WavFrag" "" "WavFrag.FileHandler"
    ;WriteRegStr HKCR "WavFrag.FileHandler" "" ""
    ;WriteRegStr HKCR "WavFrag.FileHandler\shell" "" "open"
    ;WriteRegStr HKCR "WavFrag.FileHandler\DefaultIcon" "" "$INSTDIR\WavFrag.exe,0"
    ;WriteRegStr HKCR "WavFrag.FileHandler\shell\open\command" "" '$INSTDIR\WavFrag.exe "%1"'
    ;WriteRegStr HKCR "WavFrag.FileHandler\shell\edit" "" ""
    ;WriteRegStr HKCR "WavFrag.FileHandler\shell\edit\command" "" '$INSTDIR\WavFrag.exe "%1"'

    ;Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

    ; Create control panel unistaller
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WavFrag"  "DisplayName" "WavFrag Command Recogntion  "
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WavFrag"  "UninstallString" $INSTDIR\Uninstall.exe
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WavFrag"  "DisplayIcon" $INSTDIR\WavFrag.exe,0"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WavFrag"  "DisplayVersion" "Version 1.0"
    ;WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WavFrag"  "HelpLink" "http://www.robotmonkeysoftware.com//wavfrag"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WavFrag"  "NoModify" 1
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WavFrag"  "NoRepair" 1

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

    SetShellVarContext all

    ;ADD YOUR OWN FILES HERE...

    Delete "$INSTDIR\Uninstall.exe"
    Delete "$INSTDIR\WavFrag.exe"

    RMDir /r "$INSTDIR"

    Delete "$SMPROGRAMS\WavFrag\WavFrag.lnk"
    Delete "$SMPROGRAMS\WavFrag\Readme.lnk"
    Delete "$SMPROGRAMS\WavFrag\License.lnk"

    Delete "$SMPROGRAMS\WavFrag\Guide_inside.pdf"
    Delete "$SMPROGRAMS\WavFrag\Guide_outside.pdf"
    Delete "$SMPROGRAMS\WavFrag\manual.pdf"

    Delete "$QUICKLAUNCH\WavFrag.lnk"
    Delete "$DESKTOP\WavFrag.lnk"
    Delete "$SENDTO\WavFrag.lnk"

    RMDir /r "$SMPROGRAMS\WavFrag\Tools\"
    RMDir /r "$SMPROGRAMS\WavFrag\"

    DeleteRegKey HKCU "Software\WavFrag"
    DeleteRegKey HKCR ".WavFrag"
    DeleteRegKey HKCR "WavFrag.FileHandler"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WavFrag"

SectionEnd

;  LangString DESC_SecCode ${LANG_ENGLISH} "Install WavFrag code.$\r$\n$\r$\n\
;  UnCheck (unselect) this if you do not want the installation to modify or update the WavFrag executable."
;
;  LangString DESC_SecData ${LANG_ENGLISH} "Install WavFrag data.$\r$\n$\r$\n\
;  UnCheck (unselect) this if you do not want the installation to modify or update any of your implant systems."
;
;  LangString DESC_SecImp ${LANG_ENGLISH} "Install WavFrag Implants data.$\r$\n$\r$\n\
; UnCheck (unselect) this if you do not want the installation to modify or update any of your implant systems."
;
;  LangString DESC_SecGal ${LANG_ENGLISH} "Install WavFrag Galleries data.$\r$\n$\r$\n\
; UnCheck (unselect) this if you do not want the installation to modify or update any of your gallery items."
;
;  LangString DESC_SecPat ${LANG_ENGLISH} "Install WavFrag Sample patient data.$\r$\n$\r$\n\
; UnCheck (unselect) this if you do not want the installation to modify or update any of your patient items. (safe to leave it checked)"
;
;  ;Assign language strings to sections
;  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
;    !insertmacro MUI_DESCRIPTION_TEXT ${SecCode} $(DESC_SecCode)
;    !insertmacro MUI_DESCRIPTION_TEXT ${SecData} $(DESC_SecData)
;    !insertmacro MUI_DESCRIPTION_TEXT ${SecGal} $(DESC_SecGal)
;    !insertmacro MUI_DESCRIPTION_TEXT ${SecPat} $(DESC_SecPat)
;  !insertmacro MUI_FUNCTION_DESCRIPTION_END
;

