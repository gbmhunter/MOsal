//!
//! @file				Mutex.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-11
//! @last-modified		2014-10-31
//! @brief 				Abstraction layer for a Mutex object.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef M_OSAL_MUTEX_H
#define M_OSAL_MUTEX_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsal
	{
		class Mutex;
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
		
		//! @brief		Abstraction-layer mutex object that is designed to work with the OSAL (operating system
		//!				abstraction layer).
		//! @details	Designed to specialised for a specific OS through inheritance.
		//! @note		OS-specific sub classes are in port/.
		class Mutex
		{
			
			public:

			//======================================================================================//
			//==================================== PUBLIC METHODS ==================================//
			//======================================================================================//

			//! @brief		Binary semaphore destructor.
			//! @details	Removes semaphore from OS.
			//! @warning	Do not delete semaphore if a thread is waiting on it (i.e. it has been
			//!				taken).
			virtual ~Mutex(){};

			//! @brief		Blocks current thread until the mutex can be locked.
			//! @returns	True if mutex was able to be locked before timeout period elapsed,
			//!				otherwise false.
			virtual bool Lock(float timeoutPeriodMs) = 0;

			//! @brief		Unlocks (releases) the mutex.
			//! @returns	True if mutex was able to be unlocked (i.e. it was in the locked state),
			//!				otherwise false.
			virtual bool Unlock() = 0;

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

			//! @brief		Mutex constructor.
			//! @details	Protected to enforce inheritance.
			Mutex(){};

			//======================================================================================//
			//================================== PROTECTED VARIABLES ===============================//
			//======================================================================================//
			
		}; // class Mutex


	} // namespace MOsalNs
} // namespace MbeddedNinja

#endif	// #ifndef M_OSAL_MUTEX_H

// EOF
