//!
//! @file				Queue.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-17
//! @last-modified		2014-10-30
//! @brief 				Abstraction layer for a Queue object.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_QUEUE_H
#define MOSAL_QUEUE_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsal
	{
		template < typename QueueDataT >
		class Queue;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// int8_t, int32_t e.t.c

//===== USER LIBRARIES =====//
// none

//===== USER SOURCE =====//
// none

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsal
	{
		
		//! @brief		Abstraction-layer queue object that is designed to work with the OSAL (operating system
		//!				abstraction layer).
		//! @details	Designed to specialised for a specific OS through inheritance.
		//! @note		OS-specific sub classes are in port/.
		template < typename QueueDataT >
		class Queue
		{
			
			public:

				//======================================================================================//
				//==================================== PUBLIC METHODS ==================================//
				//======================================================================================//

				//! @brief		Queue destructor.
				//! @details	Removes queue from OS.
				//! @warning	Do not delete queue if a thread is waiting on it (i.e. it has been
				//!				taken).
				virtual ~Queue(){};

				//! @brief		Blocks current thread until data can be received (taken) from queue.
				//! @returns	True if data was able to be taken from queue before timeout period elapsed,
				//!				otherwise false.
				virtual bool Receive(QueueDataT * queueData, float timeoutPeriodMs) = 0;

				//! @brief		Places data onto the queue.
				//! @returns	True if data was able to be placed on the queue,
				//!				otherwise false.
				virtual bool Send(const QueueDataT * queueData, float timeoutPeriodMs) = 0;

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
	
				//=====================================================================================//
				//=================================== PROTECTED METHODS ================================//
				//======================================================================================//
				
				//! @brief		Binary semaphore constructor.
				//! @details	Protected to enforce inheritance.
				Queue(){};
				
				//======================================================================================//
				//================================== PROTECTED VARIABLES ===============================//
				//======================================================================================//

				//! @brief		Internally saves the binary semaphore handle assigned by the OS.
				void * queueHandle;
			
		}; // class Queue

	} // namespace MOsalNs
} // namespace MbeddedNinja

#endif	// #ifndef MOSAL_QUEUE_H

// EOF
