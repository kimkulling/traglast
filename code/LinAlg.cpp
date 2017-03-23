/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : LinAlg.cpp
// Desc.       : Implementations of functions for linear algos
// Author      : Kim Kulling
// Last mod.   : 13.12.2003
// Comments    : 
//
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>

extern bool bPosDef;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: MatSyVek(int n, int Bandbreite, VektorStack A, 
//					VektorStack B, VektorStack C)
// Beschreibung	: Funktion zur Multiplikation einer 2D-Matrix mit einem Vektor 
// Parameter
// n			: n x n-Matrix
// Bandbreite	: Bandbreite der Matrix
// Vektor A		: 2D-Matrix als Band-Matrix gesichert
// Vektor B		: 1D-Matrix	als Band-Matrix gesichert
// Rückgabewert	: VektorStack
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor MatSyVek(const int n, const int Bandbreite, Vektor A, Vektor B, Vektor C)
{
	int    i, j, iUntereGrenze=9999999, iObereGrenze=-1, m, k, ii, jj;
	double dWert1, dWert2, dSumme;

	ii=0;
	for (i=0; i<=n; i++) {
		dSumme = 0; 
		jj = 0;
		ii = ii+ Bandbreite;
		iUntereGrenze = 1;
		if (i>(Bandbreite-1)) {
			jj = -Bandbreite;
			iUntereGrenze = i-Bandbreite+1;
			for (m=Bandbreite; m<=i; m++) 
				jj=jj+Bandbreite;
		}
		
		for (j=iUntereGrenze; j<=(i-1); j++) {
			jj     = jj+Bandbreite;
			k      = i+jj-j-Bandbreite+1;
			dWert1 = A.readVektor(k); 
			dWert2 = B.readVektor(j);
			dSumme = dSumme+(dWert1*dWert2);
		}
		if (i<=(n-Bandbreite+1))
			iObereGrenze=n;
		
		for (j=i; j<=iObereGrenze; j++) {
			k      = j+ii-i-Bandbreite+1;
			dWert1 = A.readVektor(k); 
			dWert2 = B.readVektor(j);
			dSumme = dSumme + (dWert1 * dWert2);
			C.addVektor(dSumme);
		}	
	}

	return C;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function		: RMatRMat 
// Beschreibung	: Multipliziert die Rechteckmatrix R mit ihrer Transponierten
// Parameter
// R			: n mal Bandbreite des Vektors
// n			: Breite der Steifigkeitsmarix
// Rückgabewert	: R
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor RMatRMat(Vektor R, int n)
{
	int    ii, jj, p, p1, p2,i, j, k;
	double dSumme;
	
	p=0;
	for ( i=1; i<=n; ++i )
	{
		ii=p+1;
		jj=0;
		for ( k=i; k<=n; ++k ) 
		{
			p++;
			p1=p;
			p2=ii+jj;
			dSumme = 0;
			for (j=k; j<=n; j++) {
				jj++;
				dSumme = dSumme + (R.readVektor(p1) * R.readVektor(p2));
				p1++;
				p2++;
			}
			R.setVektor(p,dSumme);
		}
	}

	return R;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: Cholesky
// Beschreibung	: Eine symmetrische Steifigkeitsmatrix A wird in 2 Matrizen 
//				  L und R zerlegt, so daß gilt: A = L x R
// Parameter
// Bandbreite	: Bandbreite der Matrix
// A			: Liste der Elemente der Matrix A vom Typ VektorStack
// Positivdef	: Flag, welches negativ wird, wenn die Matrix A singulär ist
// n			: Breite der Matrix A (n x m)
// Rückgabewert	: 
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor Cholesky(const int n, const int Bandbreite, Vektor A )
{
	int     ii, jj, p, p1, p2, Grenze, iNum_A,  i, j, k, len;
	double  val1, val2, val3, val4, Divisor, *pA;
	Vektor  temp;

	pA     = NULL;
	len    = 0;
	iNum_A = A.Size();

	// Allocating memory
	pA = new double[ iNum_A ];

	// Copy matrix into allocated block A
	A.GetBlock(iNum_A, 1, pA);

	Grenze = Bandbreite - 1; 
	ii     = 1 - Bandbreite;
	for (i=1; i<n+1; ++i) 
	{
		ii   += Bandbreite;
		val1  = pA[ii-1];
				
		if (val1<=POSITIV) 
		{
			bPosDef = false;
			break;
		}
		
		bPosDef  = true;
		val1     = pA[ii-1];
		pA[ii-1] = sqrt(val1);
		if (i>(n - Bandbreite + 1)) 
			Grenze = n - i;
		
		for (k=(ii+1); k<(ii + Grenze + 1); ++k) {
			Divisor = pA[ii-1];
			val1    = pA[k-1];
			val1    = val1 / Divisor;
			pA[k-1] = val1;
		}
		
		// Init vector
		int iLower(9999999), iUpper(-999999);
		iLower = ii + Grenze+1;
		iUpper = ii + Bandbreite-1;
		A.InitVector(iLower, iUpper);

		jj=0;
		for (j=1; j<Grenze+1; ++j) 
		{
			jj = jj + Bandbreite;
			for (k=0; k<(Grenze - j + 1); ++k) 
			{
				p       = ii + jj + k;
				p1      = ii + j;
				p2      = ii + j + k;
				val1    = pA[p-1];
				val2    = pA[p1-1];
				val3    = pA[p2-1];
				val4    = val1 - (val2 * val3);
				pA[p-1] = val4;				
			}
		}
	}
	
	// Copy block back to instance
	A.SetBlock(iNum_A,0,pA);
	delete [] pA;

	return A;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: VorRueck(int n, int Bandbreite, VektorStack A, VektorStack B)
// Beschreibung	: Das Gleichungssystem A x = B wird gelöst. Dabei ist A eine durch 
//					die Funktion Cholesky in eine zerlegte positiv definierte symmetrische 
//					Bandmatrix zerlegt. Der Lösungsvektor steht auf B. D
//					Die rechte Seite geht dabei verloren.
// Parameter
// n			: Dimension der symmetrischen Bandmatrix
// Bandbreite	: Bandbreite der symmetrischen Bandmatrix
// A			: Bandmatrix
// B			: Vektor B
// Rückgabewert	: Lösungsvektor, in B gespeichert
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor VorRueck(const int n, const int Bandbreite, Vektor A, Vektor B)
{
	int    i, j, k, m, ii, jj, Grenze, iA_No, iB_No;
	double wert1, wert2, wert3, *pA, *pB;
	Vektor temp;

	// Init vars and get size of vectors
	pA    = NULL;
	pB    = NULL;
	iA_No = A.Size();
	iB_No = B.Size();
	
	// Allocate memory
	pA = new double[ iA_No ];
	pB = new double[ iB_No ];
	
	A.GetBlock(iA_No, 1, pA);
	B.GetBlock(iB_No, 1, pB);
	
	// Start calculating
	ii = 1 - Bandbreite;
	for (i=1; i<=n; i++)
	{
		ii += Bandbreite;
		Grenze = 1; 
		jj     = 0;
		if (i>(Bandbreite-1)) 
		{
			jj = -Bandbreite;
			Grenze = i - Bandbreite + 1;
			for (m=Bandbreite; m<=i; m++) 
			{
				jj += Bandbreite;
			}
		}
		
		for (j=Grenze; j<=(i-1); j++) 
		{
			jj    = jj + Bandbreite;
			k     = i + jj - j - Bandbreite + 1;
			wert1 = pB[ i-1 ];
			wert2 = pA[ k-1 ];
			wert3 = pB[ j-1 ];
			pB[ i-1 ] = wert1 - (wert2 * wert3);	
		}

		wert1 = pB[i-1];
		wert2 = pA[ii-1];
		pB[i-1] = wert1 / wert2;
	}

	wert1   = pB[n-1];
	wert2   = pA[ii-1];
	pB[n-1] = wert1/wert2;
	for (i=(n-1); i>=1; --i) 
	{
		ii    -= Bandbreite; 
		Grenze = n;
		if (i<=(n-Bandbreite+1)) 
			Grenze = Bandbreite+i-1;
		for (j=(i+1); j<=Grenze; j++) 
		{
			k     = j + ii - i;
			wert1 = pB[i-1];
			wert2 = pA[k-1];
			wert3 = pB[j-1];
			pB[i-1] = wert1 - (wert2 * wert3);
		}

		wert1   = pB[i-1];
		wert2   = pA[ii-1];
		pB[i-1] = wert1 / wert2;
	}

	// Set incore vector back to old instance
	A.SetBlock(iA_No,0,pA);
	B.SetBlock(iB_No,0,pB);

	delete [] pA;
	pA = NULL;

	delete [] pB;
	pB = NULL;

	return B;
}
