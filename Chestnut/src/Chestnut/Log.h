#pragma once

#include "api.h"

#include "Patterns\Singelton.h"
#include "utils.h"

namespace chst
{
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