//!
//! @file				Osal.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-07
//! @last-modified		2014-08-29
//! @brief 				
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef OSAL_CPP_OSAL_H
#define OSAL_CPP_OSAL_H

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

// System headers
#include <cstdint>		// int8_t, int32_t e.t.c

// User libraries
// none

// User headers
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

				//! @brief		Destructor
				virtual ~Osal(){};

				//! @brief
				virtual void EnterCriticalSection() = 0;

				virtual void ExitCriticalSection() = 0;

				virtual void SuspendAllThreads(){};

				virtual void ResumeAllThreads(){};

				//! @brief		Delays a thread for a certain amount of milliseconds. Allows execution of other threads
				//!				in the interim.
				virtual void ThreadDelayMs(double milliseconds) = 0;

				//! @brief		Returns the time since operating system started running in milliseconds.
				virtual uint32_t GetTimeMs() = 0;

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
				
				//! @brief		Protected method forces this class to be inherited.
				Osal(){};
				
				//======================================================================================//
				//================================== PROTECTED VARIABLES ===============================//
				//======================================================================================//

				// none
			
		}; // class Osal

	} // namespace OsalNs
} // namespace MbeddedNinja

#endif	// #ifndef OSAL_CPP_OSAL_H

// EOF
