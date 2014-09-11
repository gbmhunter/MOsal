//!
//! @file				Timer.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-05
//! @last-modified		2014-09-11
//! @brief 				Timer object.
//! @details
//!						

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System libraries
#include <cstdint>		// int8_t, int32_t e.t.c

//! @debug
//#include <iostream>		// std::cout, std::endl

// User libraries
// none

// User source
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

			// Get the current time from the OSAL
			// and save as the current start time
			this->latestRunStartTimeInMs = Timer::osal->GetTimeMs();

			// Transition to the running state
			this->timerState = TimerStates::RUNNING;
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

		uint32_t Timer::GetElapsedTimeMs() const
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

		uint32_t Timer::GetRemainingTime() const
		{
			// If in exipred state, return 0, else a negative number would be returned!
			if(this->timerState == TimerStates::EXPIRED)
			{
				return 0;
			}
			else
			{
				return this->timeoutInMs - this->GetElapsedTimeMs();
			}
		}

	}
} // namespace MbeddedNinja

// EOF
