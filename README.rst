=====
MOsal
=====

----------------------------------------------------------------------
An C++ operating system abstraction layer (OSAL) for embedded systems.
----------------------------------------------------------------------

.. image:: https://api.travis-ci.org/mbedded-ninja/MOsal.png?branch=master   
	:target: https://travis-ci.org/mbedded-ninja/MOsal

- Author: gbmhunter <gbmhunter@gmail.com> (www.mbedded.ninja)
- Created: 2014-08-07
- Last Modified: 2014-10-14
- Version: v3.7.1.0
- Company: MbeddedNinja
- Project: The Mbedded toolkit (MToolkit) project.
- Language: C++
- Compiler: GCC	
- uC Model: Any
- Computer Architecture: Any
- Operating System: Any (currently FreeRTOS and Linux have the port--specific code written for you!)
- Documentation Format: Doxygen
- License: GPLv3

.. role:: bash(code)
	:language: bash

Description
===========

An operating system abstraction layer for embedded systems. Allows you to use a consistent OS calling interface through-out your code, keeping your code portable across many operating systems. Designed for microcontrollers and operating systems such as FreeRTOS.

The design of this module is structured around platform-specific inhertiance from platform-independant abstract iterface classes, to provide implementations for various operating systems.

Provided OS Utilities
---------------------

- Delays
- Mutexs
- Semaphores
- System time
- Threads
- Timers
- Queues

Easy To Use
------------

All you have to pretty much have to do is download this repo, and include the relevant headers in your embedded (or otherwise) project!

See the Installation section for more details...

Currently Supported OS's
------------------------

- FreeRTOS
- Linux

Note it is easy and encourged for you to port this to a specific OS! Just copy the header files in :code:`port/`, but replace the methods with the OS-specific code!

Supported Compilers
===================

- GCC v4.7 or later


Installation
============

1. Clone the git repo onto your local storage.
2. Include the platform-independent API file :code:`api/MOsalApi.hpp` and the relevant operating system specific headers from :code:'port/'. For example, if you are using FreeRTOS, you would include:

- FreeRtosOsal.hpp
- FreeRtosMutex.hpp
- FreeRtosBinarySemaphore.hpp
- FreeRtosQueue.hpp


Code Dependencies
=================

The following table lists all of MOsal's dependencies. Note that this EXCLUDES the dependecies relevant to the specific operating system you are going to use (i.e. excludes all dependecies of files in :code:`port/`).

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
<ctsdint>              C standard library   For platform agnostic fixed-width integers.
MAssert                External module      Providing runtime csafety checks against this module.
MCallbacks             External module      Method callback functionality to creating and using the :code:`Thread` object.
MUnitTest              External module      Framework for unit tests.
====================== ==================== ======================================================================

Issues
======

See GitHub Issues.

Examples
========

Basic Example Using FreeRTOS As Our Operating System
----------------------------------------------------

::

	// Include the generic OSAL API
	#include "MOsal/api/MOsalApi.hpp"
	
	// We are using FreeRTOS, so include the OS-sepcific FreeRTOS OSAL from port/
	#include "MOsal/port/FreeRtosOsal.hpp"
	
	using namespace MbeddedNinja;
	
	int main()
	{
		// Create a new FreeRTOS operating system abstraction layer
		MOsalNs::Osal * osal = new MOsalNs::FreertosOsal();
		
		// Note, if I was on Linux instead, I could just of easily typed this...
		// MOsalNs::Osal * osal = new MOsalNs::LinuxOsal();
		
		// All done! 
		// Now we can pass the generic OSAL object to other modules
		// that need to make use of operating system features.
		// They don't care whether we use FreeRTOS or Linux!
		CoolModule1 * coolModule1 = new CoolModule1(osal);
		CoolModule2 * coolModule2 = new CoolModule2(osal);
	}
	
FAQ
===

Nothing here yet...

Changelog
=========

========= ========== ===================================================================================================
Version    Date       Comment
========= ========== ===================================================================================================
v3.7.1.0  2014-10-14 Add Thread.hpp to the api file, closes #45.
v3.7.0.0  2014-10-14 Added a thread object for creating platform-independent threads, closes #42. Created a Linux implementation of this thread object along with some unit tests, closes #43. Updated the Makefile to build with thread support (added the compiler option '-pthread'). Tidyied up the README. Updated Makefile to compile with C++11, closes #44.
v3.6.5.0  2014-10-08 Added 'ISR safe' comment to Osal::EnterCriticalSection() and ExitCriticalSection(), closes #40. Improved comments through-out code base. Added IsInCriticalSection() and IsThreadsSuspended() methods to Osal, closes #41.
v3.6.4.0  2014-09-18 Fixed bugs in both 'FreeRtosMutex' and 'FreeRtosBinarySemaphore' where negative values passed as timeouts are not handled correctly, closes #38. Change all usage of doubles to floats, closes #39.
v3.6.3.0  2014-09-18 Fixed bug in FreeRtosQueue::Receive() where double is type cast to an unsigned type then checked if negative, closes #37.
v3.6.2.0  2014-09-18 Added comments to FreeRtosMutex and FreeRtosBinarySemaphore classes about their intended use, closes #36. Fixed up the names of a few of the header guards.
v3.6.1.0  2014-09-18 Added 'const' qualifier to 'FreeRtosQueue::Send()', closes #35.
v3.6.0.0  2014-09-17 Added abstract Queue class and FreeRTOS implementation (the FreeRtosQueue class), closes #34.
v3.5.2.0  2014-09-16 Changed 'Timer::GetRemainingTime()' to 'Timer::GetRemainingTimeMs()' as to indicate the units, closes #31. Capaitilised the R in Freertos in all code and filenames, closes #30. Fixed incorrectly nested forward declarations in FreeRtos port files, closes #32. Added asserts to 'FreertosBinarySemaphore' class, closes #29. Sorted port-specific code by the respective platform and placed in separate folders, closes #33.
v3.5.1.1  2014-09-12 Added 'Build Passing' image to the top of the README, closes #28.
v3.5.1.0  2014-09-12 2nd attempt at trying to get TravisCI to build correctly.
v3.5.0.0  2014-09-12 Updated Makefile to download and build dependencies correctly.
v3.4.1.0  2014-09-12 Added code to .travis.yml file to download the MAssert dependency before building, to try and fix the TravisCI error.
v3.4.0.0  2014-09-12 Added .travis.yml file for TravisCI functionality, closes #3.
v3.3.0.0  2014-09-12 Added Timer::GetState() and the definition for Timer::Reset(). Added appropriate unit tests. Added guard on Timer::Start() so that it only works when timer is in STOPPED or EXPIRED states, closes #15.
v3.2.0.0  2014-09-11 Added Timer::Stop(), Timer::Pause(), Timer::Resume() and Timer::Reset(), closes #27. Also added some helper functions like Timer::GetRemainingTime(). Added two unit tests to test the timer pausing/resuming, and test the start/stopping. Added a 'Provided OS Utilities' section to the README. Changed the use of 'configASSERT()' to use the 'MAssert' module instead, closes #17.
v3.1.0.0  2014-09-11 Renamed module from 'OsalCpp' to 'MOsal' to follow the naming convention of other MToolkit modules, closes #24. Renamed namespaces, classes and Makefile contents appropriately. Fixed Doxygen comments for Timer::Timer(), closes #23. Added 'const' qualifier to Timer::IsExpired(), closes #22. Listed MAssert as a dependency in the README, closes #21. Added ability to see how much time is remaining before a Timer Object exipres, closes #20. Assert failures are called if unimplemented methods of concrete OSALs are called, closes #26. Added function definition for LinuxOsal::ThreadDelayMs(), closes #25.
v3.0.2.0  2014-09-05 Fixed 'vTaskResumeAll()' to correct 'xTaskResumeAll()' in FreertosOsal.hpp, closes #19.
v3.0.1.0  2014-09-05 Added 'SuspendAllThreads()' and 'ResumeAllThreads()' functions to the OsalNs::Osal class, and added overloads for the `FreertosOsal` class, closes #18.
v3.0.0.0  2014-09-05 Created a Timer class for creating timer objects, closes #13. Added unit tests. Added Makefile. Added MUnitTestCpp and MAssertCpp modules as dependencies. Fixed forward declaration of FreertosOsal, closes #15. Put LinuxOsal in OsalNs namespace, closes #14. Added forward declaration to FreertosMutex and FreertosBinarySemaphore objects, closes #16.
v2.0.0.1  2014-08-29 Fixed the code example formatting in the README, closes #10.
v2.0.0.0  2014-08-29 Fixed include file extension from '.h' to '.hpp' in OsalApi.hpp. Changed website references from 'www.cladlab.com' to 'www.mbedded.ninja', closes #7. Embedded 'OsalNs' namespace in 'MbeddedNinja' namespace, closes #8. Added file 'port/LinuxOsal.hpp', which contains a Linux-port of the operating system abstraction layer, closes #6. Made methods of Osal class equal to type pure virtual to force the port-specific versions to implement all required functions. Added mutex and binary semaphore objects with port-sepcific implementations for FreeRTOS, closes #5. Renamed module from 'Osal-Cpp' to 'OsalCpp', closes #4. Added more info about module and examples to README, closes #9.
v1.0.0.0  2014-08-07 Initial commit. Basic Osal class created with support for a thread delay and atomic entry and exit functions.
========= ========== ===================================================================================================