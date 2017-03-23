//----------------------------------------------------------------------------------------------------------------------
///	\file		ElementWork.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class declaration of ElementWork ( Dialog handler ).
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
#if !defined(AFX_ELEMENTWORK_H__2E38A38B_FB7B_11D4_86F7_5254AB1A2D1D__INCLUDED_)
#define AFX_ELEMENTWORK_H__2E38A38B_FB7B_11D4_86F7_5254AB1A2D1D__INCLUDED_

//----------------------------------------------------------------------------------------------------------------------
///	\class		CElementWork
///	\ingroup	GUI
///
///\brief	Class to manage element work dialog.
//----------------------------------------------------------------------------------------------------------------------
class CElementWork : public CDialog
{
public:
	CElementWork(CWnd* pParent = NULL);

	//{{AFX_DATA(CElementWork)
	enum { IDD = IDD_ELEMENTWORK };
	int		m_iKn1;
	int		m_iKn2;
	int		m_iEleAnz;
	CString	m_strChoose;
	CString	m_strC;
	//}}AFX_DATA

// Überschreibungen
	//{{AFX_VIRTUAL(CElementWork)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CElementWork)
	afx_msg void OnSelect();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList1();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnSelchangeList3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
	int iChoosed , iArt, iLager;

};

//----------------------------------------------------------------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}

#endif // AFX_ELEMENTWORK_H__2E38A38B_FB7B_11D4_86F7_5254AB1A2D1D__INCLUDED_
