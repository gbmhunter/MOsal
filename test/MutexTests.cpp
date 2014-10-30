//!
//! @file 			MutexTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-10-31
//! @last-modified 	2014-10-31
//! @brief 			Contains unit tests which test the Mutex class.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <iostream>				// std::cout

//===== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"
#include "MString/api/MStringApi.hpp"

//===== USER SOURCE =====//
#include "../api/MOsalApi.hpp"				// MOsal::Osal
#include "../port/Linux/LinuxThread.hpp"
#include "../port/Linux/LinuxOsal.hpp"
#include "../port/Linux/LinuxMutex.hpp"		// MOsal::LinuxMutex

using namespace MbeddedNinja;

namespace MOsalTestsNs
{

	MTEST_GROUP(MutexTests)
	{

		//! @brief		A simple test class to use as a dummy class when testing the mutex object.
		class TestClass
		{
			public:

			TestClass(
				MOsal::Osal * osal,
				MOsal::Mutex * mutex,
				char charToPrint,
				MString * stringToPrintTo) :
					osal(osal),
					mutex(mutex),
					charToPrint(charToPrint),
					stringToPrintTo(stringToPrintTo)
			{}

			MOsal::Osal * osal;
			MOsal::Mutex * mutex;
			char charToPrint;
			MString * stringToPrintTo;


			//! @brief		We will use this method as the threads method to call.
			void MethodToCall(bool trueFalse)
			{
				// Let's lock the mutex
				this->mutex->Lock(1000);

				// Print out 10 instances of the character
				// Because of the mutex, these should be printed consecutively
				for(uint8_t x = 0; x < 10; x++)
				{
					this->stringToPrintTo->Append(this->charToPrint);
					this->osal->ThreadDelayMs(20);
				}

				// Add a CR/LF
				this->stringToPrintTo->Append("\r\n");

				// Let's now unlock the mutex and return
				this->mutex->Unlock();
			}

		};


		MTEST(MutexTest)
		{
			// Create a Linux OSAL
			// (change this if running unit tests on different platform)
			MOsal::LinuxOsal linuxOsal;

			// Create a Linux mutex. This will be shared between
			// the two threads
			MOsal::LinuxMutex linuxMutex;

			MString stringToPrintTo;

			TestClass myTestClass1(&linuxOsal, &linuxMutex, '1', &stringToPrintTo);
			TestClass myTestClass2(&linuxOsal, &linuxMutex, '2', &stringToPrintTo);

			// Create callbacks to the test class's method
			MCallbacks::CallbackGen<TestClass, void, bool> myCallBack1(&myTestClass1, &TestClass::MethodToCall);
			MCallbacks::CallbackGen<TestClass, void, bool> myCallBack2(&myTestClass2, &TestClass::MethodToCall);

			// Create two threads which will have to share the mutex
			MOsal::LinuxThread myThread1(myCallBack1);
			MOsal::LinuxThread myThread2(myCallBack2);

			// Lets start the threads
			myThread1.Start();
			myThread2.Start();

			// Give the threads a chance to run
			linuxOsal.ThreadDelayMs(100);

			// Stop the threads
			myThread1.Join();
			myThread2.Join();

			// Need to make sure 10 1's and 10 2's were printed without being interrupted by each other
			CHECK(stringToPrintTo.Find("1111111111") >= 0);
			CHECK(stringToPrintTo.Find("2222222222") >= 0);
		}

	} // MTEST_GROUP(MutexTests)
} // namespace MOsalTestsNs
