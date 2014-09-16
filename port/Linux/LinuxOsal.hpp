//!
//! @file				LinuxOsal.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-29
//! @last-modified		2014-09-16
//! @brief 				Port-specific operating system abstraction layer for Linux.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_LINUX_OSAL_H
#define MOSAL_LINUX_OSAL_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		class LinuxOsal;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// System headers
//#include <cstdint>		// int8_t, int32_t e.t.c
#include <sys/time.h>		// gettimeofday()
#include <unistd.h>			// usleep(), useconds_t

// User libraries
// none

// User headers
#include "../../include/Osal.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{


		//! @brief		Port-specific operating system abstraction layer for Linux.
		//! @details	Inherits from Osal.
		//! @note
		class LinuxOsal : public Osal
		{

			public:

				//======================================================================================//
				//==================================== PUBLIC METHODS ==================================//
				//======================================================================================//

				//! @brief		Osal constructor.
				LinuxOsal()
				{
	
				}

				~LinuxOsal()
				{

				}
		

				void EnterCriticalSection()
				{
					M_ASSERT_FAIL("%s", "Method not implemented yet!");
				}

				void ExitCriticalSection()
				{
					M_ASSERT_FAIL("%s", "Method not implemented yet!");
				}

				//! @brief		Delays a thread for a certain amount of milliseconds. Allows execution of other threads
				//!				in the interim.
				void ThreadDelayMs(double milliseconds)
				{
					// Call Linux API function usleep()
					usleep((useconds_t)(milliseconds*1000));
				}

				uint32_t GetTimeMs()
				{

					struct timeval te;
					gettimeofday(&te, NULL); // get current time
					long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
					// printf("milliseconds: %lld\n", milliseconds);
					return milliseconds;

				}

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
	
				void (*enterCriticalSection)();
				void (*exitCriticalSection)();
				void (*threadDelayMs)(double milliseconds);
				
			protected:

				//======================================================================================//
				//=================================== PROTECTED METHODS ================================//
				//======================================================================================//
				
				// none
				
				//======================================================================================//
				//================================== PROTECTED VARIABLES ===============================//
				//======================================================================================//

				// none
			
		}; // class LinuxOsal
		
	} // namespace MOsalNs

} // namespace MbeddedNinja

#endif	// #ifndef MOSAL_LINUX_OSAL_H

// EOF
