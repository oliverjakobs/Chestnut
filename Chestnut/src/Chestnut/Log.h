#pragma once

#include "api.h"

#include "chstpch.h"

#include "patterns\Singelton.h"

namespace chst
{
	template <typename... argv>
	std::string stringf(const char* format, argv... args)
	{
		const size_t SIZE = std::snprintf(NULL, 0, format, args...);

		std::string output;
		output.resize(SIZE + 1);
		std::snprintf(&(output[0]), SIZE + 1, format, args...);
		return std::move(output);
	}

	class CHESTNUT_API Log : private Singleton<Log>
	{
	private:
		std::string m_appName;
	public:
		static void Init(const std::string& appname = "APP");

		static void Trace(bool core, const std::string& str);
		static void Info(bool core, const std::string& str);
		static void Warn(bool core, const std::string& str);
		static void Error(bool core, const std::string& str);
	};
}

// Core log macros
#define CHST_CORE_TRACE(s, ...)    chst::Log::Trace(true, chst::stringf(s, __VA_ARGS__))
#define CHST_CORE_INFO(s, ...)     chst::Log::Info(true, chst::stringf(s, __VA_ARGS__))
#define CHST_CORE_WARN(s, ...)     chst::Log::Warn(true, chst::stringf(s, __VA_ARGS__))
#define CHST_CORE_ERROR(s, ...)    chst::Log::Error(true, chst::stringf(s, __VA_ARGS__))

// Client log macros
#define CHST_TRACE(s)     chst::Log::Trace(false, s)
#define CHST_INFO(s)      chst::Log::Info(false, s)
#define CHST_WARN(s)      chst::Log::Warn(false, s)
#define CHST_ERROR(s)     chst::Log::Error(false, s)