//!
//! @file 			TimerTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-09-11
//! @last-modified 	2014-09-11
//! @brief 			Contains unit tests which test the Timer class.
//! @details
//!					See README.rst in root dir for more info.

// System libraries
#include <iostream>

// User libraries
#include "MUnitTest/api/MUnitTestApi.hpp"

// User source
#include "../api/MOsalApi.hpp"
#include "../port/LinuxOsal.hpp"

using namespace MbeddedNinja;

namespace MOsalTestsNs
{

	MTEST(StartStopTimerTest)
	{
		// Create a Linux OSAL
		// (change this if running unit tests on different platform)
		MOsalNs::LinuxOsal linuxOsal;
		MOsalNs::Timer::StaticInit(&linuxOsal);
		MOsalNs::Timer timer1(500);

		// Start timer
		timer1.Start();

		linuxOsal.ThreadDelayMs(250);

		// Stop the timer half way through
		timer1.Stop();

		// Timer shouldn't have expired
		CHECK(!timer1.IsExpired());

		// Delay for another half
		linuxOsal.ThreadDelayMs(250);

		// If timer hadn't been stopped it would
		// be expired here
		CHECK(!timer1.IsExpired());

		// Lets start it up again
		timer1.Start();

		// Timer shouldn't have expired
		CHECK(!timer1.IsExpired());

		// Delay to half way through again
		linuxOsal.ThreadDelayMs(250);

		// Timer shouldn't have expired
		CHECK(!timer1.IsExpired());

		// Lets not stop this time, but keep going
		linuxOsal.ThreadDelayMs(250);

		// Finally, now the timer should have expired
		CHECK(timer1.IsExpired());
	}

	MTEST(ExpiredTimerTest)
	{
		// Create a Linux OSAL
		// (change this if running unit tests on different platform)
		MOsalNs::LinuxOsal linuxOsal;
		MOsalNs::Timer::StaticInit(&linuxOsal);
		MOsalNs::Timer timer1(200);

		// Start timer
		timer1.Start();

		// Timer should of not expired!
		CHECK(!timer1.IsExpired());

		linuxOsal.ThreadDelayMs(100);

		// Timer still shouldn't have expired!
		CHECK(!timer1.IsExpired());

		linuxOsal.ThreadDelayMs(100);

		// Finally, now the timer should have expired
		CHECK(timer1.IsExpired());
	}

	MTEST(PauseTimerTest)
	{
		MOsalNs::LinuxOsal linuxOsal;
		MOsalNs::Timer::StaticInit(&linuxOsal);

		MOsalNs::Timer timer1(1000);
		timer1.Start();

		CHECK(!timer1.IsExpired());

		//std::cout << "Delaying by 1s." << std::endl;

		linuxOsal.ThreadDelayMs(500);

		//std::cout << "Calling timer1.Pause()." << std::endl;

		// Pause the timer 1s into it's 2s period
		timer1.Pause();

		//std::cout << "Timer just puased." << std::endl;
		CHECK(!timer1.IsExpired());

		//std::cout << "Delaying by 2s." << std::endl;

		// Lets wait two seconds with the timer paused
		linuxOsal.ThreadDelayMs(1000);

		// Make sure the timer hasn't expired
		// (it shouldn't of because it has been paused)
		CHECK(!timer1.IsExpired());

		// Now lets unpause it
		timer1.Resume();

		//std::cout << "Delaying by 1s." << std::endl;

		// Now let's wait another second with the timer
		// running again, this should cause it to expire
		linuxOsal.ThreadDelayMs(500);

		CHECK(timer1.IsExpired());
	}


} // namespace MOsalTestsNs