/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "NodeStack.h"

using namespace std;
using namespace FEStructure;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Externe Variablen und Klassen
/////////////////////////////////////////////////////////////////////////////////////////////////
extern int				iEleNr, iKnNr, iMatNr;
extern struct			tm *pTimeNow;		// Momentanes Datum

extern NodeStack		g_NodeStack;
extern ElementStack		ElementEingabe;
extern MaterialStack	MaterialEingabe;
extern LastStack		LastEingabe;
extern Tragwerk			MyTragwerk;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::Tragwerk()
// Beschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
Tragwerk::Tragwerk()
{
	iNodeNr			= 0;
	iMaterialNr		= 0;
	iElementNr		= 0;
	iLastNr			= 0;
	iLagerKno		= 0;
	iFG				= 0;
	iCalcOption		= 0;

	Org.x			= 0;
	Org.y			= 0;

	bCalc			= FALSE;
	bMove			= FALSE;
	bDef			= FALSE;
	bM				= FALSE;
	bQ				= FALSE;
	bN				= FALSE;
	bSave			= FALSE;
	bFlag			= TRUE;
	bKnNr			= TRUE;
	bEleNr			= TRUE;
	bLogfile		= FALSE;
	
	dPl				= 0;
	dTScale			= 1;
	dDefScale		= 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::Tragwerk()
// Beschreibung	: Destruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
Tragwerk::~Tragwerk()
{
	// Leerer Destruktor
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::SetOrg
// Beschreibung	: Setzt den neuen Koordinatenursprung
/////////////////////////////////////////////////////////////////////////////////////////////////
void Tragwerk::SetOrg(CPoint newOrg)
{
	Org = newOrg;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::ScaleAdd()
// Beschreibung	: Zähl den Skalierungsfaktor um 0.1 hoch
/////////////////////////////////////////////////////////////////////////////////////////////////
void Tragwerk::ScaleAdd()
{
	dTScale = dTScale + 4.0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::ScaleSub()
// Beschreibung	: Zähl den Skalierungsfaktor um 0.1 runter
/////////////////////////////////////////////////////////////////////////////////////////////////
void Tragwerk::ScaleSub()
{
	dTScale = dTScale - 4.0;
	if (dTScale<0) 
		dTScale = 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::ScaleSet()
// Beschreibung	: Setzt den Skalierungsfaktor für das Tragwerk
// Parameter
// dS			: Wert für den Tragwerksskalierungs-Faktor
/////////////////////////////////////////////////////////////////////////////////////////////////
void Tragwerk::ScaleSet(double dS)
{
	dTScale = dS;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::GetScale()
// Beschreibung	: Gibt den Skalierungswert zurück
/////////////////////////////////////////////////////////////////////////////////////////////////
double Tragwerk::GetScale(void)
{
	return dTScale;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::LagerKnoSet()
// Beschreibung	: Setzt den Wert der gelagerten Knoten
/////////////////////////////////////////////////////////////////////////////////////////////////
void Tragwerk::LagerKnoSet(int iLK)
{
	iLagerKno = iLK;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::GetFlag()
// Beschreibung	: Gibt den bFlag zurück
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL Tragwerk::GetFlag(void)
{
	return bFlag;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::meshElement()
// Beschreibung	: Routine zur Vernetzung der Balken, ohne jedes einzelne Element eingeben zu müssen
// Parameter
// Kn1			: Knoten 1 
// nKn2			: Knoten 2
// nNrEle		: Anzah der Elemente (zum Vernetzen)
// nKnr			: Anzahl der vorhandenen Knoten
// nMNr			: Materialnummer des Querschnittes des zu vernetzenden Bereichs
// nArt			: Art des Elementes
// nGesEleq		: Gesamte Anzahl der Elemente
/////////////////////////////////////////////////////////////////////////////////////////////////
void Tragwerk::meshElement(int iKn1, int iKn2, int iNrEle, int iMNr, int iArt )
{
	if ( 0 == iNrEle )
		return;
	
	NodeStack::NodeDef node1, node2;
	g_NodeStack.getNode( iKn1, node1 );
	g_NodeStack.getNode( iKn2, node2 );

	Core::d32 dX1, dY1, dX2, dY2;
	node1.getPosition( dX1, dY1 );
	node2.getPosition( dX2, dY2 );
	
	const Core::d32 dStepx = (dX2 - dX1) / iNrEle;
	const Core::d32 dStepy = (dY2 - dY1) / iNrEle;
	Core::d32 dNeux = dX1;
	Core::d32 dNeuy = dY1;
	Core::i32 temp = iKn1;

	for ( Core::i32 i=1; i<iNrEle; i++) 
	{
		iKnNr++;
		dNeux += dStepx;
		dNeuy += dStepy;
		g_NodeStack.addNode( iKnNr, dNeux, dNeuy, 0, iKnNr, 0, iKnNr, 0, iKnNr );
		
		// Anlegen eines neuen Elementes
		iEleNr++;
		if ((iArt==3)&&(i==1)) 
		{
			ElementEingabe.addElement(iEleNr, temp, iKnNr, iMNr, 3);
			temp = iKnNr;
		}
		else 
		{
			ElementEingabe.addElement(iEleNr, temp, iKnNr, iMNr, 2);
			temp = iKnNr;
		}
	}
	// Anlegen des letzten Elementes
	iEleNr++;
	// Wenn Gelenk am letzten Knoten
	if ( 4 == iArt)
		ElementEingabe.addElement(iEleNr, iKnNr, iKn2, iMNr, 4);
	else
		ElementEingabe.addElement(iEleNr, iKnNr, iKn2, iMNr, iArt);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::LoadTragwerk(const char *lpLoadName, const char *lpPathName)
// Beschreibung	: Die Methode lädt Tragwerksdaten aus einem File
// Parameter
// *lpLoadName	: Name der file
// *lpPathName	: Pfad der file
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL Tragwerk::LoadTragwerk( const char *lpLoadName )
{
	int			iWert, iI1, iN1, iN2, iMat, iArt, iXh, iYh,iZh, iLagerKno, iGel;
	double		dX, dY, dEM, dA, dIy, dFx, dFy, dMy, dMpl;
	ifstream	file(lpLoadName);
	
	if (!file)
		return FALSE;

	std::string materialName( "" );
	file >> iWert;
	file >> iLagerKno;
	MyTragwerk.iLagerKno = iLagerKno;	
	if (iWert>0) 
	{
		for (iI1=1; iI1<iWert+1; iI1++) 
		{
			iKnNr++;
			file >> dX;
			file >> dY;
			//KoordEingabe.addKoord(dX, dY, iI1);
			file >> iXh;
			file >> iYh;
			file >> iZh;
			g_NodeStack.addNode( iI1, dX, dY, iXh, iI1, iYh, iI1, iZh, iI1 );

			//KoordEingabe.SetRandbed(iI1, iXh, iYh, iZh);
		}
	}
	
	file >> iWert;
	if ( iWert > 0 ) 
	{
		for (iI1=1; iI1<iWert+1; iI1++) 
		{
			Core::c8 buffer[512];
			iMatNr++;
			file >> buffer;
			file >> dEM;
			file >> dA;
			file >> dIy;
			file >> dMpl;
			materialName = buffer;
			MaterialEingabe.addMaterial( materialName, iI1, dEM, dA, dIy, dMpl );
		}
	}
		
	file >> iWert;
	if ( iWert > 0 ) 
	{
		for (iI1=1; iI1<iWert+1; iI1++) 
		{
			iEleNr++;
			file >> iN1;
			file >> iN2;
			file >> iMat;
			file >> iArt;
			file >> iGel;
			ElementEingabe.addElement( iI1, iN1, iN2, iMat, iArt );
		}
	}
		
	file >> iWert;
	if (iWert>0) {
		for (iI1=1; iI1<=iWert; iI1++) {
			file >> iN1;				
			file >> dFx;
			file >> dFy;
			file >> dMy;
			LastEingabe.addLast(iN1, dFx, dFy, dMy, 1);
		}
	}

	
	file.close();
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::SaveTragwerk(const char *lpSaveName, const char *lpPathName)
// Beschreibung	: Speichert das Tragwerk in ein file
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL Tragwerk::SaveTragwerk( const char *lpSaveName )
{
	assert( NULL != lpSaveName );
	int      iI1, iI2, iW, iH, iLastNr = LastEingabe.iLastNr;
	int      iLagerNr = MyTragwerk.iLagerKno;
	double   dW=0;
	ofstream file( lpSaveName );

	if ( !file.is_open() )
		return FALSE;
	
	if (iKnNr<=0)
		file << 0 << endl;	
	else 
	{
		file << iKnNr << endl;
		file << iLagerNr << endl;
		for (iI1=1; iI1<=iKnNr; iI1++) 
		{
			NodeStack::NodeDef node;
			g_NodeStack.getNode( iI1, node );
			for (iI2=1; iI2<=2; iI2++) 
			{
				dW = node.getPos( (Node<Core::d32>::Direction) iI2 );
				//dW = KoordEingabe.ReadKoord(iI1, iI2);
				file << dW << endl;
			}
			std::vector<Core::d32> holds;
			std::vector<Core::i32> ids;
			node.getBoundaryConditions( holds, ids );
			for (iI2=1; iI2<=3; iI2++) 
			{
				iH = ( Core::i32 ) holds[ iI2-1];
				//iH = KoordEingabe.ReadRandbed(iI1, iI2);
				file << iH << endl;
			}
		}
	}
	if (iMatNr<=0)
		file << 0 << endl;
	else 
	{
		file << iMatNr << endl;
		for (iI1=1; iI1<=iMatNr; iI1++) 
		{
			std::string materialName( "" );
			Core::d32 eModule( 0.0 ), area( 0.0 ), Iy( 0.0 ), mPlas( 0.0 );
			MaterialEingabe.readMaterial( iI1, materialName, eModule, area, Iy, mPlas );
			file << materialName.c_str() << endl;
			file << eModule << endl;
			file << area << endl;
			file << Iy << endl;
			file << mPlas << endl;
			/*for ( iI2=1; iI2<=4; iI2++ ) 
			{
				dW = MaterialEingabe.ReadMaterial(iI1, iI2);
				file << dW << endl;
			}*/
		}
	}

	if (iEleNr<=0)
		file << 0 << endl;
	else 
	{
		file << iEleNr << endl;
		for (iI1=1; iI1<=iEleNr; iI1++) 
		{
			for (iI2=1; iI2<=5; iI2++) 
			{
				iW = ElementEingabe.ReadElement(iI1, iI2, iEleNr);
				file << iW << endl;
			}
		}
	}

	if( iLastNr<=0 )
		file << 0 << endl;
	else 
	{
		file << iLastNr << endl;
		for (iI1=1; iI1<=iLastNr; iI1++) 
		{
			for (iI2=1; iI2<=4; iI2++)
			{
				file << LastEingabe.readLast( iI1, iI2 ) << endl;
			}
		}
	}
	file.close();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Tragwerk::SaveErgebnis()
// beschreibung	: Sichert das Ergebnis tabellarisch in der file lpPathName
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL Tragwerk::SaveCalc( Vektor Deform, Vektor MW, Vektor QW, Vektor LW, const char *lpSaveName )
{
	int	     iI1, iI2, iStep, iPos;
	double	 dW[3];
	ofstream file(lpSaveName);
	
	if ( !Math::GetDate() )
		TRACE0("Fehler bei Berechnung des Datums!\n");

	const Core::i32 iAnz = g_NodeStack.getNumberOfNodes();
	//iAnz = KoordEingabe.iAnz;
	
	if (!file)
		return FALSE;
	else {
		iStep = (Deform.iAnz/iFG);
		file << "Problem	: " << lpSaveName << endl;
		file << "Datum		: " << pTimeNow->tm_mday << "." << pTimeNow->tm_mon << "." << pTimeNow->tm_year <<endl;
		file << endl;
		file << "Durchbiegungen:" << endl;
		file << Linie << endl;

		
		iPos = 0;
		for (iI1=1; iI1<=iAnz; iI1++) {
			for (iI2=0; iI2<iFG; iI2++) {
				iPos++;
				dW[iI2] = Deform.readVektor(iPos);
			}
			file << "Koordinate: " << iI1 << "	Xdef: " << dW[0] << "		Ydef: " << dW[1] << "		Zdef: " << dW[2] << endl;
		}
		file << endl << endl;
		file << "Moment:" << endl;
		file << Linie << endl;
		
		iPos = 0;
		iStep = ElementEingabe.numberOfElements();
		for (iI1=1; iI1<=iStep; iI1++)
		{
			for (iI2=1; iI2<=2; iI2++) 
			{
				iPos++;
				dW[iI2-1] = MW.readVektor(iPos);
			}
	
			file << "Element:" << iI1 << "		Kn1: " <<dW[0] << "		Kn2:" << dW[1] << endl;
		}

		iPos = 0;
		file << endl << endl;
		file << "Querkraft: " << endl;
		file << Linie << endl;
		for (iI1=1; iI1<=iStep; iI1++) 
		{
			for (iI2=1; iI2<=2; iI2++) 
			{
				iPos++;
				dW[iI2-1] = QW.readVektor(iPos);
			}

			file << "Element: " << iI1 << "		Kn1: " << dW[0] << "	Kn2: " << dW[1] << endl;
		}

		iPos = 0;
		file << endl << endl;
		file << "Laengskraft: " << endl;
		file << Linie << endl;
		for (iI1=1; iI1<=iStep; iI1++) {
			for (iI2=1; iI2<=2; iI2++) {
				iPos++;
				dW[iI2-1] = LW.readVektor(iPos);
			}
			file << "Element:" << iI1 << "		Kn1: " << dW[0] << "		Kn2: " << dW[1] << endl;
		}
		file.close();

		return TRUE;
	}

}
