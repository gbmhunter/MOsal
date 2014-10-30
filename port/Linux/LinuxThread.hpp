//!
//! @file				LinuxThread.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-13
//! @last-modified		2014-10-30
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
	namespace MOsal
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
	namespace MOsal
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

			//! @brief		Simplified constructor.
			LinuxThread() :
				Thread()
			{

			}

			~LinuxThread()
			{
				// No tear down required
			}

			void AssignThreadMethod(MCallbacks::Callback<void, bool> threadMethod)
			{
				// Save threadMethod to internal variable
				this->threadMethod = threadMethod;
			}

			void Start()
			{
				// Make sure a callback thread method has been assigned
				M_ASSERT(this->threadMethod.IsValid());

				// Set stop thread to false, which could of been set to true if the
				// thread has been previously stopped
				this->stopThread = false;

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
			void Join()
			{
				this->myThread->join();
			}

			void Stop()
			{
				// All we can do here is set a flag to true, it is up to the running threads method
				// to check this and exit occordingly.
				this->stopThread = true;
			}

			private:

			std::thread * myThread;


		}; // class LinuxThread
		
	} // namespace MOsalNs
} // namespace MbeddedNinja

#endif	// #ifndef M_OSAL_LINUX_THREAD_H

// EOF
