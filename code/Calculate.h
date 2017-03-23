/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_CALCULATE_H__50FDEEA1_FD35_11D4_86F7_5254AB1A2D1D__INCLUDED_)
#define AFX_CALCULATE_H__50FDEEA1_FD35_11D4_86F7_5254AB1A2D1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CCalculate : public CDialog
{
public:
	CCalculate( CWnd* pParent = NULL );

	enum { IDD = IDD_CALCULATE};
	CString	m_iBand;
	CString	m_strFG;
	CString	m_strKnAnz;
	CString	m_strMem;
	CString	m_strEleAnz;
	CString	m_strProcess;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

protected:
	virtual BOOL OnInitDialog();

	Vektor LinCalc(LastStack Last, int iEleNr, int iLastNr, int iEleKn, int iFGKno,
		int iLagerKno, FEStructure::ElementStack Element);
	void		SchnittKraft(int iEleKn, int iFGKno, Vektor Erg);
	Vektor		PlastCalc();
	void		SaveData();

	virtual void OnOK();
	afx_msg void OnButton2();
	afx_msg void OnButton1();
	DECLARE_MESSAGE_MAP()

private:
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
	CButton m_ButtonOptions;
	CButton m_ButtonClose;
};

#endif // AFX_CALCULATE_H__50FDEEA1_FD35_11D4_86F7_5254AB1A2D1D__INCLUDED_
