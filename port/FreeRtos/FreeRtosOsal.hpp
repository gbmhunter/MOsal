//!
//! @file				FreeRtosOsal.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-29
//! @last-modified		2014-10-08
//! @brief 				Port-specific operating system abstraction layer for FreeRTOS.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_FREERTOS_OSAL_H
#define MOSAL_FREERTOS_OSAL_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		class FreeRtosOsal;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// System headers
//#include <cstdint>		// int8_t, int32_t e.t.c

// User libraries

// FreeRTOS includes
#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/task.h"
#include "FreeRTOS/Source/include/queue.h"
#include "FreeRTOS/Source/include/semphr.h"

// User headers
#include "../../include/Osal.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	
	namespace MOsalNs
	{
	
		//! @brief		Port-specific operating system abstraction layer for FreeRTOS.
		//! @note		Inherits from Osal. See the Osal class for method descriptions.
		class FreeRtosOsal : public Osal
		{
			
			public:

				//======================================================================================//
				//==================================== PUBLIC METHODS ==================================//
				//======================================================================================//

				//! @brief		Osal constructor.
				FreeRtosOsal()
				{

				}

				~FreeRtosOsal()
				{

				}


				void EnterCriticalSection()
				{
					taskENTER_CRITICAL();

					// Set to true after we are inside a critical section so we are "atomic"
					this->isInCriticalSection = true;
				}

				void ExitCriticalSection()
				{
					// Set to false first so that it is "atomic"
					this->isInCriticalSection = false;

					taskEXIT_CRITICAL();
				}

				void SuspendAllThreads()
				{
					//! @todo This could be buggy! What if an interrupt fires after vTaskSuspendAll() is called
					//!		but before isThreadsSuspended is set to true, and interrupt checks IsThreadsSuspended()???
					vTaskSuspendAll();

					// Set to true after we are inside a critical section so we are "atomic"
					this->isThreadsSuspended = true;
				}

				void ResumeAllThreads()
				{
					//! @todo	This could be buggy for the same reason as SuspendAllThreads().

					// Set to false first so that it is "atomic"
					this->isThreadsSuspended = false;

					xTaskResumeAll();
				}

				//! @brief		Delays a thread for a certain amount of milliseconds. Allows execution of other threads
				//!				in the interim.
				void ThreadDelayMs(double milliseconds)
				{
					vTaskDelay((milliseconds/(double)portTICK_RATE_MS));
				}

				uint32_t GetRunTimeMs()
				{
					// Freertos uses ticks, so we need to convert the tick count to
					// a specific number of milliseconds, knowing the ratio between the two
					uint32_t tickCount = xTaskGetTickCount();

					// portTICK_RATE_MS is actually the number of millisconds per tick!
					return tickCount * portTICK_RATE_MS;

				}

				//======================================================================================//
				//================================= PUBLIC VARIABLES ===================================//
				//======================================================================================//

				// none

			
		}; // class FreeRtosOsal

	} // namespace OsalNs
} // namespace MbeddedNinja

#endif	// #ifndef MOSAL_FREERTOS_OSAL_H

// EOF
