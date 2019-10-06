#pragma once

#include <memory>

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
	#error Chestnut only supports Windows!
#endif

#ifdef CHST_DEBUG
	#define CHST_ENABLE_ASSERTS
#endif

#ifdef CHST_ENABLE_ASSERTS
	#define CHST_ASSERT(x, ...) { if(!(x)) { CHST_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CHST_CORE_ASSERT(x, ...) { if(!(x)) { CHST_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CHST_ASSERT(x, ...)
	#define CHST_CORE_ASSERT(x, ...)
#endif


// Utility
#define BIT(x) (1 << x)

#define CHST_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// types
namespace chst
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
