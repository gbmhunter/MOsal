//!
//! @file 			BasicTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-09-04
//! @last-modified 	2014-09-04
//! @brief 			Contains basic tests.
//! @details
//!					See README.rst in root dir for more info.

// System libraries
#include <iostream>

// User libraries
#include "MUnitTestCpp/api/MUnitTestApi.hpp"

// User source
#include "../api/OsalApi.hpp"
#include "../port/LinuxOsal.hpp"

using namespace MbeddedNinja;

namespace OsalTestsNs
{

	MTEST(TimerTest)
	{
		// Create a Linux OSAL
		// (change this if running unit tests on different platform)
		OsalNs::LinuxOsal linuxOsal;
		OsalNs::Timer::StaticInit(&linuxOsal);
		OsalNs::Timer timer1(2000);
		std::cout << "Timer should now wait 2s..." << std::endl;
		timer1.Start();

		while(!timer1.IsExpired());
		std::cout << "Timer expired." << std::endl;
		// Check capacity is calculated correctly
		//CHECK_EQUAL("Testing", "Testing1");
	}

} // namespace OsalTestsNs
