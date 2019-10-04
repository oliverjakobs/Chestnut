#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace chst
{
	class CHST_API Log
	{
	public:
		static void Init(const std::string& appname);

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define CHST_CORE_TRACE(...)    chst::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CHST_CORE_INFO(...)     chst::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CHST_CORE_WARN(...)     chst::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CHST_CORE_ERROR(...)    chst::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CHST_CORE_CRITICAL(...) chst::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define CHST_TRACE(...)         chst::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CHST_INFO(...)          chst::Log::GetClientLogger()->info(__VA_ARGS__)
#define CHST_WARN(...)          chst::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CHST_ERROR(...)         chst::Log::GetClientLogger()->error(__VA_ARGS__)
#define CHST_CRITICAL(...)      chst::Log::GetClientLogger()->critical(__VA_ARGS__)
