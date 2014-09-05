//!
//! @file				FreertosMutex.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-11
//! @last-modified		2014-09-05
//! @brief 				FreeRTOS implementation of a Mutex.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef OSAL_CPP_FREERTOS_MUTEX_H
#define OSAL_CPP_FREERTOS_MUTEX_H

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
#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/semphr.h"

// User source
#include "../include/Mutex.h"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace OsalNs
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

				if(this->mutexHandle == nullptr)
				{
					//! @todo Add OS-independant assert
					configASSERT(0);
					return;
				}
			}

			~FreertosMutex()
			{
				if(this->mutexHandle == nullptr)
				{
					//! @todo Add OS-independant assert
					configASSERT(0);
					return;
				}
	
				// Handle is not null, so delete.
				vSemaphoreDelete(this->mutexHandle);
			}

			bool Get(double timeoutPeriodMs)
			{
				if(this->mutexHandle == nullptr)
				{
					//! @todo Add OS-independant assert
					configASSERT(0);
					return false;
				}

				//CyDebugUart_PutString("Mutex::Get() called.");

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
				if(this->mutexHandle == nullptr)
				{
					//! @todo Add OS-independant assert
					configASSERT(0);
					return false;
				}

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
	
	} // namespace OsalNs
} // namespace MbeddedNinja

#endif // #ifndef OSAL_CPP_FREERTOS_MUTEX_H

// EOF
