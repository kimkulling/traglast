//----------------------------------------------------------------------------------------------------------------------
///	\file		MainFrm.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Class declaration of MainFrm, implements the main window handling.
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
#ifndef AFX_MAINFRM_H__F1248247_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_
#define AFX_MAINFRM_H__F1248247_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_

#include "ChildView.h"
#include "LocalizationObserverSubject.h"

namespace Localization
{
class LocalizationObserver;
}

//----------------------------------------------------------------------------------------------------------------------
///	\class		CMainFrame
///	\ingroup	GUI
///
///	\brief	Class to handle the main window of the MFC application. Here all menu activities will be 
///	handled.
//----------------------------------------------------------------------------------------------------------------------
class CMainFrame:	public CFrameWnd,
					public Localization::LocalizationObserverSubject

{
public:
	///	Constructor.
	CMainFrame();
	///	Destructor.
	virtual ~CMainFrame();
	///	Callback for language change.
	bool onLanguageChange();
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void WriteProblem();
	void ReadProblem();
	CStatusBar *getStatusBar() const;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnTragwerkKoordinatenbearbeiten();
	afx_msg void OnTragwerkMaterialbearbeiten();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTragwerkTragwerksinfo();
	afx_msg void OnTragwerkElementebearbeitenNumerisch();
	afx_msg void OnDateiFfnen();
	afx_msg void OnDateiSpeichern();
	afx_msg void OnTragwerkLastenbearbeitenEinzellastenbearbeiten();
	afx_msg void OnBerechnungBerechnungstarten();
	afx_msg void OnButton32778();
	afx_msg void OnButton32780();
	afx_msg void OnButton32779();
	afx_msg void OnAnsichtZoomZoomin();
	afx_msg void OnAnsichtZoomZoomout();
	afx_msg void OnButton32787();
	afx_msg void OnButton32789();
	afx_msg void OnButton32788();
	afx_msg void OnButton32790();
	afx_msg void OnButton32793();
	afx_msg void OnBerechnungErgebnisseDurchbiegung();
	afx_msg void OnBerechnungErgebnisseLngskraft();
	afx_msg void OnBerechnungErgebnisseMoment();
	afx_msg void OnBerechnungErgebnisseQuerkraft();
	afx_msg void OnBerechnungErgebnisselschen();
	afx_msg void OnButton32799();
	afx_msg void OnButton32800();
	afx_msg void OnOpen();
	afx_msg void OnAnsichtEinstellungen();
	afx_msg void OnTragwerkLastenbearbeitenLinieneinwirkungerzeugen();
	afx_msg void OnButton32798();
	afx_msg void OnDateiNeu();
	afx_msg void OnTragwerkMaterialbearbeitenMaterialerzeugen();
	afx_msg void OnTragwerkMaterialbearbeitenMateriallschen();
	afx_msg void OnButtoncalc();
	afx_msg void OnButtonmoment();
	afx_msg void OnButtonquer();
	afx_msg void OnButtonlaengs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected: 
	DECLARE_DYNAMIC(CMainFrame)

private:
	void langSetupFileMenu( CMenu *pMenu );
	void langSetupStructureMenu( CMenu *pMenu );
	void langSetupComputationMenu( CMenu *pMenu );
	bool setLangStringInMenu( CMenu *pMenu, const std::string &rTag, UINT id );
	void showLastError(LPTSTR lpszFunction);

private:
	CStatusBar m_wndStatusBar;
	CStatusBar *m_pStatusBar;
	CToolBar m_wndToolBar;
	CToolBar m_wndKoordBar;
	CToolBar m_wndForceBar;
	CToolBar m_wndResultBar;
	CChildView m_wndView;
	Localization::LocalizationObserver *m_pLocalizationObserver;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_MAINFRM_H__F1248247_FA01_11D4_86F7_5254AB1A2D1D__INCLUDED_)
