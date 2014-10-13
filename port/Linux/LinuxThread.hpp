//!
//! @file				LinuxThread.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-14
//! @last-modified		2014-10-14
//! @brief 				Port-specific thread abstraction layer for Linux.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef M_OSAL_LINUX_THREAD_H
#define M_OSAL_LINUX_THREAD_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		class LinuxThread;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
//#include <cstdint>		// int8_t, int32_t e.t.c
#include <thread>			// std::thread

//===== USER LIBRARIES =====//
#include "MAssert/api/MAssertApi.hpp"

//===== USER SOURCE =====//
#include "../../include/Thread.hpp"
#include "../../include/Osal.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{


		//! @brief		Port-specific thread abstraction layer for Linux.
		//! @note		Inherits from Thread. See the Thread class for method descriptions.
		class LinuxThread : public Thread
		{

			public:


			//! @brief		Osal constructor.
			LinuxThread(MCallbacks::Callback<void, bool> threadMethod) :
				Thread(threadMethod)
			{

			}

			~LinuxThread()
			{
				// No tear down required
			}

			void Start()
			{
				// Create thread, which automatically starts it
				this->myThread = new std::thread(&LinuxThread::Runner, this);
			}

			void Runner()
			{
				// Just call it once
				this->threadMethod.Execute(true);

			}

			//! @brief
			//!	@details
			void Stop()
			{
				this->myThread->join();
			}

			private:

			std::thread * myThread;


		}; // class LinuxThread
		
	} // namespace MOsalNs

} // namespace MbeddedNinja

#endif	// #ifndef M_OSAL_LINUX_THREAD_H

// EOF
