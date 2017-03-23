//----------------------------------------------------------------------------------------------------------------------
///	\file		NodeStack.h
///	\ingroup	FEStructure
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009
///	\brief		Class declaration of NodeStack ( node management class ).
///
/// This program is free software: you can redistribute it and/or modify
///	it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------------------------------------------------
#ifndef FESTRUCTURE_NODESTACK_H_INC
#define FESTRUCTURE_NODESTACK_H_INC

#include "Node.h"
#include <vector>

namespace FEStructure
{

//---------------------------------------------------------------------------------------------------------------------
	///	\class		NodeStack
///	\ingroup	FEStructure
///
///	\brief	Class for node management. Each node has X- and Y-components and informations about 
///	its boundary condition. 
///	TODO:	Separate boundary conditions into a separate data structure.
//---------------------------------------------------------------------------------------------------------------------
class NodeStack
{
public:
	typedef Node<Core::d32> NodeDef;

public:
	///	Constructor.
	NodeStack();
	///	Destructor.
	~NodeStack();
	///	Adds a new node definition.
	void addNode( NodeDef &rNode );
	///	Adds a new node definition.
	void addNode( Core::i32 id, Core::d32 xPos, Core::d32 yPos, Core::d32 xHold, Core::i32 idXHold,
		Core::d32 yHold, Core::i32 idYHold, Core::d32 zHold, Core::i32 idZHold );
	///	Modifies a already existing node. all old data will be resettet.
	void setNode( Core::i32 id, Core::d32 xPos, Core::d32 yPos, Core::d32 xHold, Core::i32 idXHold,
		Core::d32 yHold, Core::i32 idYHold, Core::d32 zHold, Core::i32 idZHold );
	///	Returns the requested node.
	bool getNode( Core::i32 nodeId, NodeDef &rNode ) const;
	///	Removes a node.
	bool removeNode( Core::i32 nodeId );
	///	Returns the number of nodes.
	Core::i32 getNumberOfNodes() const;
	///	Returns minimum component value in X.
	Core::d32 getXMin();
	///	Returns maximum component value in X.
	Core::d32 getXMax();
	///	Returns minimum component value in Y.
	Core::d32 getYMin();
	///	Returns maximum component value in Y.
	Core::d32 getYMax();
	///	Clears the stack, all data will be resetted.
	void clear();

private:
	std::vector<NodeDef>::iterator getNodeById( Core::i32 id );
	Core::d32 getMin( Node<Core::d32>::Direction dir );
	Core::d32 getMax( Node<Core::d32>::Direction dir );

private:
	std::vector<NodeDef> m_Nodes;
};

} // Namespace FEStructure

//---------------------------------------------------------------------------------------------------------------------

#endif // Namespace FESTRUCTURE_NODESTACK_H_INC
