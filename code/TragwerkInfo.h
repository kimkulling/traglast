//----------------------------------------------------------------------------------------------------------------------
///	\file		TragwerkInfo.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class declaration of TragwerkInfo ( Dialog handler ).
///
/// This program is free software: you can redistribute it and/or modify
///	it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------------------------------------------------
#include "afxwin.h"
#if !defined(AFX_TRAGWERKINFO_H__2E38A38A_FB7B_11D4_86F7_5254AB1A2D1D__INCLUDED_)
#define AFX_TRAGWERKINFO_H__2E38A38A_FB7B_11D4_86F7_5254AB1A2D1D__INCLUDED_

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CTragwerkInfo : public CDialog
{
// Konstruktion
public:
	CTragwerkInfo(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CTragwerkInfo)
	enum { IDD = IDD_TRAGWERKINFO };
	CString	m_strKoordAnz;
	CString	m_strMatAnz;
	CString	m_strEleAnz;
	CString	m_strLastAnz;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CTragwerkInfo)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL
	virtual BOOL OnInitDialog();

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CTragwerkInfo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
};

//----------------------------------------------------------------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}

#endif // AFX_TRAGWERKINFO_H__2E38A38A_FB7B_11D4_86F7_5254AB1A2D1D__INCLUDED_
