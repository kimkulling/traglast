/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ELEMENT_BERECHNEN__H
#define __ELEMENT_BERECHNEN__H

Vektor Fachwerk(double emodul, double flaeche, double x1, double x2, double y1, double y2,
					 Vektor K);
Vektor Balken(double emodul, double flaeche, double iy, double x1, double x2, double y1,
					double y2);
Vektor BalkenGelenk(int nPos, double dX1, double dX2, double dY1, double dY2, double dEM,
						 double dA, double dIy);
void   CalcMoment(double *dDef, double dK1[2], double dK2[2], double dL, double dEM, 
				  double dIy, double *dM);
void   CalcQuer (double *dDef, double dK1[2], double dK2[2], double dL, double dEM, 
				 double dIy, double *dQ);
void   CalcLaeng (double *dDef, double dK1[2], double dK2[2], double dL, 
				  double dEM, double dA, double *dN);
void   CalcMomentGelenk (double *dDef, double dK1[2], double dK2[2], double dL, 
					   double dEm, double dIy, double *dM, int iArt);
void   CalcQuerGelenk (double *dDef, double dK1[2], double dK2[2], double dL, 
					 double dEm, double dIy, double *dQ, int iArt);
void   TransformDeform (double *dDef, double dCx, double dCy, double *dTrans, int iT);

#endif