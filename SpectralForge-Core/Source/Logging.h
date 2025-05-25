#pragma once

#include "spdlog/spdlog.h"
#include <memory>

namespace Badiya {
	class Logging
	{
	private:
		static std::shared_ptr<spdlog::logger> s_ViewerLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetViewerLogger() { return s_ViewerLogger; }
	};
}

#ifdef DIST
//In Dist build
#define BDY_CORE_TRACE(...)
#define BDY_CORE_INFO(...)
#define BDY_CORE_WARN(...)
#define BDY_CORE_ERROR(...)
#define BDY_CORE_FATAL(...)

#define BDY_TRACE(...)
#define BDY_INFO(...)
#define BDY_WARN(...)
#define BDY_ERROR(...)
#else
//CORE Log Macros
#define BDY_CORE_TRACE(...) Badiya::Logging::GetCoreLogger()->trace(__VA_ARGS__)
#define BDY_CORE_INFO(...)  Badiya::Logging::GetCoreLogger()->info(__VA_ARGS__)
#define BDY_CORE_WARN(...)  Badiya::Logging::GetCoreLogger()->warn(__VA_ARGS__)
#define BDY_CORE_ERROR(...) Badiya::Logging::GetCoreLogger()->error(__VA_ARGS__)
#define BDY_CORE_FATAL(...) Badiya::Logging::GetCoreLogger()->fatal(__VA_ARGS__)
//Client Log Macros
#define BDY_TRACE(...) Badiya::Logging::GetViewerLogger()->trace(__VA_ARGS__)
#define BDY_INFO(...)  Badiya::Logging::GetViewerLogger()->info(__VA_ARGS__)
#define BDY_WARN(...)  Badiya::Logging::GetViewerLogger()->warn(__VA_ARGS__)
#define BDY_ERROR(...) Badiya::Logging::GetViewerLogger()->error(__VA_ARGS__)
#define BDY_FATAL(...) Badiya::Logging::GetViewerLogger()->fatal(__VA_ARGS__)
#endif
