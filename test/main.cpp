//!
//! @file 			main.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-09-05
//! @last-modified 	2014-09-11
//! @brief 			Contains main entry point for unit tests.
//! @details
//!					See README.rst in root dir for more info.

// System libraries
#include <iostream>

// User libraries
#include "MUnitTest/api/MUnitTestApi.hpp"

// User source
// none


int main()
{
	// Give a little note about how these tests may
	// take a few seconds to run...
	std::cout << "Note: These timer unit tests will take some time (e.g. seconds), \r\n"
			"as they use OS thread pauses to make sure that the timers work correctly \r\n"
			"(e.g. expire at the right time)." << std::endl;

	// Run all unit tests and return the result
	return MbeddedNinja::TestRegister::RunAllTests();
	
}
