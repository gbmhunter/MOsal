//!
//! @file				Osal.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-07
//! @last-modified		2014-10-29
//! @brief 				Base operating system abstraction layer.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_OSAL_H
#define MOSAL_OSAL_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		class Osal;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// int8_t, int32_t e.t.c

//===== USER LIBRARIES =====//
#include "MCallbacks/api/MCallbacksApi.hpp"

//===== USER SOURCE =====//
// none

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
	

		//! @brief		The basic OSAL object that provides an interface to OS specific functionality.
		//! @details	Provide the OS-specific function bodies by inheriting from this class.
		//!				This class essentially specifies the common OSAL interface that can be used on
		//!				any operating system.
		//! @note		OS-specific sub classes are in port/.
		class Osal
		{
			
			public:

				//======================================================================================//
				//==================================== PUBLIC METHODS ==================================//
				//======================================================================================//

				//! @brief		Destructor.
				virtual ~Osal(){};

				//! @brief		Enters a critical section (the scheduler and OS-aware interrupts are disabled).
				//! @details	Use to enter a section of atomic code.
				//! @note		ISR safe (tested with the FreeRTOS port on a Cortex-M3).
				virtual void EnterCriticalSection() = 0;

				//! @brief		Exits a critical section (the scheduler and OS-aware interrupts are re-enabled).
				//! @details	Use to exit a section of atomic code.
				//! @note		ISR safe (tested with the FreeRTOS port on a Cortex-M3).
				virtual void ExitCriticalSection() = 0;

				//! @brief		Use to determine is OS is current executing inside a critical section.
				//! @returns	True if OS is currently executing inside a critical section, otherwise false.
				bool IsInCriticalSection();

				//! @brief		Suspends all threads.
				virtual void SuspendAllThreads(){};

				//! @brief		Resumes all threads.
				virtual void ResumeAllThreads(){};

				//! @brief		Use to determine if threads are currently suspended.
				//! @returns	True if threads are currently suspended, otherwise false.
				bool IsThreadsSuspended();

				//! @brief		Delays a thread for a certain amount of milliseconds. Allows execution of other threads
				//!				in the interim.
				virtual void ThreadDelayMs(double milliseconds) = 0;

				//! @brief		Returns a time (in milliseconds) that can be used for relative time periods.
				//! @details	Actual value is platform specific (e.g. it could be the time since Epoch when running under Linux, or the time since the OS was started if running under FreeRTOS). This should only be used for relative time periods (i.e. one minus another). Will raise an assert if method has not been implemented for a particular port.
				virtual uint64_t GetTimeMs();

				//! @brief		Returns the time (in milliseconds) since the Epoch.
				//! @details	Will raise an assert if method has not been implemented for a particular port.
				virtual uint64_t GetUnixTimeMs();

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
				
				//! @brief		Used to remember when OS is currently in a critical section.
				//! @details	Value returned by the method IsInCriticalSection().
				bool isInCriticalSection;

				//! @brief		Used to remember when threads are currently suspended.
				//! @details	Value returned by the method IsThreadsSuspended().
				bool isThreadsSuspended;

			protected:

				//======================================================================================//
				//=================================== PROTECTED METHODS ================================//
				//======================================================================================//
				
				//! @brief		Protected method forces this class to be inherited.
				Osal(){};
				
				//======================================================================================//
				//================================== PROTECTED VARIABLES ===============================//
				//======================================================================================//

				// none
			
		}; // class Osal

	} // namespace OsalNs
} // namespace MbeddedNinja

#endif	// #ifndef MOSAL_OSAL_H

// EOF
