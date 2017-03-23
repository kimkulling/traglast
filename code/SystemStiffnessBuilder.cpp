#include "stdafx.h"
#include "SystemStiffnessBuilder.h"

namespace Solver
{

//-------------------------------------------------------------------------------------------------
//	Constructor.
SystemStiffnessBuilder::SystemStiffnessBuilder( Core::ui32 numberOfElements, 
											   Core::ui32 numberOfEleNodes, 
											   Core::ui32 numberOfDoF, 
											   Core::ui32 band,
											   InzidenzStack Inz,
											   Vektor eleSteif, 
											   Vektor sysSteif ) :
	m_ElementId( numberOfElements ),
	m_NumberOfEleNodes( numberOfEleNodes ),
	m_numberOfDoF( numberOfDoF ),
	m_Inz( Inz ),
	m_EleSteif( eleSteif ),
	m_SysSteif( sysSteif ),
	m_Band( band )
{
	//	empty
}

//-------------------------------------------------------------------------------------------------
//	Destructor.
SystemStiffnessBuilder::~SystemStiffnessBuilder()
{
	//	empty
}

//-------------------------------------------------------------------------------------------------
//	Starts the operation.
bool SystemStiffnessBuilder::start()
{
	InzidenzStack EleKnoInz, EleInz;
	int           jj,s,p,o,u, r, iVal;
	double        dRes;

	// Berechnung der Elementknoten-Inzidenzmatrix
	for ( Core::ui32 i=1; i<m_NumberOfEleNodes+1; i++ ) 
	{
		const int j    = ( m_ElementId - 1 ) * m_NumberOfEleNodes + i;
		iVal = m_Inz.ReadInz( j );
		EleKnoInz.addInz( i, iVal );
	}
	
	// Calculate whole number of degree of freedoms.
	const Core::i32 FGEle = m_NumberOfEleNodes * m_numberOfDoF;

	// Inizialisierung der Inzidenztabelle zur Speicherung der Freiheitsgrade des Elementes
	EleInz.DeklInz(FGEle);

	// Ermittlung der ElementInzidenzmatrix zur Zuordnung der Freiheitsgrade
	for ( Core::ui32 i=1; i<=m_NumberOfEleNodes; i++ ) 
	{
		s = (EleKnoInz.ReadInz(i) - 1) * m_numberOfDoF;
		p = 1 + (i - 1) * m_numberOfDoF;
		r = 0;
		for ( Core::ui32 k=p; k<=(p + m_numberOfDoF - 1); k++ ) 
		{
			r++;
			dRes = s+r;
			EleInz.SetInz(k,(int) dRes);
		}
	}
	
	o = 0;
	Core::ui32 k = 0;
	for (r=1; r<=FGEle; r++) 
	{
		// Read number of current degree of freedom
		Core::ui32 i  = EleInz.ReadInz( r );	
		jj = 0;
		// Current degree of freedom
		u  = r;					
		for ( s=1; s<=FGEle; s++ )
		{
			int j = EleInz.ReadInz( s );	// Nummer des Freiheitsgrades des jeweiligen Elements
			if (s<r) 
			{
				// Wenn kleiner der gesamten Freiheitsgrade des Elemente
				u  += jj;
				jj = FGEle - s;	
			}
			else 
			{
				o++;
			}

			// Wenn Nummer des weiteren Freiheitsgrades > jeweiligen Freiheitsgrad des Elementes
			if ( ( Core::ui32 ) j >=i )
			{
				Core::ui32 t = (i - 1) * m_Band + j - i + 1;
				if (s<r)
					k = u;
				else
					k = o;
				
				// Add value of local stiffness to global stiffness matrix.
				double dW = m_SysSteif.readVektor( t );
				dRes = dW + m_EleSteif.readVektor( k );
				m_SysSteif.setVektor(t, dRes);
			}
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
//	Returns the sytem stiffness matrix as a vector.
Vektor SystemStiffnessBuilder::getSystemStiffness()
{
	return m_SysSteif;
}

//-------------------------------------------------------------------------------------------------

} // Namespace Solver
