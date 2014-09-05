==============================================================
Osal-Cpp
==============================================================

----------------------------------------------------------------------
An C++ operating system abstraction layer (OSAL) for embedded systems.
----------------------------------------------------------------------

- Author: gbmhunter <gbmhunter@gmail.com> (www.mbedded.ninja)
- Created: 2014-08-07
- Last Modified: 2014-09-05
- Version: v3.0.2.0
- Company: MbeddedNinja
- Project: The Mbedded toolkit project.
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

The following table lists all of Osal-Cpp's dependencies. Note that this EXCLUDES the dependecies relevant to the specific operating system you are going to use (i.e. excludes all dependecies of files in :code:'port/').

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
<ctsdint>              C standard library   For platform agnostic fixed-width integers.
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
	#include "OsalCpp/api/OsalApi.hpp"
	
	// We are using FreeRTOS, so include the OS-sepcific FreeRTOS OSAL from port/
	#include "OsalCpp/port/FreertosOsal.hpp"
	
	using namespace MbeddedNinja;
	
	int main()
	{
		// Create a new FreeRTOS operating system abstraction layer
		OsalNs::Osal * osal = new OsalNs::FreertosOsal();
		
		// Note, I could just of easily typed this...
		// OsalNs::Osal * osal = new OsalNs::LinuxOsal();
		
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
v3.0.2.0  2014-09-05 Fixed 'vTaskResumeAll()' to correct 'xTaskResumeAll()' in FreertosOsal.hpp, closes #19.
v3.0.1.0  2014-09-05 Added 'SuspendAllThreads()' and 'ResumeAllThreads()' functions to the OsalNs::Osal class, and added overloads for the `FreertosOsal` class, closes #18.
v3.0.0.0  2014-09-05 Created a Timer class for creating timer objects, closes #13. Added unit tests. Added Makefile. Added MUnitTestCpp and MAssertCpp modules as dependencies. Fixed forward declaration of FreertosOsal, closes #15. Put LinuxOsal in OsalNs namespace, closes #14. Added forward declaration to FreertosMutex and FreertosBinarySemaphore objects, closes #16.
v2.0.0.1  2014-08-29 Fixed the code example formatting in the README, closes #10.
v2.0.0.0  2014-08-29 Fixed include file extension from '.h' to '.hpp' in OsalApi.hpp. Changed website references from 'www.cladlab.com' to 'www.mbedded.ninja', closes #7. Embedded 'OsalNs' namespace in 'MbeddedNinja' namespace, closes #8. Added file 'port/LinuxOsal.hpp', which contains a Linux-port of the operating system abstraction layer, closes #6. Made methods of Osal class equal to type pure virtual to force the port-specific versions to implement all required functions. Added mutex and binary semaphore objects with port-sepcific implementations for FreeRTOS, closes #5. Renamed module from 'Osal-Cpp' to 'OsalCpp', closes #4. Added more info about module and examples to README, closes #9.
v1.0.0.0  2014-08-07 Initial commit. Basic Osal class created with support for a thread delay and atomic entry and exit functions.
========= ========== ===================================================================================================