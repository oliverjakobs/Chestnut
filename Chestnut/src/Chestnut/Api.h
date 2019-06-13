#pragma once

#ifdef CHST_PLATFORM_WINDOWS
#if CHST_DYNAMIC_LINK
	#ifdef CHST_BUILD_DLL
		#define CHST_API __declspec(dllexport)
	#else
		#define CHST_API __declspec(dllimport)
	#endif
#else
    #define CHST_API
#endif
#else
	#error Chestnut currently only supports Windows!
#endif

#ifdef CHST_DEBUG
	#define CHST_ASSERT(x, ...) { if(!(x)) { CHST_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CHST_CORE_ASSERT(x, ...) { if(!(x)) { CHST_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CHST_ASSERT(x, ...)
	#define CHST_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CHST_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)