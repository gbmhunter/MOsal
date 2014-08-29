//!
//! @file				Osal.c
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-07
//! @last-modified		2014-08-29
//! @brief 				
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System libraries
//#include <cstdint>		// int8_t, int32_t e.t.c
//#include <cstdio>			// snprintf()
//#include <cstdlib>		// realloc(), malloc(), free()
//#include <iostream>		// std::cin, cout, e.t.c

// User libraries
// none

// User source
#include "../include/Osal.h"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{

	//============================================================================================//
	//=============================== PUBLIC METHOD DEFINITIONS ==================================//
	//============================================================================================//

	Osal::Osal(
		void (*threadDelayMs)(double milliseconds),
		void (*enterCriticalSection)(),
		void (*exitCriticalSection)())
	{
		this->threadDelayMs = threadDelayMs;
		this->enterCriticalSection = enterCriticalSection;
		this->exitCriticalSection = exitCriticalSection;		
		
		//! @todo Add warning/error messages if functions pointers are null
	}
		
	void Osal::ThreadDelayMs(double milliseconds)
	{
		if(this->threadDelayMs == nullptr)
		{
			//! @todo Add error message
			return;	
		}		
		
		this->threadDelayMs(milliseconds);
	}
	
	void Osal::EnterCriticalSection()
	{
		if(this->enterCriticalSection == nullptr)
		{
			//! @todo Add error message
			return;	
		}	
		
		this->enterCriticalSection();		
	}


	void Osal::ExitCriticalSection()
	{
		if(this->exitCriticalSection == nullptr)
		{
			//! @todo Add error message
			return;	
		}	
		
		this->exitCriticalSection();
	}
	
	//============================================================================================//
	//============================== PRIVATE METHOD DEFINITIONS ==================================//
	//============================================================================================//

	// none

} // namespace MbeddedNinja

// EOF
