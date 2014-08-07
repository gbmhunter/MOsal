==============================================================
Osal-Cpp
==============================================================

----------------------------------------------------------------------
An C++ operating system abstraction layer (OSAL) for embedded systems.
----------------------------------------------------------------------

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2014-08-07
- Last Modified: 2014-08-07
- Version: v1.0.0.0
- Company: CladLabs
- Project: Free Code Libraries
- Language: C++
- Compiler: GCC	
- uC Model: n/a
- Computer Architecture: n/a
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

.. role:: bash(code)
	:language: bash

Description
===========

An operating system abstraction layer for embedded systems. Allows you to use a consistent OS calling interface through-out your code, keeping your code portable across many operating systems. Designed for microcontrollers and operating systems such as FreeRTOS. 

Easy Including
--------------

All you need to do is include the single header file called :code:`OsalApi.hpp` which is found in the :code:`api/` directory, and provide the compiler with all the files in the :code:`src/` directory.


Installation
============

1. Clone the git repo onto your local storage.


Dependencies
============

The following table lists all of Osal-Cpp's dependencies.

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

Nothing here yet...
	
FAQ
===

Nothing here yet...

Changelog
=========

========= ========== ===================================================================================================
Version    Date       Comment
========= ========== ===================================================================================================
v1.0.0.0  2014-08-07 Initial commit. Basic Osal class created with support for a thread delay and atomic entry and exit functions.
========= ========== ===================================================================================================