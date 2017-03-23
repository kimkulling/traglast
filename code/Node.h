#ifndef TL_FESTRUCTURE_NODE_H_INC
#define TL_FESTRUCTURE_NODE_H_INC

#include "types.h"
#include <cassert>
#include <vector>

namespace FEStructure
{

//---------------------------------------------------------------------------------------------------------------------
///	\class		Node
///	\ingroup	FEStructure
///
///	\brief	Class to store node informations.
//---------------------------------------------------------------------------------------------------------------------
template<class Prec>
class Node
{
public:
	enum Direction
	{
		XPos = 1,
		YPos
	};

	static const Core::i32 NotSet = -1;
	Node();
	Node( Core::i32 id, Prec xPos, Prec yPos, Prec xHold, Core::i32 idXHold, Prec yHold, 
		Core::i32 idYHold, Prec zHold, Core::i32 idZHold );
	~Node();
	void setId( Core::i32 id );
	Core::i32 getId() const;
	void setPosition( Prec xPos, Prec yPos );
	void getPosition( Prec &rXPos, Prec &rYPos );
	Prec getPos( Direction dir ) const;
	void setBoundaryConditions( Prec xHold, Core::i32 idXHold, Prec yHold, Core::i32 idYHold, Prec zHold, Core::i32 idZHold );
	void getBoundaryConditions( Prec &rXHold, Core::i32 &rIdXHold, Prec rYHold, Core::i32 &rIdYHold, Prec &rZHold, Core::i32 &rIdZHold );
	void getBoundaryConditions( std::vector<Prec> &rHolds, std::vector<Core::i32> &rIds );

private:
	Core::i32 m_NodeId;
	Prec m_X;
	Prec m_Y;
	Prec m_Xhold;
	Core::i32 m_IdXhold;
	Prec m_Yhold;
	Core::i32 m_IdYhold;
	Prec m_Zhold;
	Core::i32 m_IdZhold;
};

//---------------------------------------------------------------------------------------------------------------------
//	Default constructor.
template<class Prec>
inline Node<Prec>::Node() :
	m_NodeId( NotSet ),
	m_X( 0.0 ),
	m_Y( 0.0 ),
	m_Xhold( 0.0 ),
	m_IdXhold( NotSet ),
	m_Yhold( 0.0 ),
	m_IdYhold( NotSet ),
	m_Zhold( 0.0 ),
	m_IdZhold( NotSet )
{
	// empty
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//	Constructor.
template<class Prec>
inline 
Node<Prec>::Node( Core::i32 id, Prec xPos, Prec yPos, Prec xHold, Core::i32 idXHold, 
				  Prec yHold, Core::i32 idYHold, Prec zHold, Core::i32 idZHold ) :
	m_NodeId( id ),
	m_X( xPos ),
	m_Y( yPos ),
	m_Xhold( xHold ),
	m_IdXhold( idXHold ),
	m_Yhold( yHold ),
	m_IdYhold( idYHold ),
	m_Zhold( zHold ),
	m_IdZhold( idZHold )
{
	// empty
}

//---------------------------------------------------------------------------------------------------------------------
//	Destructor.
template<class Prec>
inline Node<Prec>::~Node()
{
	// empty
}

//---------------------------------------------------------------------------------------------------------------------
//	Id setter.
template<class Prec>
inline void Node<Prec>::setId( Core::i32 id )
{
	assert( id > -1 );
	m_NodeId = id;
}

//---------------------------------------------------------------------------------------------------------------------
//	Id getter.
template<class Prec>
inline Core::i32 Node<Prec>::getId() const
{
	return m_NodeId;
}

//---------------------------------------------------------------------------------------------------------------------
//	Position setter.
template<class Prec>
inline void Node<Prec>::setPosition( Prec xPos, Prec yPos )
{
	m_X = xPos;
	m_Y = yPos;
}

//---------------------------------------------------------------------------------------------------------------------
//	Position getter.
template<class Prec>
inline void Node<Prec>::getPosition( Prec &rXPos, Prec &rYPos )
{
	rXPos = m_X;
	rYPos = m_Y;
}
//---------------------------------------------------------------------------------------------------------------------
//
template<class Prec>
inline Prec Node<Prec>::getPos( Direction dir ) const
{
	if ( Node::XPos == dir )
		return this->m_X;
	else if ( Node::YPos == dir )
		return this->m_Y;
	else
		assert( false );
	return 0.0;
}

//---------------------------------------------------------------------------------------------------------------------
//	Boundary condition setter.
template<class Prec>
inline void Node<Prec>::setBoundaryConditions( Prec xHold, Core::i32 idXHold, 
											  Prec yHold, Core::i32 idYHold, 
											  Prec zHold, Core::i32 idZHold )
{
	assert( idXHold > -1 );
	assert( idYHold > -1 );
	assert( idZHold > -1 );

	m_Xhold = xHold;
	m_IdXhold = idXHold;
	m_Yhold = yHold;
	m_IdYhold = idYHold;
	m_Zhold = zHold;
	m_IdZhold = idZHold;
}

//---------------------------------------------------------------------------------------------------------------------
//	Boundary condition getter.
template<class Prec>
inline void Node<Prec>::getBoundaryConditions( Prec &rXHold, Core::i32 &rIdXHold, 
											  Prec rYHold, Core::i32 &rIdYHold, 
											  Prec &rZHold, Core::i32 &rIdZHold )
{
	rXHold = m_Xhold;
	rIdXHold = m_IdXhold;
	rYHold = m_Yhold;
	rIdYHold =m_IdYhold;
	rZHold = m_Zhold;
	rIdZHold = m_IdZhold;
}

//---------------------------------------------------------------------------------------------------------------------
//	Boundary condition getter.
template<class Prec>
inline void Node<Prec>::getBoundaryConditions( std::vector<Prec> &rHolds, 
											  std::vector<Core::i32> &rIds )
{
	rHolds.resize( 0 );
	rHolds.push_back( m_Xhold );
	rHolds.push_back( m_Yhold );
	rHolds.push_back( m_Zhold );

	rIds.resize( 0 );
	rIds.push_back( m_IdXhold );
	rIds.push_back( m_IdYhold );
	rIds.push_back( m_IdZhold );
}

//---------------------------------------------------------------------------------------------------------------------

} // Namespace FEStructure

#endif // TL_FESTRUCTURE_NODE_H_INC
