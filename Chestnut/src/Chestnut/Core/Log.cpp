#include "chstpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace chst
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init(const std::string& appname)
	{
		spdlog::set_pattern("[%^%l%$] %v");
		s_CoreLogger = spdlog::stdout_color_mt("CHST");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt(appname);
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}