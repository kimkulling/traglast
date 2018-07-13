#ifndef __VECTOR_H_INC__
#define __VECTOR_H_INC__

/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: VektorStack
// Beschreibung	: Klasse zum Anlegen einer Vektor-Liste
/////////////////////////////////////////////////////////////////////////////////////////////////
class Vektor {
public:
	// Kostruktor
	Vektor();

	// Destruktor
	~Vektor();

	// Returns number of entries
	int Size();

    bool isEmpty() const;

	// Methode zum Belegen eines neuen Vektors mit Nullen
	void initVector(int iAnz);

	// Methode zum Addieren eines neuen Wertes in die Liste
	int addVektor(const double W);

	// Methode zum Auslesen eines Eintrages aus der Liste
	double readVektor(const int iPos);	

	// Method for reading Entries, Val will be returned by parameter
	int ReadVektor(int iIndex, double *pData);

	// Method to read value per parameter
	int ReadVector(int iNr, double *pValues);

	// Method to reads values from vector per block
	int GetBlock(int iNum, int iStart, double *pBlock); 

	// Methode zum Löschen eines Eintrages in der Liste
	int delVektor(int iPos);

	// Methode zum Neusetzten eines Wertes in der Liste
	bool setVektor(int pos, double w);

	// Method to set a incore block
	int SetBlock(int iNum, int iStart, double *pBlock);

	// Methode zum Auslesen der Minimalwerte
	double Getmin(int iFG, int iArt);

	// Methode zum Auslesen der Maximalwerte
	double Getmax(int iFG, int iArt);
	
	// Methode zum Sortieren des Vektors
	bool SortVektor(int iArt);

	// Methode zum Laden einer Vektorliste
    bool LoadVektor(const char *cLoad);

	// Methode zum Speichern einer Vektorliste
    bool SaveVektor(const char *cSave, int iAnz);

	// Methode zum Löschen der gesamten Liste
    bool DelList();

	// Method to clear a vector
	int InitVector(int iLower, int iUpper);

private:
    mutable double	m_dMaxV;
	mutable double	m_dMinV;  
	bool	        m_changed;
	double         *m_data;   
	double          m_dVector; 
	
public:
    int		m_size;
	double	m_dScaleX;
	double	m_dScaleY;

private:
	void SetChanged();
};

inline
double Vektor::readVektor( const int iPos ) { 
    return m_data[ iPos - 1 ];
};

inline
void Vektor::SetChanged() { 
    m_changed = true;
}

#endif
