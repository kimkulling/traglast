/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : Material.cpp
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 11.12.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ChildView.h"
#include <cassert>

extern int iMatNr;

using namespace Core;
using namespace FEStructure;

//-------------------------------------------------------------------------------------------------
//	Constructor.
Material::Material() :
	m_MatNummer( 0 ),
	m_EModul( 0.0),
	m_A( 0.0 ),
	m_Iy( 0.0 ),
	m_dMpl( 0.0 ),
	m_pNext_Material( NULL ) 
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Destructor.
Material::~Material()
{
	if (m_pNext_Material!=NULL)
		delete m_pNext_Material;
	m_pNext_Material = NULL;
}

//-------------------------------------------------------------------------------------------------
//	Material setter.
void Material::setMaterial( Core::i32 matId, const std::string &rMaterialName,
						   Core::d32 EModul, Core::d32 A, 
						   Core::d32 Iy,
						   Core::d32 plastMoment )
{
	assert( Iy >= 0.0 );
	assert( matId > -1 );
	assert( !rMaterialName.empty() );

	m_MatNummer = matId;
	m_EModul = EModul;
	m_A	= A;
	m_Iy = Iy;
	m_strMaterialName = rMaterialName;
	m_dMpl = plastMoment;
}

//-------------------------------------------------------------------------------------------------
//	Material id getter.
Core::i32 Material::getMatId() const
{
	return m_MatNummer;
}

//-------------------------------------------------------------------------------------------------
//	Gets material data.
void Material::getMaterial( Core::i32 &matId,  std::string &rName, 
						   Core::d32 &EModul, Core::d32 &A, 
						   Core::d32 &Iy, Core::d32 &plastMoment )
{
	matId = m_MatNummer;
	EModul = m_EModul;
	A = m_A;
	Iy = m_Iy;
	rName = m_strMaterialName;
	plastMoment = m_dMpl;
}
               
//-------------------------------------------------------------------------------------------------
//	Set pointer to next material.
void Material::setNextMaterial( Material *pMaterial )
{
	m_pNext_Material = pMaterial;
}

//-------------------------------------------------------------------------------------------------
//	Next material getter.
Material *Material::getNextMaterial() const
{
	return m_pNext_Material;
}

//-------------------------------------------------------------------------------------------------
//	Constructor.
MaterialStack::MaterialStack() :
	m_MaterialList()
{
}

//-------------------------------------------------------------------------------------------------
//	Destructor.
MaterialStack::~MaterialStack()
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Adds a new material.
int MaterialStack::addMaterial( const std::string &rMaterialName, int nr, 
							   double em, double a, double iy, double dMpl)
{
	Material *pNewMaterial  = new Material;

	iAnz++;
	pNewMaterial->setMaterial( nr, rMaterialName, em, a, iy, dMpl );
	pNewMaterial->setNextMaterial( NULL );
	pNewMaterial->setName( rMaterialName );
	m_MaterialList.push_back( pNewMaterial );

	return ErrorHandler::WT_OK;
}

//-------------------------------------------------------------------------------------------------
//	Deletes a material.
int MaterialStack::DelMaterial(int mnr, int /*amnr*/)
{
	int ret_code = 0;
	for ( std::vector<Material*>::iterator it = m_MaterialList.begin();
		it != m_MaterialList.end(); 
		++it )
	{
		if ( (*it)->getMatId() == mnr )
		{
			it = m_MaterialList.erase( it );
			ret_code = 1;
			break;
		}
	}
	return ret_code;
}

//-------------------------------------------------------------------------------------------------
//	Set new material data for a given material.
int MaterialStack::setMaterial(int iMatNr, const std::string &rMaterialName, 
							   double dEM, double dA, double dIy, 
							   double dMpl)
{
	Material *pMaterial = getMaterialById( iMatNr );
	if ( NULL != pMaterial )
	{
		pMaterial->setMaterial( iMatNr, rMaterialName, dEM, dA, dIy, dMpl );
		return ErrorHandler::WT_OK;
	}

	return ErrorHandler::WT_ERR;
}

//-------------------------------------------------------------------------------------------------
//	Returns material data.
double MaterialStack::ReadMaterial(int mnr, int art)
{
	Material *pMaterial = getMaterialById( mnr );
	if ( NULL == pMaterial )
		return -1;

	double dOut( 0.0 );
	switch ( art ) 
	{
	case 1:
		dOut = pMaterial->getEModul();
		break;

	case 2:
		dOut = pMaterial->getArea();
		break;

	case 3:
		dOut = pMaterial->getIy();
		break;

	case 4:
		dOut = pMaterial->getPlastMoment();
		break;

	case 5:
		dOut = pMaterial->getMatId();			
		break;

	default:
		TRACE0("Fehler beim Auslesen vom Material!\n");
		break;
	}

	return dOut;
}

//-------------------------------------------------------------------------------------------------
//	Reads material data from a material.
bool MaterialStack::readMaterial( Core::i32 matId, std::string &rMaterialName,
								 double &dEM, double &dA, double &dIy, 
								 double &dMpl )
{
	Material *pMaterial = this->getMaterialById( matId );
	if ( NULL == pMaterial )
		return false;

	rMaterialName = pMaterial->getName();
	dEM = pMaterial->getEModul();
	dA = pMaterial->getArea();
	dIy =pMaterial->getIy();
	dMpl = pMaterial->getPlastMoment();
	
	return true;
}

//-------------------------------------------------------------------------------------------------
//	Dumps data of a material.
int MaterialStack::ShowMaterial(int iNr)
{
	int       n; 
	double    em, a, iy;
	Material *pMaterial = getMaterialById( iNr );
	if ( NULL == pMaterial )
		return ErrorHandler::WT_ERR;


	n = pMaterial->getMatId(); 
	em = pMaterial->getEModul();
	a = pMaterial->getArea();
	iy = pMaterial->getIy();
	return ErrorHandler::WT_OK;
}

//-------------------------------------------------------------------------------------------------------------------
//	Removes all materials.
int MaterialStack::DelList()
{
	for ( std::vector<Material*>::iterator it = m_MaterialList.begin();
		it != m_MaterialList.end();
		++it )
	{
		if ( NULL != *it )
		{
			delete *it;
		}
	}
	m_MaterialList.resize( 0 );
	return ErrorHandler::WT_OK;
}

//-------------------------------------------------------------------------------------------------
//	Search for a material by its id and returns the instance.
Material *MaterialStack::getMaterialById( Core::i32 materialId )
{
	assert( materialId > -1 );
	Material *pMaterial = NULL;
	for ( std::vector<Material*>::iterator it = m_MaterialList.begin();
		it != m_MaterialList.end();
		++it )
	{
		if ( (*it)->getMatId() == materialId )
		{
			pMaterial = *it;
			break;
		}
	}
	return pMaterial;
}

//-------------------------------------------------------------------------------------------------
