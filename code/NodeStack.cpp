#include "StdAfx.h"
#include "NodeStack.h"

namespace FEStructure
{

using namespace Core;

//-------------------------------------------------------------------------------------------------
//	Constructor.
NodeStack::NodeStack() :
	m_Nodes()
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Destructor.
NodeStack::~NodeStack()
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Adds a new node instance.
void NodeStack::addNode( NodeDef &rNode )
{
	m_Nodes.push_back( rNode );
}

//-------------------------------------------------------------------------------------------------
//	Adds a new node instance.
void NodeStack::addNode( i32 id, d32 xPos, d32 yPos, d32 xHold, i32 idXHold, 
						d32 yHold, i32 idYHold, d32 zHold, i32 idZHold )
{
	NodeDef node( id, xPos, yPos, xHold, idXHold, yHold, idYHold, zHold, idZHold );
	m_Nodes.push_back( node );
}

//-------------------------------------------------------------------------------------------------
//	Modify a given node.
void NodeStack::setNode( Core::i32 id, Core::d32 xPos, Core::d32 yPos, 
						Core::d32 xHold, Core::i32 idXHold,	Core::d32 yHold,
						Core::i32 idYHold, Core::d32 zHold, Core::i32 idZHold )
{
	NodeDef node;
	if ( getNode( id, node ) )
	{
		node.setPosition( xPos, yPos );
		node.setBoundaryConditions( xHold, idXHold, yHold, idYHold, zHold, idZHold );
	}
}

//-------------------------------------------------------------------------------------------------
//	Returns a node instance.
bool NodeStack::getNode( i32 nodeId, NodeDef &rNode ) const
{
	for ( std::vector<NodeDef>::const_iterator it = m_Nodes.begin();
		it != m_Nodes.end();
		++it )
	{
		if ( (*it).getId() == nodeId )
		{
			rNode = *it;
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
//	Removes a node instance.
bool NodeStack::removeNode( Core::i32 nodeId )
{
	std::vector<NodeDef>::iterator it = getNodeById( nodeId );
	if (  m_Nodes.end() == it )
		return false;
	it = m_Nodes.erase( it );
	return true;
}

//-------------------------------------------------------------------------------------------------
//	Returns the nuber of managed nodes.
i32 NodeStack::getNumberOfNodes() const
{
	return m_Nodes.size();
}

//-------------------------------------------------------------------------------------------------
//	Returns the assigned node iterator for a given node id.
std::vector<NodeStack::NodeDef>::iterator NodeStack::getNodeById( Core::i32 id )
{
	assert( id > -1 );
	for ( std::vector<NodeDef>::iterator it = m_Nodes.begin();
		it != m_Nodes.end();
		++it )
	{
		if ( (*it).getId() == id )
		{
			 return it;
		}
	}
	return m_Nodes.end();
}

//-------------------------------------------------------------------------------------------------
Core::d32 NodeStack::getXMin()
{
	return getMin( Node<Core::d32>::XPos );
}

//-------------------------------------------------------------------------------------------------
Core::d32  NodeStack::getXMax()
{
	return getMax( Node<Core::d32>::XPos );
}

//-------------------------------------------------------------------------------------------------
Core::d32  NodeStack::getYMin()
{
	return getMin( Node<Core::d32>::YPos );
}

//-------------------------------------------------------------------------------------------------
Core::d32 NodeStack::getYMax()
{
	return getMax( Node<Core::d32>::YPos );
}

//-------------------------------------------------------------------------------------------------
void NodeStack::clear()
{
	this->m_Nodes.resize( 0 );
}

//-------------------------------------------------------------------------------------------------
Core::d32 NodeStack::getMin( Node<Core::d32>::Direction dir )
{
	Core::d32 min = 99999999.999;
	for ( std::vector<NodeDef>::iterator it = this->m_Nodes.begin();
		it != m_Nodes.end();
		++it )
	{
		const Core::d32 pos = ( *it ).getPos( dir );
		if ( pos < min )
			min = pos;
	}
	return min;

}

//-------------------------------------------------------------------------------------------------
Core::d32 NodeStack::getMax( Node<Core::d32>::Direction dir )
{
	Core::d32 max = -99999999.999;
	for ( std::vector<NodeDef>::iterator it = this->m_Nodes.begin();
		it != m_Nodes.end();
		++it )
	{
		const Core::d32 pos = ( *it ).getPos( dir );
		if ( pos > max )
			max = pos;
	}
	return max;

}

//-------------------------------------------------------------------------------------------------

} // namespace FEStructure
