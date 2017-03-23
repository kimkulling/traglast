#ifndef SOLVER_BANDOP_H_INC
#define SOLVER_BANDOP_H_INC

#include "IOperation.h"

class InzidenzStack;

namespace Solver
{

class BandOp : public IOperation
{
public:
	BandOp( Core::i32 iEleKn, Core::i32 numberOfElements, const InzidenzStack &rInz, Core::i32 numberOfDOF );
	~BandOp();
	bool start();
	Core::i32 getBandWitdh() const;

private:
	Core::i32 m_iBandWidth;
	Core::i32 m_iEleKn;
	Core::i32 m_iNumberOfElements;
	Core::i32 m_iNumberOfDOF;
	InzidenzStack m_rInz;
};

} // namespace Solver

#endif