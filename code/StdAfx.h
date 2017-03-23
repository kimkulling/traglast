/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : StdAfx.h
// Desc.       : 
// Autor       : Kim Kulling
// Last mod.   : 16.12.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STDAFX__H
#define __STDAFX__H

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxdisp.h>        // MFC Automatisierungsklassen
#include <afxdtctl.h>		// MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterstützung für gängige Windows-Steuerelemente
#endif 

// Including OpenGL-header

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <new.h>

#include "vector.h"
#include "fem2d.h"
#include "mymathdef.h"
#include "wtErrorHandler.h"
#include "Inzidenz.h"
#include "Last.h"
#include "band.h"
#include "LinALg.h"
#include "element_berechnen.h"
#include "Structure.h"
#include "wtErrorHandler.h"

#endif
