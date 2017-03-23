/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : LinAlg.h
// Desc.       : Prototypes and preprozessor definitions
// Author      : Kim Kulling
// Last mod.   : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __LINEAR_INCLUDED__H
#define __LINEAR_INCLUDED__H

// Funktion prototypes //////////////////////////////////////////////////////////////////////////
Vektor MatSyVek(const int n, const int Bandbreite, Vektor A, Vektor B, Vektor C);
Vektor Cholesky(const int n, const int Bandbreite, Vektor A);
Vektor VorRueck(const int n, const int Bandbreite, Vektor A, Vektor B);

#endif