#include "pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Conway {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::Init()
	{
		//Set pattern for log format
		spdlog::set_pattern("%v%$");

		s_CoreLogger = spdlog::stderr_color_mt("Conway Game");
		
		//Set level for output
		s_CoreLogger->set_level(spdlog::level::trace);

	}

	void Log::setLevel(spdlog::level::level_enum level)
	{
		s_CoreLogger->set_level(level);
	}
}