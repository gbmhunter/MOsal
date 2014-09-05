//!
//! @file				Timer.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-05
//! @last-modified		2014-09-05
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
#include "../include/Timer.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace OsalNs
	{

		Osal * Timer::osal = nullptr;

	}
} // namespace MbeddedNinja

// EOF
