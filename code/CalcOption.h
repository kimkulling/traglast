//----------------------------------------------------------------------------------------------------------------------
///	\file		CalcOption.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Class declaration of CalcOption ( Dialog handler ).
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
#ifndef TL_GUI_CALCOPTION__H_INC
#define TL_GUI_CALCOPTION__H_INC

#include "afxwin.h"


//----------------------------------------------------------------------------------------------------------------------
///	\class		CCalcOption
///	\ingroup	GUI
///
///	\brief	Handles the calculate options for a computation.
//----------------------------------------------------------------------------------------------------------------------
class CCalcOption : public CDialog
{
public:
	///	Constructor.
	CCalcOption(CWnd* pParent = NULL); 
	///	Destructor.
	~CCalcOption();

	//{{AFX_DATA(CCalcOption)
	enum { IDD = IDD_CALCOPTION };
	double	m_dMoment;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CCalcOption)
protected:
	///	Data exchanage handling.
	virtual void DoDataExchange(CDataExchange* pDX);
	///	Creation of dialg resources.
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CCalcOption)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual void OnOK();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CButton m_UseLog;
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
};
//----------------------------------------------------------------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}

#endif // TL_GUI_CALCOPTION__H_INC
