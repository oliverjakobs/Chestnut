#include "chstpch.h"
#include "Log.h"

namespace chst
{
	void Log::Init(const std::string& appname)
	{
		Get()->m_appName = appname;
	}

	void Log::Trace(bool core, const std::string& str)
	{
		if (core)
			std::clog << "[TRACE] " << "[CHESTNUT] " << str << "\n";
		else
			std::clog << "[TRACE] " << "[" << Get()->m_appName << "] " << str << "\n";
	}

	void Log::Info(bool core, const std::string& str)
	{
		if (core)
			std::clog << "[INFO]  " << "[CHESTNUT] " << str << "\n";
		else
			std::clog << "[INFO]  " << "[" << Get()->m_appName << "] " << str << "\n";
	}

	void Log::Warn(bool core, const std::string& str)
	{
		if (core)
			std::clog << "[WARN]  " << "[CHESTNUT] " << str << "\n";
		else
			std::clog << "[WARN]  " << "[" << Get()->m_appName << "] " << str << "\n";
	}

	void Log::Error(bool core, const std::string& str)
	{
		if (core)
			std::clog << "[ERROR] " << "[CHESTNUT] " << str << "\n";
		else
			std::clog << "[ERROR] " << "[" << Get()->m_appName << "] " << str << "\n";
	}
}