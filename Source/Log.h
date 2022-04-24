#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/logger.h"

namespace Conway {
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };

		void setLevel(spdlog::level::level_enum level);

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}


//Log Macros
#define CW_CORE_ERROR(...)  ::Conway::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CW_CORE_WARN(...)   ::Conway::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CW_CORE_INFO(...)   ::Conway::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CW_CORE_TRACE(...)  ::Conway::Log::GetCoreLogger()->trace(__VA_ARGS__)
