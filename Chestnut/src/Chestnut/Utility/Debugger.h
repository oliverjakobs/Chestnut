#pragma once

#include "Logger.h"
#include "Timer.h"

#if _DEBUG
	
#define OBILISK_LOGGING
#define OBILISK_ASSERT
#define OBILISK_TIMER

#endif

// -----------------------------------------------------------------------------------
// Logging
// -----------------------------------------------------------------------------------
#ifdef OBILISK_LOGGING

#define DEBUG_INFO(s, ...)		obelisk::Logger::Info(s, __VA_ARGS__)
#define DEBUG_TRACE(s, ...)		obelisk::Logger::Trace(s, __VA_ARGS__)
#define DEBUG_WARN(s, ...)		obelisk::Logger::Warn(s, __VA_ARGS__)
#define DEBUG_ERROR(s, ...)		obelisk::Logger::Error(s, __VA_ARGS__)
#define DEBUG_CRITICAL(s, ...)	obelisk::Logger::Critical(s, __VA_ARGS__)

#else

#define DEBUG_INFO(s, ...)
#define DEBUG_TRACE(s, ...)
#define DEBUG_WARN(s, ...)
#define DEBUG_ERROR(s, ...)
#define DEBUG_CRITICAL(s, ...)

#endif

// -----------------------------------------------------------------------------------
// Assert
// -----------------------------------------------------------------------------------
#ifdef OBILISK_ASSERT

#define DEBUG_ASSERT(x, ...) { if(!(x)) { DEBUG_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

#define DEBUG_ASSERT(x, ...)

#endif

// -----------------------------------------------------------------------------------
// Timer
// -----------------------------------------------------------------------------------
#ifdef OBILISK_TIMER

#define DEBUG_TIMER()				obelisk::Timer timer
#define DEBUG_TIMER_GET_ELAPSED()	timer.GetElapsedMS()
#define DEBUG_TIMER_RESET()			timer.Reset()

#define DEBUG_TIMER_TRACE(s)		DEBUG_TRACE(s, timer.GetElapsedMS())

#else

#define DEBUG_TIMER()
#define DEBUG_TIMER_GET_ELAPSED()
#define DEBUG_TIMER_RESET()

#define DEBUG_TIMER_TRACE(s)

#endif