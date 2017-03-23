#include "stdafx.h"
#include "BandOp.h"
#include "fem2d.h"

namespace Solver
{

BandOp::BandOp( int iEleKn, int numberOfElements, const InzidenzStack &rInz, int numberOfDOF ) :
	m_iBandWidth( -1 ),
	m_iEleKn( iEleKn ),
	m_iNumberOfElements( numberOfElements ),
	m_rInz( rInz ),
	m_iNumberOfDOF( numberOfDOF )
{
	// empty
}

BandOp::~BandOp()
{
}

bool BandOp::start()
{
	InzidenzStack EleKnoInz;	
	

	// Initialisiere Inzidenz-Objekt
	for ( int i=1; i<= m_iEleKn; i++)
		EleKnoInz.addInz(i, 0 );

	int s = 0;
	for ( int i=1; i<= m_iNumberOfElements; i++ ) 
	{
		int r=0;
		// Ermittlung der einzelnen Element-Inzidenztabelle zur Berechnung der Differenz
		for ( int j=1; j<m_iEleKn+1; j++ ) 
		{	
			r++;		
			s++;
			int InzRead = m_rInz.ReadInz( s );
			EleKnoInz.SetInz( r, InzRead );
		}

		for ( int j=1; j<m_iEleKn+1; j++ )
		{
			for ( int k=j; k<m_iEleKn+1; k++ ) 
			{
				// Calculating difference between the maximum node-numbers
				int iDiff = abs( EleKnoInz.ReadInz( j ) - (EleKnoInz.ReadInz( k ) ) );
				// If an greater value was calculated, save it
				if ( iDiff > m_iBandWidth ) 
					m_iBandWidth = iDiff;
			}
		}
	}
	// Calc bandwidth of matrix
	m_iBandWidth = (m_iBandWidth + 1) * m_iNumberOfDOF;

	return true;

}

int BandOp::getBandWitdh() const
{
	return this->m_iBandWidth;
}

} // Namespace Solver
