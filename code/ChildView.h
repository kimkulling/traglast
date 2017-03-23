//----------------------------------------------------------------------------------------------------------------------
///	\file		ChildView.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of CChildView.
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
#ifndef TL_GUI_CHILDVIEW_H_INC
#define TL_GUI_CHILDVIEW_H_INC

#include "LocalizationObserverSubject.h"

namespace Localization
{
class LocalizationObserver;
}

class CMainFrame;

//----------------------------------------------------------------------------------------------------------------------
///	\class		CChildView
///	\ingroup	GUI
///
///	\brief	IMplements the child view of the application. Controls drawing of the displayed model, 
///	forces and reaction forces.
//----------------------------------------------------------------------------------------------------------------------
class CChildView :	public CWnd,
					public Localization::LocalizationObserverSubject
{
public:
	CChildView();

	// Zeichnet das Koordinatenkreuz
	BOOL KoordDraw(double);
	
	// Methode zum Löschen des Bildschirms
	void ClearScreen();	

	// Zeichnet die Knoten und Nummerierung
	BOOL DrawNodes(void);

	// Zeichnet die Elemente
	BOOL DrawElements(double);

	// Zeichnet die aufgetragene Belastung
	BOOL DrawForce(double);

	// Zeichnet einen Pfeil
	BOOL DrawArrow(double, int, int, int, int, short, short, short);

	// Zeichnet ein Gelenk
	BOOL DrawGelenk(double dX, double dY);							

	// Zeichnet die Durchbiegungen
	BOOL DrawDeform(double dScale, Vektor DeformVektor, InzidenzStack Inz);

	// Zeichnet einen Knoten an der angegebenen Position
	BOOL DrawNode(double dX, double dY);

	// Zeichnet die SChnittkraftFlächen
	BOOL DrawSchnittkraft(Vektor VM, Vektor VQ, Vektor VN); 

	// Anzeige der Mauskoordinaten in der Statusanzeige
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam);
	
	//
	BOOL DrawALL();

	bool onLanguageChange();

// Überladungen
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CChildView();

	// Generierte Funktionen für die Nachrichtentabellen
protected:
//	CCalculate *m_pCalcDlg;

	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void rescaleValue( Core::d32 x, Core::d32 y, Core::d32 &dCx, Core::d32 &dCy );
	void setLocalizedStatusTexts();

private:
	CStatusBar *m_pStatusBar;
	Localization::LocalizationObserver *m_pLocalizationObserver;
	CMainFrame *m_pMainFrame;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // TL_GUI_CHILDVIEW_H_INC
