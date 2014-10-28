//!
//! @file				BinarySemaphore.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-11
//! @last-modified		2014-10-29
//! @brief 				
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_BINARY_SEMAPHORE_H
#define MOSAL_BINARY_SEMAPHORE_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		class BinarySemaphore;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM HEADERS =====//
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
	namespace MOsalNs
	{
		
		//! @brief		Abstraction-layer binary semaphore object that is designed to work with the OSAL (operating system
		//!				abstraction layer).
		//! @details	Designed to specialised for a specific OS through inheritance.
		//! @note		OS-specific sub classes are in port/.
		class BinarySemaphore
		{
			
			public:

				//======================================================================================//
				//==================================== PUBLIC METHODS ==================================//
				//======================================================================================//

				//! @brief		Binary semaphore constructor.
				//! @details	Adds semaphore to OS.
				BinarySemaphore(){};

				//! @brief		Binary semaphore destructor.
				//! @details	Removes semaphore from OS.
				//! @warning	Do not delete semaphore if a thread is waiting on it (i.e. it has been
				//!				taken).
				virtual ~BinarySemaphore(){};

				//! @brief		Blocks current thread until the binary semaphore can be taken.
				//! @returns	True if semaphore was able to be taken before timeout period elapsed,
				//!				otherwise false.
				virtual bool Take(float timeoutPeriodMs) = 0;

				//! @brief		Releases the binary semaphore.
				//! @returns	True if semaphore was able to be given (i.e. it's been taken first),
				//!				otherwise false.
				virtual bool Give() = 0;

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

				//! @brief		Internally saves the binary semaphore handle assigned by the OS.
				void * binarySemaphoreHandle;
			
		}; // class BinarySemaphore


	} // namespace MOsalNs
} // namespace MbeddedNinja

#endif	// #ifndef MOSAL_BINARY_SEMAPHORE_H

// EOF
