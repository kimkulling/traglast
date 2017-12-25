/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : Vector.cpp
// Desc.       : Implementation of class vector
// Autor       : Kim Kulling
// Last mod.   : 09.01.2004
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace Core;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Vektor::Vektor()
// Beschreibung	: Konstruktor der Klasse Vektor
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor::Vektor()
: m_dVector( 0.0 )
, m_data( nullptr )
, m_dScaleX( 0.0 )
, m_dScaleY( 0.0 )
, m_size( 0U )
, m_dMaxV( 0.0 )
, m_dMinV( 0.0 )
, m_changed( false ) {
    //  empty
}

void Vektor::initVector(int numItems )  {
	if ( numItems < 1)
		return;

	if ( numItems ==1) {
		m_dVector = 0.0;
        return;
	}

    m_size = numItems;
    m_data = new double[ numItems ];
	::memset( m_data, 0, sizeof(double) * numItems );
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : Vektor::Size(void)
// Desc.  : Returns size of vector
// Parameters
//   Returns number of entries
/////////////////////////////////////////////////////////////////////////////////////////////////
i32 Vektor::Size()
{
	return m_size;
}

bool Vektor::isEmpty() const {
    return ( 0 == m_size );
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: VektorStack::addVektor(double W, int Pos)
// Beschreibung	: Fügt einen neuen Listeneintrag ans Ende des Stacks hinzu
// Parameter
// dW					: Wert, der eingetragen wird
// iPos					: POsiion in der Liste
/////////////////////////////////////////////////////////////////////////////////////////////////
int Vektor::addVektor(const double dWert)
{
	int    i=0;
	double *tmp=NULL;
	
	++m_size;
	if ( m_size ==1) {
		m_dVector    = dWert;
		m_changed = true;

		return ErrorHandler::WT_OK;
	}

	if ((tmp = new double[m_size])==NULL)
		return ErrorHandler::WT_FATAL_ERR;
	
	for (i=0; i<m_size; i++)
		tmp[i] = m_data[i];	

	tmp[ m_size -1] = dWert;
	delete [] m_data;
    m_data = nullptr;

	
	for (i=0; i<m_size; i++)
        m_data[i] = tmp[i];

	if (!m_size )
		return ErrorHandler::WT_FATAL_ERR;

	if ( m_size>1)
		delete [] tmp;
	else 
		delete tmp;

	m_changed = true;

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : Vektor::GetBlock(int iNum, iStart, double *pBlock)
// Desc.  : 
/////////////////////////////////////////////////////////////////////////////////////////////////
int Vektor::GetBlock(int iNum, int iStart, double *pBlock)
{
	int iIndex;

	if (pBlock==NULL)
		return ErrorHandler::WT_ERR;

	iIndex = iStart * iNum;

	if (iIndex>m_size )
		return ErrorHandler::WT_ERR;
	
	memcpy(pBlock, m_data, sizeof(double) * iIndex);

	return ErrorHandler::WT_OK;
}

int Vektor::delVektor(int iPos) {
	if (iPos<1 || m_data == nullptr )
		return ErrorHandler::WT_ERR;

	// Delete thee vector, if its possible
	int diff = m_size - iPos;
	if (diff>0) {
		for (int i=(iPos-1); i<m_size; i++) {
			if (i<( m_size -1))
                m_data[i] = m_data[i+1];
			if (i==( m_size -1))
				delete &m_data[i];
		}
		m_changed = true;
		
		return ErrorHandler::WT_OK;
	}		

	return ErrorHandler::WT_ERR;	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: VektorStack::setVektor(int iPos, double dW)
// Beschreibung	: Ersetzt den Wert an der angegebenen Position in der Liste um den 
//						übergebenen
// Parameter
// iPos			: Position des zu ersetzenden Wertes
// dW			: Neuer Wert
/////////////////////////////////////////////////////////////////////////////////////////////////
int Vektor::setVektor(int iPos, double dW)
{
	if ( m_data ==NULL)
		return FALSE;
	
	m_changed = TRUE;
	if ( m_size ==1)
	{
		m_dVector = dW;
		return TRUE;
	}
	
    m_data[iPos-1] = dW;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : Vektor::SetBlock(int iNum, int iStart, double *pBlock)
// Desc   :
/////////////////////////////////////////////////////////////////////////////////////////////////
int Vektor::SetBlock(int iNum, int iStart, double *pBlock)
{
	if (pBlock==NULL || iNum==0 || iStart<0)
		return ErrorHandler::WT_FATAL_ERR;
	
	int iIndex=0;
	iIndex = iNum + iStart;
	if (iIndex>m_size )
		return ErrorHandler::WT_FATAL_ERR;
	
	if (memcpy( m_data, pBlock, sizeof(double) * iNum) == NULL)
		return ErrorHandler::WT_FATAL_ERR;

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : VektorStack::Getmax(int iFG, int iArt)
// Desc   : Methode, die die maximalen Werte aus der Liste ausliest
// 
// --> iFG  : Maximaler Freiheitsgrad der Knoten
// --> iArt : 1, 2->Rückgabe nach FG; 3->Einfache Rückgabe
// <-- 
/////////////////////////////////////////////////////////////////////////////////////////////////
double Vektor::Getmax(int iFG, int iArt)
{
	int    iIn1, iIn2, iI;
	double *pIndex = m_data,dTempX=0, dTempY=0, dMax = 0;

	iI = 0;
	if (pIndex!=NULL) {
		if ( m_changed ) {
			for (iIn1=1; iIn1<=( m_size /iFG); iIn1++) {
				for (iIn2=1; iIn2<=iFG; iIn2++) {
					if ((pIndex[iI]<dTempX) && (iIn2==1) )
						dTempX = pIndex[iI];
					if ((pIndex[iI]<dTempY) && (iIn2==2) )
						dTempY = pIndex[iI];
					if (dMax < pIndex[iI])
						dMax = pIndex[iI];
					iI++;
				}
			}

			// Caching the calculated values
            m_dMaxV = dMax;
            m_changed = false;
		}
		switch (iArt) 
		{
			case 1:  
				return dTempX;
			case 2:  
				return dTempY;
			case 3:  
				return m_dMaxV;
			default: 
				return 0;
			
		}
	}

	return ErrorHandler::WT_FATAL_ERR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: VektorStack::Getmin(int iFG, int iArt)
// Beschreibung	: Liest den minimalen Wert aus der Liste aus
// Parameter
// iFG			: Maximaler Freiheitsgrad eines Knotens
// iArt			: Art der Rückgabe (1->sortiert nach FG; 2->Minimaler Wert nicht sortiert)
// Rückgabewert	: Minimaler Wert aus der Liste
/////////////////////////////////////////////////////////////////////////////////////////////////
double Vektor::Getmin(int iFG, int iArt)
{
	double	*pIndex = m_data, dTempX=0, dTempY=0, dMin = 0;
	int		iIn1, iIn2, iI = 0;
	
	if (pIndex==NULL)
		return (double) 0.0;

	
	for (iIn1=1; iIn1<=(m_size/iFG); ++iIn1) 
	{
		for (iIn2=1; iIn2<=iFG; iIn2++) 
		{
			if ((dTempX>pIndex[iI])&&(iIn2==1))
				dTempX = pIndex[iI];
			if ((dTempY>pIndex[iI])&&(iIn2==2))
				dTempY = pIndex[iI];
			if (dMin>pIndex[iI])
				dMin = pIndex[iI];
			++iI;
		}
	}
	// Return wanted value
	switch (iArt)
	{
		case 1:  
			return dTempX;
		case 2:  
			return dTempY;
		case 3: 
			return dMin;
		default: 
			break;
	}
	
	return (double) ErrorHandler::WT_FATAL_ERR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: VektorStack::SortVektor(int iArt)
// Beschreibung	: Sortiert den Vektor auf- oder absteigend nach dem Selectionsort-Verfahren
// Parameter
// iArt			: Art der Sortierung (1->Max/2->Mn)
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL Vektor::SortVektor(int iArt)
{
	int    iI1, iI2, iMin;
	double dWert = 0;

	for (iI1=1; iI1<( m_size -1); iI1++)
	{
		iMin = iI1;
		for (iI2=1; iI2<m_size; iI2++)
		{
			if (iArt==1) 
			{
				if (readVektor(iI2) < readVektor(iMin))
					iMin = iI2;
			}

			if (iArt==2) 
			{
				if (readVektor(iI2) > readVektor(iMin))
					iMin = iI2;
			}
		}
		dWert = readVektor(iMin);
		setVektor(iMin, (readVektor(iI1)));
		setVektor(iI1, dWert);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: VektorStack::LoadVektor(const char *lpLoadName)
// Beschreibung	: Lädt einen Vektoraus einer Datei
// Parameter
// lpLoadName	: Name der Eingabedatei
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL Vektor::LoadVektor(const char *lpLoadName)
{
	int iW, iI1;
	double dW;

	ifstream datei(lpLoadName);

	if (!datei)
		return FALSE;
	else 
	{
		datei >> iW;
		if (iW>0) 
		{
			for (iI1=1; iI1<=iW; iI1++) 
			{
				datei >> iW;
				datei >> dW;
				addVektor(dW);
			}
		}
		datei.close();

		return TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: VektorStack::SaveVektor(const char *lpSaveName, int iAnz)
// Beschreibung	: Speicher einen Vektor in eine Datei
// Parameter
// lpSaveName	: Name der Ausgabe-Datei
// iAnz			: Anzahl der zu sichernen Werte
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL Vektor::SaveVektor(const char *lpSaveName, int iAnz)
{
	double	*pWork = m_data;
	int		iI;

	ofstream Datei(lpSaveName);

	if (!Datei)
		return FALSE;
	else {
		if (iAnz==0)
			Datei << 0;
		else {
			for (iI=0; iI<iAnz; iI++) {
				Datei << (iI+1) << endl;
				Datei << pWork[iI] << endl;
			}
		}
		Datei.close();

		return TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: VektorStack::DelList(void)
// Beschreibung	: Löscht die eingetragene Liste der Klasse
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL Vektor::DelList()
{
	double *pIndex = m_data;

	if (pIndex!=nullptr) {
        m_data = NULL;
        m_size = 0;
		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : Vektor::InitVector(int iLower, int iUpper)
// Desc.  : 
/////////////////////////////////////////////////////////////////////////////////////////////////
int Vektor::InitVector(int iLower, int iUpper)
{
	if (m_data==NULL)
		return ErrorHandler::WT_OK;

	if (iLower<0 || iUpper>m_size || iLower>iUpper)
		return ErrorHandler::WT_ERR;

	int iWidth = iUpper - iLower;
	if (iWidth<0)
		return ErrorHandler::WT_ERR;

	double *pTemp = new double[iWidth];
	if (pTemp==NULL)
		return ErrorHandler::WT_OUT_OF_MEM;

	memcpy( m_data + iLower, pTemp, sizeof(double) * iWidth);

	delete [] pTemp;

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: VektorStack:~VektorStack
// Beschreibung	: Destruktor der Klasse VektorStack
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor::~Vektor()
{
	if (NULL != m_data ) {
/*		if (Size()>1)
			delete [] pVektor;
		else
			delete pVektor;

		pVektor = NULL;*/
	}
	return;
}
