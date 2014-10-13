//!
//! @file				Thread.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-12
//! @last-modified		2014-10-12
//! @brief 				A platform-independent OSAL thread object.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef M_OSAL_THREAD_H
#define M_OSAL_THREAD_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		class Thread;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// int8_t, int32_t e.t.c

//===== USER LIBRARIES =====//
#include "MAssert/api/MAssertApi.hpp"
#include "MCallbacks/api/MCallbacksApi.hpp"

//===== USER SOURCE =====//
#include "Osal.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{
		
		//! @brief
		//! @details
		//! @note
		class Thread
		{
			
			public:

			//! @brief 		Enumerates the possible states the thread can be in.
			//! @details	Used internally to keep track of the thread state, also returned by the function GetState().
			enum class ThreadStates : uint8_t
			{
				//! Timer has been created but Start() has not been called, or thread was running and
				//! Stop() was called.
				STOPPED,
				//! Thread is currently running
				RUNNING
			};

			//======================================================================================//
			//==================================== PUBLIC METHODS ==================================//
			//======================================================================================//

			//! @brief		Static initialisation for all Timer objects.
			//! @warning	You must call this before creating a timer object, otherwise
			//!				an assert will be raised.
			static void StaticInit(Osal * osal);


			//! @brief		Thread destructor.
			virtual ~Thread(){};

			//! @brief		Starts the thread.
			//! @details
			virtual void Start() = 0;

			//! @brief		Stops the thread.
			//!	@details	This causes the thread to enter the STOPPED state when it is any other state. This has to be called when using the Linux implementation before main() exits, otherwise an exception will be thrown (this calls join()).
			virtual void Stop() = 0;

			//! @brief		Use to determine what state the thread is in.
			//! @returns	The state the thread is in.
			ThreadStates GetState();

			protected:

			//! @brief		Thread constructor. Protected to forced inheritance.
			//! @details	Thread is NOT started on construction. Start() has to be called to start the thread.
			//! @param		threadMethod		The method to call when the thread starts running.
			Thread(MCallbacks::Callback<void, bool> threadMethod);

			//======================================================================================//
			//================================= PUBLIC VARIABLES ===================================//
			//======================================================================================//

			// none

			protected:


			//! @brief		Pointer to the operating system abstraction layer object.
			//! @details	Initialised in StaticInit().
			static Osal * osal;

			//! @brief		Holds the current state of the timer.
			ThreadStates threadState;

			//! @brief		Holds a callback to the method to call when the thread starts running.
			MCallbacks::Callback<void, bool> threadMethod;

			
		}; // class Thread


	} // namespace MOsalNs
} // namespace MbeddedNinja

#endif	// #ifndef M_OSAL_THREAD_H

// EOF
