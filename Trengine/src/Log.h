#pragma once
#include <memory>
#include "Trengine/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Trengine {
	class TR_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};

}

#define TR_CORE_TRACE(...) ::Trengine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TR_CORE_INFO(...) ::Trengine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TR_CORE_WARN(...) ::Trengine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TR_CORE_ERROR(...) ::Trengine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TR_CORE_FATAL(...) ::Trengine::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#define TR_TRACE(...) ::Trengine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TR_INFO(...) ::Trengine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TR_WARN(...) ::Trengine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TR_ERROR(...) ::Trengine::Log::GetClientLogger()->error(__VA_ARGS__)
#define TR_FATAL(...) ::Trengine::Log::GetClientLogger()->fatal(__VA_ARGS__)
