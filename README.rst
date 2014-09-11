=====
MOsal
=====

----------------------------------------------------------------------
An C++ operating system abstraction layer (OSAL) for embedded systems.
----------------------------------------------------------------------

- Author: gbmhunter <gbmhunter@gmail.com> (www.mbedded.ninja)
- Created: 2014-08-07
- Last Modified: 2014-09-12
- Version: v3.3.0.0
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

Uses inhertiance from an abstract iterface class (the Osal class), to provide implementations for various operating systems. 

Provided OS Utilities
---------------------

- Mutexs
- Semaphores
- System time
- Timers

Easy To Use
------------

All you have to pretty much have to do is download this repo, and include the relevant headers in your embedded (or otherwise) project!

See the Installation section for more details...

Currently Supported OS's
------------------------

- FreeRTOS
- Linux

Note it is easy and encourged for you to port this to a specific OS! Just copy the header files in :code:'port/', but replace the methods with the OS-specific code!

Supported Compilers
===================

- GCC v4.7 or later


Installation
============

1. Clone the git repo onto your local storage.
2. Include the relevant operating system specific headers from :code:'port/'. For example, if you are using FreeRTOS, you would include:

- FreertosOsal.hpp
- FreertosMutex.hpp
- FreertosBinarySemaphore.hpp


Code Dependencies
=================

The following table lists all of MOsal's dependencies. Note that this EXCLUDES the dependecies relevant to the specific operating system you are going to use (i.e. excludes all dependecies of files in :code:'port/').

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
<ctsdint>              C standard library   For platform agnostic fixed-width integers.
MAssert                External module      Providing runtime csafety checks against this module.
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
	#include "MOsal/port/FreertosOsal.hpp"
	
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