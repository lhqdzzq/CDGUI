#pragma once

#pragma warning( disable: 4251 )
#pragma warning(push, 0)
#include"spdlog/spdlog.h"
#include"spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace cdgui {

	class Log
	{
	public:
		static void Init();


		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//核心日志宏
#define CG_CORE_TRACE(...)		::cdgui::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define CG_CORE_INFO(...)		::cdgui::Log::GetCoreLogger()->info(__VA_ARGS__);
#define CG_CORE_WARN(...)		::cdgui::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define CG_CORE_ERROR(...)		::cdgui::Log::GetCoreLogger()->error(__VA_ARGS__);
#define CG_CORE_CRITICAL(...)	::cdgui::Log::GetCoreLogger()->critical(__VA_ARGS__);

//客户应用宏
#define CG_TRACE(...)		::cdgui::Log::GetClientLogger()->trace(__VA_ARGS__);
#define CG_INFO(...)		::cdgui::Log::GetClientLogger()->info(__VA_ARGS__);
#define CG_WARN(...)		::cdgui::Log::GetClientLogger()->warn(__VA_ARGS__);
#define CG_ERROR(...)		::cdgui::Log::GetClientLogger()->error(__VA_ARGS__);
#define CG_CRITICAL(...)	::cdgui::Log::GetClientLogger()->critical(__VA_ARGS__);