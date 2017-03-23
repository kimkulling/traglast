//----------------------------------------------------------------------------------------------------------------------
///	\file		EinzelEinwirkung.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class declaration of Einzeleinwirkung ( Dialog handler ).
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
#ifndef AFX_EINZELEINWIRKUNG_H__C9045FA1_FD13_11D4_86F7_5254AB1A2D1D__INCLUDED_
#define AFX_EINZELEINWIRKUNG_H__C9045FA1_FD13_11D4_86F7_5254AB1A2D1D__INCLUDED_


//----------------------------------------------------------------------------------------------------------------------
///	\class		CEinzeleinwirkung
///	\ingroup	GUI
///	
///	\brief	Dialog handler for nodal point loads.
//----------------------------------------------------------------------------------------------------------------------
class CEinzeleinwirkung : public CDialog
{
public:
	CEinzeleinwirkung(CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CEinzeleinwirkung)
	enum { IDD = IDD_EINZELEINWIRKUNG };
	double	m_dEinwirkung;
	int		m_iN;
	CString	m_strChoosed;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CEinzeleinwirkung)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	virtual BOOL OnInitDialog();

protected:
	//{{AFX_MSG(CEinzeleinwirkung)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
	int m_iChoose;
};

//----------------------------------------------------------------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}

#endif // AFX_EINZELEINWIRKUNG_H__C9045FA1_FD13_11D4_86F7_5254AB1A2D1D__INCLUDED_
