//!
//! @file				FreeRtosQueue.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-17
//! @last-modified		2014-09-18
//! @brief 				FreeRTOS implementation of a Queue.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_FREERTOS_QUEUE_H
#define MOSAL_FREERTOS_QUEUE_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		template < typename QueueDataT >
		class FreeRtosQueue;
	}
}

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>					// uint32_t

//===== USER LIBRARIES =====//
#include "MAssert/api/MAssertApi.h"		// M_ASSERT()

// FreeRTOS
#include "FreeRTOS/Source/include/FreeRTOS.h"	// FreeRTOS API
#include "FreeRTOS/Source/include/queue.h"		// xQueueCreate(), xQueueDelete(), xQueueSend()...

//===== USER SOURCE =====//
#include "../../include/Queue.h"


//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		template < typename QueueDataT >
		class FreeRtosQueue : public Queue<QueueDataT>
		{

		public:

			//============================================================================================//
			//=============================== PUBLIC METHOD DEFINITIONS ==================================//
			//============================================================================================//

			FreeRtosQueue(uint32_t queueLength)
			{
				// Create queue with FreeRTOS kernal call
				this->queueHandle = xQueueCreate(
					queueLength,				// The length of the queue
					sizeof(QueueDataT));		// Size of each queue object

				// Make sure the queue was created
				M_ASSERT(this->queueHandle);
			}

			~FreeRtosQueue()
			{
				// Remove the queue from the FreeRTOS kernel
				vQueueDelete(this->queueHandle);
			}

			//! @brief		Waits a specified amount of time for data to be available on the
			//!				queue.
			//! @param [out]	queueData	The memory space to copy the received data to.
			//! @param [in]		timeoutPeriodMs		The maximum time (in ms) you want to wait for data to
			//!						become available. A negative number will cause Receive() to wait indefinitely.
			bool Receive(QueueDataT * queueData, float timeoutPeriodMs)
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
					tickTypeTimeoutPeriodInTicks = tickTypeTimeoutPeriodInTicks/portTICK_RATE_MS;
				}

				// Wait for queue to have data
				if(xQueueReceive(
					this->queueHandle,
					(void *)queueData,		// Pass in void* pointer to the queue data
					tickTypeTimeoutPeriodInTicks) == pdPASS)
					return true;
				else
					return false;

			}

			//! @brief		Waits a specified amount of time for data to be available on the
			//!				queue.
			//! @param [out]	queueData	A pointer to the data you wish to copy onto the queue.
			//! @param [in]		timeoutPeriodMs		The maximum time (in ms) you want to wait for the queue to have
			//!						space available. A negative number will cause Send() to wait indefinitely.
			bool Send(const QueueDataT * queueData, float timeoutPeriodMs)
			{
				// Convert double into TickType_t
				TickType_t tickTypeTimeoutPeriodInTicks = (TickType_t)timeoutPeriodMs;

				// If it less than 0, the user wants to wait indefinitely
				if(tickTypeTimeoutPeriodInTicks < 0)
				{
					// Overwrite with special constant
					// (note that the FreeRTOS macro "INCLUDE_vTaskSuspend" has to be set to 1)
					tickTypeTimeoutPeriodInTicks = portMAX_DELAY;
				}
				else
				{
					// User has specified non-negative timeout, so convert this from ms to ticks
					tickTypeTimeoutPeriodInTicks = tickTypeTimeoutPeriodInTicks/portTICK_RATE_MS;
				}

				// Wait for queue to have data
				if(xQueueSendToBack(
					this->queueHandle,
					(void *)queueData,		// Pass in void* pointer to the queue data
					tickTypeTimeoutPeriodInTicks) == pdPASS)
					return true;
				else
					return false;

			}

			//============================================================================================//
			//============================== PRIVATE METHOD DEFINITIONS ==================================//
			//============================================================================================//
		
			// none
		}; // class FreeRtosQueue : public Queue
	
	} // namespace MOsalNs
} // namespace MbeddedNinja

#endif // #ifndef MOSAL_FREERTOS_QUEUE_H

// EOF
