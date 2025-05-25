#include "pch.h"
#include "Logging.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Badiya {
	std::shared_ptr<spdlog::logger> Logging::s_ViewerLogger;
	std::shared_ptr<spdlog::logger> Logging::s_CoreLogger;


	void Logging::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Badiya");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ViewerLogger = spdlog::stdout_color_mt("APP");
		s_ViewerLogger->set_level(spdlog::level::trace);

	}
}