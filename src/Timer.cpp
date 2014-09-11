//!
//! @file				Timer.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-05
//! @last-modified		2014-09-11
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
	namespace MOsalNs
	{

		Osal * Timer::osal = nullptr;

		void Timer::StaticInit(Osal * osal)
		{
			// Make sure OSAL is not null
			M_ASSERT(osal);

			Timer::osal = osal;
		}

		//! @brief		Binary semaphore constructor.
		//! @details	Protected to enforce inheritance.
		Timer::Timer(uint32_t timeoutInMs)
		{
			if(!Timer::osal)
				M_ASSERT_FAIL("%s", "Please call Timer::StaticInit() before creating any Timer object.");
			this->timeoutInMs = timeoutInMs;
		};

		void Timer::Start()
		{
			// Get the current time from the OSAL
			// and save as the current start time
			this->startTimeInMs = Timer::osal->GetTimeMs();
		}

		bool Timer::IsExpired() const
		{
			if(Timer::osal->GetTimeMs() >= this->startTimeInMs + this->timeoutInMs)
				return true;
			else
				return false;

		}

		uint32_t Timer::GetRemainingTime() const
		{
			return this->timeoutInMs - (Timer::osal->GetTimeMs() - this->startTimeInMs);

		}

	}
} // namespace MbeddedNinja

// EOF
