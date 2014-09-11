//!
//! @file				FreertosOsal.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-29
//! @last-modified		2014-09-05
//! @brief 				Port-specific operating system abstraction layer for FreeRTOS.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef OSAL_CPP_FREERTOS_OSAL_H
#define OSAL_CPP_FREERTOS_OSAL_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	class FreertosOsal;
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
#include "../include/Osal.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	
	namespace MOsalNs
	{
	
		//! @brief		Port-specific operating system abstraction layer for FreeRTOS.
		//! @details	Inherits from Osal.
		//! @note
		class FreertosOsal : public Osal
		{
			
			public:

				//======================================================================================//
				//==================================== PUBLIC METHODS ==================================//
				//======================================================================================//

				//! @brief		Osal constructor.
				FreertosOsal()
				{

				}

				~FreertosOsal()
				{

				}


				void EnterCriticalSection()
				{
					taskENTER_CRITICAL();
				}

				void ExitCriticalSection()
				{
					taskEXIT_CRITICAL();
				}

				void SuspendAllThreads()
				{
					vTaskSuspendAll();
				}

				void ResumeAllThreads()
				{
					xTaskResumeAll();
				}

				//! @brief		Delays a thread for a certain amount of milliseconds. Allows execution of other threads
				//!				in the interim.
				void ThreadDelayMs(double milliseconds)
				{
					vTaskDelay((milliseconds/(double)portTICK_RATE_MS));
				}

				uint32_t GetTimeMs()
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

			private:

				//======================================================================================//
				//=================================== PRIVATE METHODS ==================================//
				//======================================================================================//

				// none

				//======================================================================================//
				//================================== PRIVATE VARIABLES =================================//
				//======================================================================================//



			protected:

				//======================================================================================//
				//=================================== PROTECTED METHODS ================================//
				//======================================================================================//
				
				// none
				
				//======================================================================================//
				//================================== PROTECTED VARIABLES ===============================//
				//======================================================================================//

				// none
			
		}; // class FreertosOsal

	} // namespace OsalNs

} // namespace MbeddedNinja

#endif	// #ifndef OSAL_CPP_FREERTOS_OSAL_H

// EOF
