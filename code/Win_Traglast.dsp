# Microsoft Developer Studio Project File - Name="Win_Traglast" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Win_Traglast - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Win_Traglast.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Win_Traglast.mak" CFG="Win_Traglast - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Win_Traglast - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Win_Traglast - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win_Traglast - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Win_Traglast - Win32 Debug"

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
# ADD CPP /nologo /G5 /Zp1 /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Win_Traglast - Win32 Release"
# Name "Win_Traglast - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Band.cpp
# End Source File
# Begin Source File

SOURCE=.\CalcOption.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculate.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\Delmat.cpp
# End Source File
# Begin Source File

SOURCE=.\Eigenschaften.cpp
# End Source File
# Begin Source File

SOURCE=.\Einzeleinwirkung.cpp
# End Source File
# Begin Source File

SOURCE=.\Element.cpp
# End Source File
# Begin Source File

SOURCE=.\element_berechnen.cpp

!IF  "$(CFG)" == "Win_Traglast - Win32 Release"

!ELSEIF  "$(CFG)" == "Win_Traglast - Win32 Debug"

# ADD CPP /w /W0

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ElementWork.cpp
# End Source File
# Begin Source File

SOURCE=.\Inzidenz.cpp
# End Source File
# Begin Source File

SOURCE=.\Koord.cpp
# End Source File
# Begin Source File

SOURCE=.\KoordWork.cpp
# End Source File
# Begin Source File

SOURCE=.\Lager.cpp
# End Source File
# Begin Source File

SOURCE=.\Last.cpp
# End Source File
# Begin Source File

SOURCE=.\LinAlg.cpp
# End Source File
# Begin Source File

SOURCE=.\logfile.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Material.cpp
# End Source File
# Begin Source File

SOURCE=.\MaterialWork.cpp
# End Source File
# Begin Source File

SOURCE=.\Myfont.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMathDef.cpp
# End Source File
# Begin Source File

SOURCE=.\oglPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Streckeneinwirkung.cpp
# End Source File
# Begin Source File

SOURCE=.\Structure.cpp
# End Source File
# Begin Source File

SOURCE=.\Tragwerk.cpp
# End Source File
# Begin Source File

SOURCE=.\TragwerkInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Vektor.cpp
# End Source File
# Begin Source File

SOURCE=.\Win_Traglast.cpp
# End Source File
# Begin Source File

SOURCE=.\Win_Traglast.rc
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Band.h
# End Source File
# Begin Source File

SOURCE=.\CalcOption.h
# End Source File
# Begin Source File

SOURCE=.\Calculate.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\Delmat.h
# End Source File
# Begin Source File

SOURCE=.\Eigenschaften.h
# End Source File
# Begin Source File

SOURCE=.\Einzeleinwirkung.h
# End Source File
# Begin Source File

SOURCE=.\element_berechnen.h
# End Source File
# Begin Source File

SOURCE=.\ElementWork.h
# End Source File
# Begin Source File

SOURCE=.\fem2d.h
# End Source File
# Begin Source File

SOURCE=.\inzidenz.h
# End Source File
# Begin Source File

SOURCE=.\KoordWork.h
# End Source File
# Begin Source File

SOURCE=.\Last.h
# End Source File
# Begin Source File

SOURCE=.\LinALg.h
# End Source File
# Begin Source File

SOURCE=.\logfile.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MaterialWork.h
# End Source File
# Begin Source File

SOURCE=.\Myfont.h
# End Source File
# Begin Source File

SOURCE=.\mymathdef.h
# End Source File
# Begin Source File

SOURCE=.\oglPlot.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Streckeneinwirkung.h
# End Source File
# Begin Source File

SOURCE=.\Structure.h
# End Source File
# Begin Source File

SOURCE=.\TragwerkInfo.h
# End Source File
# Begin Source File

SOURCE=.\Win_Traglast.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\calcbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\forcebar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\koordbar.bmp
# End Source File
# Begin Source File

SOURCE=.\MyCross.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Win_Traglast.ico
# End Source File
# Begin Source File

SOURCE=.\res\Win_Traglast.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
