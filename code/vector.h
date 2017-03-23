#ifndef __VECTOR_H_INC__
#define __VECTOR_H_INC__

/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: VektorStack
// Beschreibung	: Klasse zum Anlegen einer Vektor-Liste
/////////////////////////////////////////////////////////////////////////////////////////////////
class Vektor
{
public:
	// Kostruktor
	Vektor();

	// Destruktor
	~Vektor();

	// Returns number of entries
	int Size();

	// Methode zum Belegen eines neuen Vektors mit Nullen
	int DeclVektor(int iAnz);

	// Methode zum Addieren eines neuen Wertes in die Liste
	int addVektor(const double W);

	// Methode zum Auslesen eines Eintrages aus der Liste
	double readVektor(const int iPos) {return pVektor[iPos-1];};	

	// Method for reading Entries, Val will be returned by parameter
	int ReadVektor(int iIndex, double *pData);

	// Method to read value per parameter
	int ReadVector(int iNr, double *pValues);

	// Method to reads values from vector per block
	int GetBlock(int iNum, int iStart, double *pBlock); 

	// Methode zum Löschen eines Eintrages in der Liste
	int delVektor(int iPos);

	// Methode zum Neusetzten eines Wertes in der Liste
	BOOL setVektor(int pos, double w);

	// Method to set a incore block
	int SetBlock(int iNum, int iStart, double *pBlock);

	// Methode zum Auslesen der Minimalwerte
	double Getmin(int iFG, int iArt);

	// Methode zum Auslesen der Maximalwerte
	double Getmax(int iFG, int iArt);
	
	// Methode zum Sortieren des Vektors
	BOOL SortVektor(int iArt);

	// Methode zum Laden einer Vektorliste
	BOOL LoadVektor(const char *cLoad);

	// Methode zum Speichern einer Vektorliste
	BOOL SaveVektor(const char *cSave, int iAnz);

	// Methode zum Löschen der gesamten Liste
	BOOL DelList(void);

	// Method to clear a vector
	int InitVector(int iLower, int iUpper);

private:
	mutable double	dMaxV;    // Calculeted max of vector
	mutable double	dMinV;    // Calculeted min of vector
	BOOL	        m_bChanged; // Flag for calc
	double         *pVektor;  // Pointer auf Array mit den Daten
	double          dVector;  // 
	
public:
	int		iAnz;
	double	dScaleX;
	double	dScaleY;

private:
	void SetChanged() {m_bChanged = TRUE;};
};

#endif