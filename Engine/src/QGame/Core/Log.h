#pragma once
#include "QGame/Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
namespace QGame {

	class GAME_API Log {
	public:
		static void Init();
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;


	};
}


#define QG_CORE_TRACE(...)  ::QGame::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QG_CORE_INFO(...)   ::QGame::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QG_CORE_WARN(...)   ::QGame::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QG_CORE_ERROR(...)  ::QGame::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QG_CORE_FATAL(...)  ::QGame::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#define QG_TRACE(...)  ::QGame::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QG_INFO(...)   ::QGame::Log::GetClientLogger()->info(__VA_ARGS__)
#define QG_WARN(...)   ::QGame::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QG_ERROR(...)  ::QGame::Log::GetClientLogger()->error(__VA_ARGS__)
#define QG_FATAL(...)  ::QGame::Log::GetClientLogger()->fatal(__VA_ARGS__)