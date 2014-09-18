//!
//! @file				FreeRtosBinarySemaphore.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-11
//! @last-modified		2014-09-18
//! @brief 				FreeRTOS implementation of a BinarySemaphore.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_FREERTOS_BINARY_SEMAPHORE_H
#define MOSAL_FREERTOS_BINARY_SEMAPHORE_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		class FreeRtosBinarySemaphore;
	}
}

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
//none

//===== USER LIBRARIES =====//

// FreeRTOS
#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/semphr.h"

//===== USER SOURCE =====//
#include "../../include/BinarySemaphore.h"

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

		//! @brief		A FreeRTOS implementation of a binary semaphore.
		//! @details	A FreeRTOS binary semaphore is useful for implementing synchronisation between two threads (or one thread and a interrupt). It does not have a priority inheritance mechanism and is not designed for protecting a shared resource (use a FreeRtosMutex object for that purpose).
		class FreeRtosBinarySemaphore : public BinarySemaphore
		{
			public:

				//! @brief		Default constructor. Creates and registers a binary semaphore with the FreeRTOS kernel.
				FreeRtosBinarySemaphore()
				{
					this->binarySemaphoreHandle = xSemaphoreCreateBinary();

					// Check to make sure semaphore was created successfully
					M_ASSERT(this->binarySemaphoreHandle);
				}

				//! @brief		Destructor. Removes and deletes the binary semaphore from the FreeRTOS kernel.
				~FreeRtosBinarySemaphore()
				{
					// Handle is not null, so delete.
					vSemaphoreDelete(this->binarySemaphoreHandle);
				}

				bool Take(float timeoutPeriodMs)
				{
					// For storing conversion of float into TickType_t
					TickType_t tickTypeTimeoutPeriodInTicks;

					// If it less than 0, the user wants to wait indefinitely
					if(timeoutPeriodMs < 0)
					{
						// Overwrite with special constant
						// (note that the FreeRTOS macro "INCLUDE_vTaskSuspend" has to be set to 1)
						tickTypeTimeoutPeriodInTicks = portMAX_DELAY;
					}
					else
					{
						// User has specified non-negative timeout, so convert this from ms to ticks
						tickTypeTimeoutPeriodInTicks = (TickType_t)(timeoutPeriodMs/(float)portTICK_RATE_MS);
					}

					// Take the semaphore
					if(xSemaphoreTake(
							this->binarySemaphoreHandle,
							tickTypeTimeoutPeriodInTicks) == pdPASS)
						return true;
					else
						return false;
				}

				bool Give()
				{
					if(xSemaphoreGive(this->binarySemaphoreHandle) == pdPASS)
						return true;
					else
						return false;
				}

			//============================================================================================//
			//============================== PRIVATE METHOD DEFINITIONS ==================================//
			//============================================================================================//
		
			// none
		}; // class FreeRtosBinarySemaphore : public BinarySemaphore
	
	} // namespace OsalNs
} // namespace MbeddedNinja

#endif // #ifndef MOSAL_FREERTOS_BINARY_SEMAPHORE_H

// EOF
