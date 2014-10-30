//!
//! @file				Timer.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-05
//! @last-modified		2014-10-30
//! @brief 				Timer object.
//! @details
//!					

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_TIMER_H
#define MOSAL_TIMER_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsal
	{
		class Timer;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// int8_t, int32_t e.t.c

//===== USER LIBRARIES =====//
#include "MAssert/api/MAssertApi.hpp"

//===== USER SOURCE =====//
#include "Osal.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsal
	{
		
		//! @brief
		//! @details
		//! @note
		class Timer
		{
			
		public:

			//! @brief 		Enumerates the possible states the timer can be in.
			//! @details	Used internally to keep track of the timer state, also returned by the function GetState().
			enum class TimerStates : uint8_t
			{
				//! Timer has been created but either Start() has not been called or Reset()
				//! has been recently called.
				STOPPED,
				//! Timer is currently running, and the timer will transition to the expired state
				//! when it times out.
				RUNNING,
				//! Timer is currently paused. It can be resumed by calling Resume().
				PAUSED,
				//! Timer has expired. Call Reset() to transition back to the STOPPED state,
				//! or Start() to start the timer again.
				EXPIRED
			};

			//======================================================================================//
			//==================================== PUBLIC METHODS ==================================//
			//======================================================================================//

			//! @brief		Static initialisation for all Timer objects.
			//! @warning	You must call this before creating a timer object, otherwise
			//!				an assert will be raised.
			static void StaticInit(Osal * osal);

			//! @brief		Timer constructor.
			//! @param		timeoutInMs		The timeout period for this timer. The timer starts couting once
			//!								you call Start().
			Timer(uint32_t timeoutInMs);

			//! @brief		Starts the timer.
			//! @details	No effect unless the timer is in the STOPPED state (which is the
			//!				initial state when you create a new timer object).
			void Start();

			//! @brief		Stops the timer and reset the elapsed time.
			//!	@details	This causes the timer to enter the STOPPED state
			//!				when it is any other state.
			void Stop();

			//! @brief		Pauses the timer.
			//! @details	Has no effect unless the timer is currently in the RUNNING state.
			void Pause();

			//! @brief		Resumes the timer (so it is in the running state).
			//! @details	Has no effect unless the timer is currently in the PAUSED state.
			void Resume();

			//! @brief		Resets the elapsed time back to 0, but doesn't stop the timer if it is
			//!				running or paused (use Stop() to do this).
			//! @details	Use to reset the "countdown" while it is running.
			void Reset();

			//! @brief		Use to determine what state the Timer is in.
			//! @returns	The state the Timer is in.
			TimerStates GetState();

			//! @brief		Call this to easily check if the timer has expired. Not const because it will change the timer to the expired state if needed.
			//! @details	You can also determine if the timer has expired by calling GetState().
			//! @returns	True if the timer has expired, otherwise false.
			bool IsExpired();

			//! @returns	The elapsed time (total run time) of the timer. Will keep working
			//!				even after the timer has gone into the EXPIRED state, this function will
			//!				just return a number higher than timeoutInMs.
			uint64_t GetElapsedTimeMs() const;

			//! @brief		Call to find out how much time (in milliseconds) the timer has left
			//!				remaining until it expires.
			//! @returns	The amount of time the timer has left until it expires, in milliseconds.
			//!				Returns 0 if the timer has expired.
			uint64_t GetRemainingTimeMs() const;

			//======================================================================================//
			//================================= PUBLIC VARIABLES ===================================//
			//======================================================================================//

			// none

			private:

			//======================================================================================//
			//=================================== PRIVATE METHODS ==================================//
			//======================================================================================//

			//! @brief		Checks and changes the timers state if neccessary
			void CheckForExpiry();

			//======================================================================================//
			//================================== PRIVATE VARIABLES =================================//
			//======================================================================================//

			//! @brief		Pointer to the operating system abstraction layer object.
			//! @details	Initialised in StaticInit().
			static Osal * osal;

			//! @brief		Holds the current state of the timer.
			TimerStates timerState;

			//! @brief		Remembers the system time at which Start() was called.
			uint64_t latestRunStartTimeInMs;

			//! @brief		Remembers the elpased time in ms. Useful for when Pause() and Resume() are used.
			uint64_t elapsedTimeInPreviousRunStatesInMs;

			//! @brief		Remembers the time at which the timer will timeout at.
			uint64_t timeoutInMs;

			protected:
	
			//======================================================================================//
			//=================================== PROTECTED METHODS ================================//
			//======================================================================================//



			//======================================================================================//
			//================================== PROTECTED VARIABLES ===============================//
			//======================================================================================//

			
		}; // class Timer


	} // namespace MOsalNs
} // namespace MbeddedNinja

#endif	// #ifndef MOSAL_TIMER_H

// EOF
