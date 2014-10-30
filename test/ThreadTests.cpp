//!
//! @file 			ThreadTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-10-13
//! @last-modified 	2014-10-28
//! @brief 			Contains unit tests which test the Thread class.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
//#include <iostream>

//===== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MOsalApi.hpp"
#include "../port/Linux/LinuxThread.hpp"
#include "../port/Linux/LinuxOsal.hpp"

using namespace MbeddedNinja;

namespace MOsalTestsNs
{
	//! @brief		A simple test class to use as a dummy class when testing the Thread object.
	class TestClass
	{
		public:

		TestClass() :
			hasBeenCalled(false)
		{}

		//! @brief		This variable should be set to true when the thread runs.
		bool hasBeenCalled;

		//! @brief		We will use this method as the threads method to call.
		void MethodToCall(bool trueFalse)
		{
			hasBeenCalled = true;
		}

	};


	MTEST(ThreadTest)
	{
		// Create a Linux OSAL
		// (change this if running unit tests on different platform)
		MOsal::LinuxOsal linuxOsal;

		TestClass myTestClass;

		// Create callback to the test class's method
		MCallbacks::CallbackGen<TestClass, void, bool> myCallBack(&myTestClass, &TestClass::MethodToCall);

		// Create a new thread
		MOsal::LinuxThread myThread(myCallBack);

		// Thread should not have started running yet
		CHECK_EQUAL(myTestClass.hasBeenCalled, false);

		// Lets start the thread
		myThread.Start();

		// Give the thread a chance to run
		linuxOsal.ThreadDelayMs(100);

		// Stop the thread
		myThread.Join();

		// The new thread should have run, and the var hasBeenCalled
		// set to true
		CHECK_EQUAL(myTestClass.hasBeenCalled, true);
	}

	MTEST(StopThenStartThreadAgainTest)
	{
		// Create a Linux OSAL
		// (change this if running unit tests on different platform)
		MOsal::LinuxOsal linuxOsal;

		TestClass myTestClass;

		// Create callback to the test class's method
		MCallbacks::CallbackGen<TestClass, void, bool> myCallBack(&myTestClass, &TestClass::MethodToCall);

		// Create a new thread
		MOsal::LinuxThread myThread(myCallBack);

		// Thread should not have started running yet
		CHECK_EQUAL(myTestClass.hasBeenCalled, false);

		// Lets start the thread
		myThread.Start();

		// Give the thread a chance to run
		linuxOsal.ThreadDelayMs(100);

		// Stop the thread
		myThread.Join();

		// The new thread should have run, and the var hasBeenCalled
		// set to true
		CHECK_EQUAL(myTestClass.hasBeenCalled, true);

		// Now set that boolean back to false
		myTestClass.hasBeenCalled = false;

		// Lets start the thread
		myThread.Start();

		// Give the thread a chance to run
		linuxOsal.ThreadDelayMs(100);

		// Stop the thread
		myThread.Join();

		// The new thread should have run, and the var hasBeenCalled
		// set to true
		CHECK_EQUAL(myTestClass.hasBeenCalled, true);

	}

} // namespace MOsalTestsNs
