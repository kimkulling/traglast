/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : fem2d.h
// Desc.       : 
// Autor       : Kim Kulling
// Last mod.   : 06.12.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FEM__H
#define __FEM__H

#include "types.h"
#include "ElementStack.h"
#include <vector>
#include <cassert>

namespace FEStructure
{
	
/////////////////////////////////////////////////////////////////////////////////////////////////
///	\class	Koord
///	\brief	Klasse zum Speichern von Koordinaten und Randbedingungen
/////////////////////////////////////////////////////////////////////////////////////////////////
class Koord		// Einzelnder Listeneintrag für Koord
{
public:
	int    Nr;			///< Nummer des Punktes
	double XPos;		///< X-Koordinate
	double YPos;		///< Y-Koordinate
	long   Xhold;		///< In X-Richtung gehalten
	int    NrXhold;		///< Nummer des Freiheitsgrades
	long   Yhold;		///< In Y-Richtung gehalten
	int    NrYhold;		///< Nummer des Freiheitsgrades
	long   Zhold;		///< Um X-Achse gehalten
	int    NrZhold;		///< Nummer des Freiheitsgrades
	Koord *pNext_Koord;	///< Pointer auf die nächsten Koordinatendaten

	// Konstruktor
	Koord(void);
	
	// Destruktor
	~Koord(void);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: KoordSTack
// Beschreibung	: Klasse zum Anlegen einer Liste von Koordinaten
/////////////////////////////////////////////////////////////////////////////////////////////////
class KoordStack
{
private:
	Koord *pKoordAnker;		// Anker der Liste (Beginn der Liste von Variablen)
	Koord *pKoordAktuell;	// Aktuelles Glied der Liste (ohne Bewegung in der Kette Bearbeitung möglich)

public: // Vars
	int iAnz;

public:
	// Konstruktor
	KoordStack();

	// Destruktor
	~KoordStack();

	// Method to get number of coords
	int GetNumber();

	// Eine Koordinate an die Liste anhängen
	void addKoord(double x, double y, int kn);	

	// Koordinateninformationen änder
	void setKoord(double x, double y, int kn, BOOL bX, BOOL bY, BOOL bZ);
	
	// Eine Koordinate aus der Liste löschen
	void delKoord(int nr);
	
	// Gibt die Koordinatennummer zurück
	int CheckKoord(double dX, double dY);
	
	// Koordinate aus der Liste lesen
	double ReadKoord(int nr, int art);	

	// Kleinste X-Koordinate zurückgeben;
	double GetXMin();

	// Größte X-Koordinate zurückgeben
	double GetXMax();

	// Kleinste Y-Koordinate zurückgeben
	double GetYMin();

	// Größter Y-Wert zurückgeben
	double GetYMax();

	// Alle Koordinaten anzeigen
	int ShowKoord(int KnNr);					
	
	// Randbedingungen setzten
	void SetRandbed(int KnNr, int x, int y, int z);
	
	// Randbedingungen lesen
	int ReadRandbed(int KnNr, int art);			
	
	// Funktion zum Lesen von Randbedingungen
	int top(void);

	// Methode zum Löschen der gesamten Liste
	BOOL DelList();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	Lager 
///	\brief	Klasse zum Sichern von eigenen Lagerinformationen
/////////////////////////////////////////////////////////////////////////////////////////////////
class Lager
{
public:
	double Wert;			///< Lagerwert
	int Pos;				///< Position in der Liste
	Lager *pNext_Lager;		///< Pointer auf den nächsten Listeneintrag (wenn keiner vorh., =NULL)
	Lager();				///< Konstruktor
	~Lager();				///< Destruktor
};

/////////////////////////////////////////////////////////////////////////////////////////////////
///	\class	LagerStack
///	\brief	Klasse zum Anlegen von Lagerdaten
/////////////////////////////////////////////////////////////////////////////////////////////////
class LagerStack
{
private:
	Lager *pLagerAnker;			///< Pointer auf den ersten Listeneintrag
	Lager *pLagerAktuell;		///< Pointer auf den momentanen (bzw. zuletzt ausgelesenen) Listeneintrag

public:
	int iAnz;

public:
	///	Konstruktor
	LagerStack();

	///	Destruktor
	~LagerStack();

	///	Methode zum Anfügen eines neuen Lagereintrages in die Liste
	void addLager(double Wert, int Pos);

	///	Methode zum Auslesen eine LAgereintrages aus der Liste
	double readLager(int Pos);

	///	Methode zum Löschen von Lager-Daten
	BOOL delLager(int iPos);

	///	Methode zum Variieren von Lagerdaten
	BOOL setLager(double dWert, int iPos);
	
	///	Methode zum Löschen der Liste
	BOOL DelList();
};


//-------------------------------------------------------------------------------------------------------------------
///	\class	Material
///	\brief	Klasse zum Speichern von Materialdaten.
//-------------------------------------------------------------------------------------------------------------------
class Material
{
public:
	///	Constructor.
	Material();
	///	Destructor.
	~Material();
	///	Sets new material data.
	void setMaterial( Core::i32 matId, const std::string &rName, Core::d32 EModul, Core::d32 A, Core::d32 Iy,Core::d32 plastMoment );
	///	Returns the material id.
	Core::i32 getMatId() const;
	///	Returns the material data.
	void getMaterial( Core::i32 &matId, std::string &rName, Core::d32 &EModul, Core::d32 &A, Core::d32 &Iy, Core::d32 &plastMoment );
	///	Assigns new material.
	void setNextMaterial( Material *pMaterial );
	///	Next material getter.
	Material *getNextMaterial() const;
	///	EModul getter.
	double getEModul() const;
	///	Area getter.
	double getArea() const;
	///	Iy getter.
	double getIy() const;
	///	Plastical moment getter.
	double getPlastMoment() const;
	///	Name setter.
	void setName( const std::string &rName );
	///	Name getter.
	const std::string &getName() const;

private:
	///	Number of material.
	Core::i32 m_MatNummer;
	///	Emodule.
	double m_EModul;
	///	Area of material
	double m_A;
	/// Trägheitsmoment 2.er Ordnug des Elements
	double m_Iy;				
	///	Plastic Moment.
	double m_dMpl;
	///	Name of material.
	std::string m_strMaterialName;
	///	Pointer to next material.
	Material *m_pNext_Material;
};

//-------------------------------------------------------------------------------------------------------------------
//	E modul getter.
inline double Material::getEModul() const
{
	return m_EModul;
}

//-------------------------------------------------------------------------------------------------------------------
//	Area getter.
inline double Material::getArea() const
{
	return m_A;
}

//-------------------------------------------------------------------------------------------------------------------
//	Iy getter.
inline double Material::getIy() const
{
	return m_Iy;
}

//-------------------------------------------------------------------------------------------------------------------
//	Plastical moment getter.
inline double Material::getPlastMoment() const
{
	return m_dMpl;
}

//-------------------------------------------------------------------------------------------------------------------
//	Material name setter.
inline void Material::setName( const std::string &rName )
{
	assert( !rName.empty() );
	m_strMaterialName = rName;
}

//-------------------------------------------------------------------------------------------------------------------
//	Material name getter.
inline const std::string &Material::getName() const
{
	return m_strMaterialName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
///	\class	MaterialStack
///	\brief	Klasse zum Anlegen einer Datenliste von Materialien
/////////////////////////////////////////////////////////////////////////////////////////////////
class MaterialStack
{
public:
	int iAnz;

public: 
	/// Constructor.
	MaterialStack();
	/// Destructor.
	~MaterialStack(void);

	/// Methode zu Hinzufügen eines Materialeintrages
	int addMaterial( const std::string &rMaterialName, int nr, double em, double a, double iy, double dMpl);

	/// Methode zum Löschen eines Materialeintrages
	int DelMaterial(int mnr, int amnr);		
	
	/// Methode zum Modifizieren eines Materials
	int setMaterial(int iMatNr, const std::string &rMaterialName, double dEM, double dA, double dIy, double dMpl);

	/// Methode zum Auslesen der Materialdaten
	double ReadMaterial(int mnr, int art);

	bool readMaterial( Core::i32 matId, std::string &rMaterialName, double &dEM, double &dA, double &dIy, double &dMpl );

	/// Methode zum Anzeigen von Materialeinträgen
	int ShowMaterial(int nr);

	/// Method	
	int GetNumber();

	// Methode zum Löschen der Liste
	int DelList(void);

private:
	Material *getMaterialById( Core::i32 materialId );

private:
	//Material *pMaterialAnker;	///< Pointer auf den ersten Eintrag in der Liste
	//Material *pMaterialAktuell;	///< Pointer auf den aktuellen Eintreg in der Liste
	std::vector<Material*> m_MaterialList;
};
/*
/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: Element
// Beschreibung	: Klasse zum Sicher von Elementdaten
/////////////////////////////////////////////////////////////////////////////////////////////////
class Element
{
public:
	int ElementNr;			// Nummer des Element
	int KnNr1;				// Knotennummer Elementanfang
	int KnNr2;				// Knotennummer Elementende
	int MatNr;				// Materialnummer
	int Balkenart;			// Art des Elementes (1, 2, 3 oder 4)
	Element *pNextElement;	// Pointer auf díe nächsten Elementdaten

	// Constructor
	Element(void);

	// Destructor
	~Element(void);		
};


/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: ElementStack
// Beschreibung	: Klasse zum Anlegen einer Liste von Elementdaten
/////////////////////////////////////////////////////////////////////////////////////////////////
class ElementStack
{
private:
	Element *pElementAnker;		// Erstes Element in der Liste
	Element *pElementAktuell;	// Zeiger auf dem aktuellen Element

protected:
	// empty

public:
	// Number of entries
	int iAnz;

public:
	// Constructor
	ElementStack(void);

	// Method to add an entry 
	void addElement(int EleNr, int n1, int n2, int mat, int art);

	//Method to delete an entry
	BOOL delElement(int iEleNr);

	// Method to modity an entry
	BOOL setElement(int iEleNr, int iKn1, int iKn2, int iMat, int iArt);

	// Method to get the nodenumber, who is connected to an element
	int CheckNode(int iNode, int iArt);

	// Method to dump the elements into the logfile
	void ShowElement(void);

	// Methode zum Auslesen der Elementdaten aus der Liste
	int ReadElement(int Nr, int SWert, int EleNr);

	// Methode zu Löschen der Liste
	BOOL DelList(void);

	// Destruktor
	~ElementStack(void);
};

*/

/////////////////////////////////////////////////////////////////////////////////////////////////
// Class : Tragwerk
// Desc. : Manager of the structure
/////////////////////////////////////////////////////////////////////////////////////////////////
class Tragwerk : public CObject
{
public:	
	// Konstruktor
	Tragwerk(void);
	// Destructor
	~Tragwerk(void);

	// Ursprungskoordinaten neu setzen
	void SetOrg(CPoint);

	// Skalierungsfaktor wird erhöht
	void ScaleAdd();

	// Skalierungsfaktor wird heruntergesetzt
	void ScaleSub();

	// Skalierungsfaktor wird um den angegebenen Wert ersetzt
	void ScaleSet(double);

	// Funktion, die den Skalierungsfaktor zurückgibt
	double GetScale(void);
	
	// Anzahl der gelagerten Knoten wird neu gesetzt
	void LagerKnoSet(int);

	// Funktion gibt Flag für Koordinatenkreuz-Darstellung zurück
	BOOL GetFlag(void);

	// Methode zum Vernetzen einzelner Balken
	void meshElement(int, int, int, int, int );
	
	// Methode zum Renumerieren des Tragwerks
	BOOL Renumber(void);

	// Methode zum Laden der Tragwerksdaten
	BOOL LoadTragwerk( const char *lpLoadName );

	// Methode zum Speichern des Tragwerks
	BOOL SaveTragwerk(const char *lpSaveName );

	// Methode zum Speichern der Ergebnisse in einer Datei
	BOOL SaveCalc(Vektor Deform, Vektor MW, Vektor QW, Vektor LW, const char *lpSaveName );

private:
	double	dDefScale;		// Scaling-factor for deformations

public:
	int		iNodeNr;		// Anzahl von Knoten im Tragwerk
	int		iMaterialNr;	// Anzahl der Materilaien
	int		iElementNr;		// Anzahl von Elementen
	int		iLastNr;		// Anzahl von Lasten
	int		iFG;			// Freiheitsgrade des Tragwerks
	int		iLagerKno;		// Anzahl der gelagerten Knoten;
	int		iCalcOption;	// Art der Berechnung (entweder einfach oder nach Traglastverfahren)
	CPoint	Org;			// Koordinatenursprung in X
	CPoint	Mtemp;			// Zwischenspeicher für Maus-Koordinaten
	double	dPl;			// Berechneter Wert der plastischen Last
	double	dTScale;		// Skalierungsfaktor für das Tragwerk
	BOOL	bCalc;			// Flag, ob bereits berechnet wurde
	BOOL	bMove;			// Flag, ob im ChileView-Fenster bewegt werden kann
	BOOL	bDef;			// Flag, ob die Durchbiegung angezeigt werden soll
	BOOL	bM;				// Flag, ob die Momentenfläche angezeigt werden soll
	BOOL	bQ;				// Flag, ob die Querkraftfläche angezeigt werden soll
	BOOL	bN;				// Flag, ob die Längskraftfläche angezeigt werden soll
	BOOL	bSave;			// Flag, ob das Tragwer bereits gespeichert ist
	BOOL	bFlag;
	BOOL	bKnNr;			// Flag, ob die Knotennummerierung angezeigt werden soll
	BOOL	bEleNr;			// Flag, ob die Elementnummerierung angezeigt werden soll
	BOOL	bLogfile;		// Flag, ob ein Logfile der Berechnung erzeugt werden soll
};

/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: Plot
// Beschreibung	: Klasse zum Sichern von Plotdaten
/////////////////////////////////////////////////////////////////////////////////////////////////
class Plot
{
public:
	int nPos;			// Position des Eintragews
	double dXpos;		// X-Position
	double dYpos;		// Y-Position
	double dXdef;		// Verformung in X
	double dYdef;		// Verformung in Y
	double dRot;		// Rotation um X
	Plot *pNextPlot;	// Pointer auf den nächsten Eintrag (wenn keiner da, Null-Pointer)

	// Constructor
	Plot();

	// Destructor
	~Plot();
};


/////////////////////////////////////////////////////////////////////////////////////////////////
// Class  : PlotStack
// Desc.  : Managing the datas for plotting
/////////////////////////////////////////////////////////////////////////////////////////////////
class PlotStack
{
private:
	Plot *pPlotAnker;		// Pointer auf den Anker
	Plot *pPlotAktuell;		// Pointer auf den momentanen Listeneintrag

public:
	double dScaleX;			// Skalierungsfaktor in X
	double dScaleY;			// Skalierungsfaktor in Y
	int nAnz;				// Anzahl der Einträge

public:
	// Konstruktor
	PlotStack(void);

	// Destruktor
	~PlotStack(void);

	// Methode zum Anfügen von Listeneinträgen
	BOOL AddPlotKoord(int nPos, double dXpos, double dYpos, double dXdef, double dYdef, double dRot);

	// Methode zum Auslesen einzelner Einträge
	double ReadPlot(int nPos, int nArt);

	// Methode zum Manipulieren von Ploteinträgen
	BOOL SetPlot(int nPos, int nX, int nY);

	// Methode zum Löschen der Liste
	BOOL DelList(void);

	// Methode zum Speichern de Liste
	BOOL SavePlot(const char *lpSavName);
};

} // Namespace Structure

#endif