#ifndef SOLVER_IOPERATION_H_INC
#define SOLVER_IOPERATION_H_INC

#include "types.h"

namespace Solver
{

class IOperation
{
public:
	virtual ~IOperation();
	virtual bool start() = 0;

protected:
	IOperation();
};

inline IOperation::IOperation()
{
}

inline IOperation::~IOperation()
{
}

} // Namespace Solver

#endif // IOPERATION_H_INC
