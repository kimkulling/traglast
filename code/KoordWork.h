//----------------------------------------------------------------------------------------------------------------------
///	\file		KoordWork.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Class declaration of KoordWork ( Dialog handler ).
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
#if !defined(AFX_KOORDWORK_H__F1248250_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_)
#define AFX_KOORDWORK_H__F1248250_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_

#include "Childview.h"
#include "afxwin.h"

//----------------------------------------------------------------------------------------------------------------------
///	\class		CKoordWork
///	\ingroup	GUI
///
///	\brief	Class to handle coordinate management.
//----------------------------------------------------------------------------------------------------------------------
class CKoordWork : public CDialog
{
public:
	CKoordWork(CWnd* pParent = NULL);
	virtual ~CKoordWork();
	virtual BOOL OnInitDialog();



// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CKoordWork)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CKoordWork)
	virtual void OnOK();
	afx_msg void OnNext();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	//{{AFX_DATA(CKoordWork)
	enum { IDD = IDD_KOORDWORK };
	double	m_dXKoord;
	double	m_dYKoord;
	//}}AFX_DATA
	CChildView  m_wndView;
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
	CButton m_ButtonNext;
	long lX, lY, lZ;

};

//----------------------------------------------------------------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}

#endif // AFX_KOORDWORK_H__F1248250_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_
