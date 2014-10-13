//!
//! @file				OsalApi.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-07
//! @last-modified		2014-10-14
//! @brief 				The single header to include when using the OSAL module.
//! @details
//!

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef M_OSAL_OSAL_API_H
#define M_OSAL_OSAL_API_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== USER SOURCE =====//
#include "../include/BinarySemaphore.hpp"
#include "../include/Mutex.hpp"
#include "../include/Osal.hpp"
#include "../include/Thread.hpp"
#include "../include/Timer.hpp"
#include "../include/Queue.hpp"

// Do not include port-specific headers here, these are to be selectively included by the user.

#endif	// #ifndef M_OSAL_OSAL_API_H

// EOF
