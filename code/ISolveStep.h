#ifndef TRAGLAST_SOLVER_ISOLVESTEP_H_INC
#define TRAGLAST_SOLVER_ISOLVESTEP_H_INC

#include "stdafx.h"

namespace Solver
{

class ISolveStep
{
public:
	virtual ~ISolveStep();

protected:
	ISolveStep();
};

inline ISolveStep::ISolveStep()
{
}

inline ISolveStep::~ISolveStep()
{
}

} // Namespace Solver

#endif // TRAGLAST_SOLVER_ISOLVESTEP_H_INC
