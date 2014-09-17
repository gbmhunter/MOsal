//!
//! @file				OsalApi.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-07
//! @last-modified		2014-09-17
//! @brief 				
//! @details
//!

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MOSAL_OSAL_API_H
#define MOSAL_OSAL_API_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// User headers
#include "../include/Osal.hpp"
#include "../include/BinarySemaphore.hpp"
#include "../include/Mutex.hpp"
#include "../include/Timer.hpp"
#include "../include/Queue.hpp"

// Do not include port-specific headers here, these are to be selectively included by the user.

#endif	// #ifndef OSAL_CPP_OSAL_API_H

// EOF
