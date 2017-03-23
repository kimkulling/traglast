#ifndef SOLVER_SYSTEMSTIFFNESSBUILDER_H_INC
#define SOLVER_SYSTEMSTIFFNESSBUILDER_H_INC

#include "IOperation.h"

namespace Solver
{

//-------------------------------------------------------------------------------------------------
///	\class		SystemStiffnessBuilder
///	\ingroup	Solver
///	
///	\brief	Asselble a single element matrix into a given system stiffness 
///	matrix.
//-------------------------------------------------------------------------------------------------
class SystemStiffnessBuilder : public IOperation
{
public:
	///	Constructor.
	SystemStiffnessBuilder( Core::ui32 numberOfElements, Core::ui32 numberOfEleNodes, Core::ui32 numberOfDoF, Core::ui32 band, InzidenzStack Inz, Vektor eleSteif, Vektor sysSteif );
	///	Destructor.
	~SystemStiffnessBuilder();
	///	Starts the operation.
	bool start();

	Vektor getSystemStiffness();

private:
	///	Number of elements in the system of this system stiffness.
	Core::ui32 m_ElementId;
	///	Number of nodes per elements.
	Core::ui32 m_NumberOfEleNodes;
	///	Number of degree of freedoms per node.
	Core::ui32 m_numberOfDoF;
	///	Assigned incidence table.
	InzidenzStack m_Inz;
	///	Element stiffness matrix.
	Vektor m_EleSteif;
	///	System stiffness matrix.
	Vektor m_SysSteif;
	///	Band width of the element matrix.
	Core::ui32 m_Band;
};

//-------------------------------------------------------------------------------------------------

} // Namespace Solver

#endif // SOLVER_SYSTEMSTIFFNESSBUILDER_H_INC
