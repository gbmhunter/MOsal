//!
//! @file				FreeRtosBinarySemaphore.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-11
//! @last-modified		2014-09-16
//! @brief 				FreeRTOS implementation of a BinarySemaphore.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef OSAL_CPP_FREERTOS_BINARY_SEMAPHORE_H
#define OSAL_CPP_FREERTOS_BINARY_SEMAPHORE_H

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

		class FreeRtosBinarySemaphore : public BinarySemaphore
		{
			public:

				FreeRtosBinarySemaphore()
				{
					this->binarySemaphoreHandle = xSemaphoreCreateBinary();

					// Check to make sure semaphore was created successfully
					M_ASSERT(this->binarySemaphoreHandle);
				}

				~FreeRtosBinarySemaphore()
				{
					// Handle is not null, so delete.
					vSemaphoreDelete(this->binarySemaphoreHandle);
				}

				bool Take(double timeoutPeriodMs)
				{
					// Take the semaphore
					if(xSemaphoreTake(this->binarySemaphoreHandle, timeoutPeriodMs/portTICK_RATE_MS) == pdPASS)
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

#endif // #ifndef OSAL_CPP_FREERTOS_BINARY_SEMAPHORE_H

// EOF
