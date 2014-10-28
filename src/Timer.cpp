//!
//! @file				Timer.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-05
//! @last-modified		2014-10-29
//! @brief 				Timer object.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// int8_t, int32_t e.t.c

//! @debug
//#include <iostream>		// std::cout, std::endl

//===== USER LIBRARIES =====//
// none

//===== USER SOURCE =====//
#include "../include/Timer.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MOsalNs
	{

		Osal * Timer::osal = nullptr;

		void Timer::StaticInit(Osal * osal)
		{
			// Make sure OSAL is not null
			M_ASSERT(osal);

			Timer::osal = osal;
		}

		//! @brief		Binary semaphore constructor.
		//! @details	Protected to enforce inheritance.
		Timer::Timer(uint32_t timeoutInMs) :
				// Transition into the WAITING_FOR_START state on Timer object creation
				timerState(TimerStates::STOPPED),
				elapsedTimeInPreviousRunStatesInMs(0)
		{
			if(!Timer::osal)
				M_ASSERT_FAIL("%s", "Please call Timer::StaticInit() before creating any Timer object.");

			// Save the timeout time
			this->timeoutInMs = timeoutInMs;
		};

		void Timer::Start()
		{
			// Only start the timer if it is in the STOPPED or EXPIRED states
			if(this->timerState == TimerStates::STOPPED || this->timerState == TimerStates::EXPIRED)
			{
				// Get the current time from the OSAL
				// and save as the current start time
				this->latestRunStartTimeInMs = Timer::osal->GetTimeMs();

				// Transition to the running state
				this->timerState = TimerStates::RUNNING;
			}
		}

		void Timer::Stop()
		{
			if(this->timerState != TimerStates::STOPPED)
			{
				// Reset the elapsed time
				this->elapsedTimeInPreviousRunStatesInMs = 0;

				// Transition to the stopped state
				this->timerState = TimerStates::STOPPED;
			}
		}

		void Timer::Reset()
		{
			if(this->timerState == TimerStates::RUNNING || this->timerState == TimerStates::PAUSED)
			{
				// If the timer is in a running or paused state, reset causes the timer to
				// start running again
				this->Stop();
				this->Start();
			}
			else if(this->timerState == TimerStates::EXPIRED)
			{
				// Just push the timer back into the STOPPED state
				// if it has expired
				this->Stop();
			}
		}

		void Timer::Pause()
		{
			if(this->timerState == TimerStates::RUNNING)
			{
				//std::cout << "Pausing timer..." << std::endl;
				// Add the current run timer since timer was last started/un-paused to the total elapsed time
				this->elapsedTimeInPreviousRunStatesInMs += Timer::osal->GetTimeMs() - this->latestRunStartTimeInMs;

				//std::cout <<
				//	"elapsedTimeInPreviousRunStatesInMs now = '" <<
				//	this->elapsedTimeInPreviousRunStatesInMs << "'." << std::endl;

				// Transition to PAUSED state
				this->timerState = TimerStates::PAUSED;
			}
		}

		void Timer::Resume()
		{
			//std::cout << "Timer::Resume() called." << std::endl;
			if(this->timerState == TimerStates::PAUSED)
			{
				//std::cout << "Resuming timer..." << std::endl;

				// Update the latest run time to the current system time
				this->latestRunStartTimeInMs = Timer::osal->GetTimeMs();

				//std::cout <<
				//	"Timer::GetElapsedTimeMs() = '" <<
				//	Timer::GetElapsedTimeMs() << "'." << std::endl;

				// Transition to RUNNING state
				this->timerState = TimerStates::RUNNING;
			}
		}

		Timer::TimerStates Timer::GetState()
		{
			// Since this could be called while the timer is running,
			// we first need to check to see if the timer has expired.
			this->CheckForExpiry();

			// Now we will be returning the correct state
			return this->timerState;
		}

		bool Timer::IsExpired()
		{
			// Use another method to do most of the calculation
			//std::cout << "Elapsed time = '" << this->GetElapsedTimeMs() << "'." << std::endl;
			if(this->GetElapsedTimeMs() >= this->timeoutInMs)
			{
				// Transition to the expired state
				this->timerState = TimerStates::EXPIRED;
				return true;
			}
			else
				return false;

		}

		uint64_t Timer::GetElapsedTimeMs() const
		{
			//std::cout << "Timer::GetElapsedTimeMs() called." << std::endl;
			//std::cout << "this->elapsedTimeInPreviousRunStatesInMs = '" <<
			//		this->elapsedTimeInPreviousRunStatesInMs << "'." << std::endl;


			if(this->timerState == TimerStates::RUNNING)
			{
				//std::cout << "Latest run time = '" <<
				//	Timer::osal->GetTimeMs() - this->latestRunStartTimeInMs <<
				//	"'." << std::endl;


				// Total elapsed time is the sum of the elapsed time variable and the current run time since
				// the timer was last un-paused (or started).
				return this->elapsedTimeInPreviousRunStatesInMs + (Timer::osal->GetTimeMs() - this->latestRunStartTimeInMs);
			}
			else
			{
				// Since we are not running, just return the time record in
				// the elapsed variable
				return this->elapsedTimeInPreviousRunStatesInMs;
			}

		}

		uint64_t Timer::GetRemainingTimeMs() const
		{
			// We have to take a snapshot of the elapsed time, because we use it multiple times in this
			// function, at the value could change between calls to this->GetElapsedTimeMs()
			uint32_t elapsedTimeMs = this->GetElapsedTimeMs();
			if(this->timeoutInMs > elapsedTimeMs)
			{
				// We havn't expired yet, so return the difference in ms
				return this->timeoutInMs - elapsedTimeMs;
			}
			else
				// Timer must of expired, so return 0
				return 0;

		}

		void Timer::CheckForExpiry()
		{
			// Check to see if the elapsed time has exceeded the timeout time
			if(this->GetElapsedTimeMs() >= this->timeoutInMs)
			{
				// Transition to the expired state
				this->timerState = TimerStates::EXPIRED;
			}
		}

	}
} // namespace MbeddedNinja

// EOF
