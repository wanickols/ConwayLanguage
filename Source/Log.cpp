#include "pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Conway {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::Init()
	{
		//Set pattern for log format
		spdlog::set_pattern("%^[T] %n: %v%$");

		s_CoreLogger = spdlog::stderr_color_mt("ConwayGame");
		//Set level for output
		s_CoreLogger->set_level(spdlog::level::trace);

	}
}