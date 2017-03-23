// PlastCalcCtrl.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Win_Traglast.h"
#include "PlastCalcCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Tragwerk MyTragwerk;

CString strPlastName;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPlastCalcCtrl 


CPlastCalcCtrl::CPlastCalcCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CPlastCalcCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlastCalcCtrl)
	m_strPlastName = _T("");
	//}}AFX_DATA_INIT
}


void CPlastCalcCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlastCalcCtrl)
	DDX_Text(pDX, IDC_EDIT2, m_strPlastName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlastCalcCtrl, CDialog)
	//{{AFX_MSG_MAP(CPlastCalcCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------------------
// Behandlungsroutinen für Nachrichten CPlastCalcCtrl 

//-----------------------------------------------------------------------------------------------
// Methode		: CPlastCalcCtrl::OnOK()
//-----------------------------------------------------------------------------------------------

void CPlastCalcCtrl::OnOK() 
{
	BOOL bFlag = TRUE;
	CString strError;
	UpdateData(TRUE);

	if (m_strPlastName.GetLength()<2)
	{
		strError.Format("Bitte Namen für die AUsgabedatei eingeben!");
		bFlag = FALSE;
	}

	if (bFlag)
	{
		CDialog::OnOK();
	}
	else
		AfxMessageBox(strError);
}
