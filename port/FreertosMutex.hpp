//!
//! @file				FreertosMutex.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-11
//! @last-modified		2014-09-11
//! @brief 				FreeRTOS implementation of a Mutex.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_FREERTOS_MUTEX_H
#define MOSAL_FREERTOS_MUTEX_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	class FreertosMutex;
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

#include "MAssert/api/MAssertApi.h"

// FreeRTOS
#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/semphr.h"

// User source
#include "../include/Mutex.h"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{

		class FreertosMutex : public Mutex
		{

		public:

			//============================================================================================//
			//=============================== PUBLIC METHOD DEFINITIONS ==================================//
			//============================================================================================//

			FreertosMutex()
			{
				// Create mutex with FreeRTOS call
				this->mutexHandle = xSemaphoreCreateMutex();

				// Make sure the mutex was created
				M_ASSERT(this->mutexHandle);
			}

			~FreertosMutex()
			{
				// Handle is not null, so delete.
				vSemaphoreDelete(this->mutexHandle);
			}

			bool Get(double timeoutPeriodMs)
			{

				// Take the semaphore
				if(xSemaphoreTake(this->mutexHandle, timeoutPeriodMs/portTICK_RATE_MS) == pdPASS)
				{
					//CyDebugUart_PutString("Mutex obtained.");
					return true;
				}
				else
				{
					//CyDebugUart_PutString("Mutex was not obtained.");
					return false;
				}
			}

			bool Release()
			{

				if(xSemaphoreGive(this->mutexHandle) == pdPASS)
					return true;
				else
					return false;
			}

			//============================================================================================//
			//============================== PRIVATE METHOD DEFINITIONS ==================================//
			//============================================================================================//
		
			// none
		}; // class FreertosMutex : public Mutex
	
	} // namespace MOsalNs
} // namespace MbeddedNinja

#endif // #ifndef MOSAL_FREERTOS_MUTEX_H

// EOF
