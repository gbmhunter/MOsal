//!
//! @file				Osal.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-07
//! @last-modified		2014-10-29
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
#include "MAssert/api/MAssertApi.hpp"

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
		
		uint64_t Osal::GetTimeMs()
		{
			M_ASSERT_FAIL("%s", "Osal::GetRunTimeMs() has not been implemented by the specific port you are using.");
			return 0;
		}

		uint64_t Osal::GetUnixTimeMs()
		{
			M_ASSERT_FAIL("%s", "Osal::GetUnixTimeMs() has not been implemented by the specific port you are using.");
			return 0;
		}

		//============================================================================================//
		//============================== PRIVATE METHOD DEFINITIONS ==================================//
		//============================================================================================//
	
		// none
		
	} // namespace MOsalNs
		
} // namespace MbeddedNinja

// EOF
