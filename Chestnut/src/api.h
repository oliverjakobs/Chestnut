#pragma once

#ifdef CHST_EXPORTS
	#define CHESTNUT_API __declspec(dllexport)
#else
	#define CHESTNUT_API __declspec(dllimport)
#endif

#ifdef CHST_ENABLE_ASSERTS
	#define CHST_ASSERT(x, ...) { if(!(x)) { GOLEM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CHST_CORE_ASSERT(x, ...) { if(!(x)) { GOLEM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CHST_ASSERT(x, ...)
	#define CHST_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SAFE_DELETE(ptr) { if((ptr) != nullptr) delete (ptr); (ptr) = nullptr; }