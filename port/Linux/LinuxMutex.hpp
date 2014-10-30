//!
//! @file				LinuxMutex.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-31
//! @last-modified		2014-10-31
//! @brief 				Linux implementation of a Mutex.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef M_OSAL_LINUX_MUTEX_H
#define M_OSAL_LINUX_MUTEX_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsal
	{
		class LinuxMutex;
	}
}

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
//#include <cstdint>		// int8_t, int32_t e.t.c
#include <mutex>			// std::mutex

//===== USER LIBRARIES =====//
#include "MAssert/api/MAssertApi.hpp"

//===== USER SOURCE =====//
#include "../../include/Mutex.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsal
	{

		//! @brief		A FreeRTOS implementation of a Mutex.
		//! @details	A FreeRTOS mutex is a binary semaphore with a priority inheritance mechanism. A FreeRTOS mutex is good for protecting a shared resource. A mutex is designed to be got and released from the same thread.
		//! @note		Inherits from Mutex. See the Mutex class for method descriptions.
		class LinuxMutex : public Mutex
		{

		public:

			//============================================================================================//
			//=============================== PUBLIC METHOD DEFINITIONS ==================================//
			//============================================================================================//

			LinuxMutex()
			{
				// Create mutex with std::mutex call
				this->mutex = new std::mutex;

				// Make sure the mutex was created
				M_ASSERT(this->mutex);
			}

			~LinuxMutex()
			{
				// Behaviour of program is undefined if mutex is destroyed while some thread still has a lock,
				// so be careful with this!
				delete this->mutex;

				// Set to nullptr just to be safe
				this->mutex = nullptr;
			}

			bool Lock(float timeoutPeriodMs)
			{
				// Lock the mutex
				this->mutex->lock();

				return true;
			}

			bool Unlock()
			{
				// Unlock the mutex
				this->mutex->unlock();

				return true;
			}

			//============================================================================================//
			//============================== PRIVATE METHOD DEFINITIONS ==================================//
			//============================================================================================//
		
			//! @brief		Pointer to mutex that is created in the constructor and destroyed in destructor.
			std::mutex * mutex;

		}; // class LinuxMutex : public Mutex
	
	} // namespace MOsal
} // namespace MbeddedNinja

#endif // #ifndef M_OSAL_LINUX_MUTEX_H

// EOF
