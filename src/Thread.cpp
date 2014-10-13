//!
//! @file				Thread.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-13
//! @last-modified		2014-10-13
//! @brief				A platform-independent OSAL thread object.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// int8_t, int32_t e.t.c

//! @debug
//#include <iostream>		// std::cout, std::endl

//===== USER LIBRARIES =====//
// none

//===== USER SOURCE =====//
#include "../include/Thread.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{

		Osal * Thread::osal = nullptr;

		void Thread::StaticInit(Osal * osal)
		{
			// Make sure OSAL is not null
			M_ASSERT(osal);

			Thread::osal = osal;
		}

		//! @brief		Binary semaphore constructor.
		//! @details	Protected to enforce inheritance.
		Thread::Thread(MCallbacks::Callback<void, bool> threadMethod) :
				// Transition into the WAITING_FOR_START state on Timer object creation
				threadState(ThreadStates::STOPPED)
		{
			//if(!Thread::osal)
			//	M_ASSERT_FAIL("%s", "Please call Timer::StaticInit() before creating any Timer object.");

			// Save the callback to the thread's method, we run this when Start() is called
			this->threadMethod = threadMethod;

		};

		Thread::ThreadStates Thread::GetState()
		{
			return this->threadState;
		}

	}
} // namespace MbeddedNinja

// EOF
