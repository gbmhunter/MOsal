//!
//! @file 			main.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-09-05
//! @last-modified 	2014-09-11
//! @brief 			Contains main entry point for unit tests.
//! @details
//!					See README.rst in root dir for more info.

// System libraries
#include <stdio.h>

// User libraries
#include "MUnitTest/api/MUnitTestApi.hpp"

// User source
//#include "../api/OsalApi.hpp"


int main()
{

	return MbeddedNinja::TestRegister::RunAllTests();
	
}
