//----------------------------------------------------------------------------------------------------------------------
///	\file		Eigenschaften.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class declaration of Eigenschaften ( Dialog handler ).
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
#if !defined(AFX_EIGENSCHAFTEN_H__2A9E74E1_22CF_11D5_86F9_5254AB1A2D1D__INCLUDED_)
#define AFX_EIGENSCHAFTEN_H__2A9E74E1_22CF_11D5_86F9_5254AB1A2D1D__INCLUDED_

#include <map>
#include <string>

//----------------------------------------------------------------------------------------------------------------------
///	\class		CEigenschaften
///	\ingroup	GUI
///
///	\brief	Handles the property dialog GUI:
//----------------------------------------------------------------------------------------------------------------------
class CEigenschaften : public CDialog
{
public:
	CEigenschaften(CWnd* pParent = NULL);

	//{{AFX_DATA(CEigenschaften)
	enum { IDD = IDD_EIGENSCHAFTEN };
	//}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CEigenschaften)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchangeCombo1();
	
private:
	std::map<Core::i32, std::string> m_ProvidedLanguages;
	CComboBox m_LangSelector;
};

//{{AFX_INSERT_LOCATION}}
//----------------------------------------------------------------------------------------------------------------------


#endif // AFX_EIGENSCHAFTEN_H__2A9E74E1_22CF_11D5_86F9_5254AB1A2D1D__INCLUDED_
