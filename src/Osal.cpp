//!
//! @file				Osal.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-07
//! @last-modified		2014-10-08
//! @brief 				Base operating system abstraction layer.
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
#include "../include/Osal.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{

	namespace MOsalNs
	{

		//============================================================================================//
		//=============================== PUBLIC METHOD DEFINITIONS ==================================//
		//============================================================================================//

		bool Osal::IsInCriticalSection()
		{
			return this->isInCriticalSection;
		}

		bool Osal::IsThreadsSuspended()
		{
			return this->isThreadsSuspended;
		}
		
		//============================================================================================//
		//============================== PRIVATE METHOD DEFINITIONS ==================================//
		//============================================================================================//
	
		// none
		
	} // namespace Osal
		
} // namespace MbeddedNinja

// EOF
