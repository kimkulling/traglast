/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : wtErrorHandler.h
// Beschreibung	: Definitions and enum-definitions of class weErrorHandler
// Autor		: Kim Kulling
// Last mod.    : 06.12.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TRAGLAST_CORE_WTERRORHANDLER_H_INC
#define TRAGLAST_CORE_WTERRORHANDLER_H_INC


namespace Core
{

class ErrorHandler
{
public:
	enum ErrorCode
	{
		WT_FATAL_ERR  = -1,
		WT_ERR        = 0,
		WT_OK         = 1,
		WT_OUT_OF_MEM = 2,
	};

public:
	///	Constructor.
	ErrorHandler();
	///	Destructor.
	~ErrorHandler();
	///	Returns error code and message.
	void HandleMessage(int iErrCode);
	
private:
	int iLastError;
};

} // Namespace Core 

#endif // TRAGLAST_CORE_WTERRORHANDLER_H_INC
