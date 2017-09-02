cd ..\wflib
nmake -f wflib.mak  CFG="wflib - Win32 Release"
cd ..
nmake -f WavFrag.mak  CFG="wavfrag - Win32 Release"
cd install
"C:\Program Files\NSIS\makensisw.exe" wavfrag.nsi