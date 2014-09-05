//!
//! @file				FreertosBinarySemaphore.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-11
//! @last-modified		2014-09-05
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
	class FreertosBinarySemaphore;
}

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System libraries
//#include <cstdint>		// int8_t, int32_t e.t.c
//#include <cstdio>			// snprintf()
//#include <cstdlib>		// realloc(), malloc(), free()
//#include <iostream>		// std::cin, cout, e.t.c

// User libraries
#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/semphr.h"

// User source
#include "../include/BinarySemaphore.h"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace OsalNs
	{

		//============================================================================================//
		//=============================== PUBLIC METHOD DEFINITIONS ==================================//
		//============================================================================================//

		class FreertosBinarySemaphore : public BinarySemaphore
		{
			public:

				FreertosBinarySemaphore()
				{
					this->binarySemaphoreHandle = xSemaphoreCreateBinary();

					if(this->binarySemaphoreHandle == nullptr)
					{
						//! @todo Add assert
						return;
					}
				}

				~FreertosBinarySemaphore()
				{
					if(this->binarySemaphoreHandle == nullptr)
					{
						//! @todo Add assert
						return;
					}

					// Handle is not null, so delete.
					vSemaphoreDelete(this->binarySemaphoreHandle);
				}

				bool Take(double timeoutPeriodMs)
				{
					if(this->binarySemaphoreHandle == nullptr)
					{
						//! @todo Add assert
						return false;
					}

					// Take the semaphore
					if(xSemaphoreTake(this->binarySemaphoreHandle, timeoutPeriodMs/portTICK_RATE_MS) == pdPASS)
						return true;
					else
						return false;
				}

				bool Give()
				{
					if(this->binarySemaphoreHandle == nullptr)
					{
						//! @todo Add assert
						return false;
					}

					if(xSemaphoreGive(this->binarySemaphoreHandle) == pdPASS)
						return true;
					else
						return false;
				}

			//============================================================================================//
			//============================== PRIVATE METHOD DEFINITIONS ==================================//
			//============================================================================================//
		
			// none
		}; // class FreertosBinarySemaphore : public BinarySemaphore
	
	} // namespace OsalNs
} // namespace MbeddedNinja

#endif // #ifndef OSAL_CPP_FREERTOS_BINARY_SEMAPHORE_H

// EOF
