//----------------------------------------------------------------------------------------------------------------------
///	\file		MaterialWork.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class declaration of MaterialWork ( Dialog handler ).
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
#ifndef AFX_MATERIALWORK_H__F1248254_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_
#define AFX_MATERIALWORK_H__F1248254_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_


//----------------------------------------------------------------------------------------------------------------------
///	\class		CMaterialWork
///	\ingroup	GUI
///
///	\brief	Class for material management.
//----------------------------------------------------------------------------------------------------------------------
class CMaterialWork : public CDialog
{
public:
	CMaterialWork(CWnd* pParent = NULL);

	//{{AFX_DATA(CMaterialWork)
	enum { IDD = IDD_MATERIALWORK };
	double	m_dEmodul;
	double	m_dFlaeche;
	double	m_dIy;
	double	m_dMpl;
	
	//}}AFX_DATA

	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CMaterialWork)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	virtual BOOL OnInitDialog();

protected:
	//{{AFX_MSG(CMaterialWork)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strMatName;
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
};

//----------------------------------------------------------------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}

#endif // AFX_MATERIALWORK_H__F1248254_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_
