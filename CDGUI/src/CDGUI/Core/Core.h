#pragma once
#include<memory>
#include"Log.h"

#ifdef CG_PLATFORM_WINDOWS
#if CG_DYNAMIC_LINK
	#ifdef CG_BUILD_DLL
		#define CDGUI_API __declspec(dllexport)
	#else
		#define CDGUI_API __declspec(dllimport)
	#endif
#else
	#define CDGUI_API
#endif
#else
	#error only windows
#endif

#ifdef CG_ENABLE_ASSERTS
	#define CG_ASSERTS(x,...) { if(!(x)) { CG_ERROR("¶ÏÑÔ {0} ³ö´í£¡",__VA_ARGS__); __debugbreak(); } }
	#define CG_CORE_ASSERTS(x,...) { if(!(x)) { CG_CORE_ERROR("¶ÏÑÔ {0} ³ö´í£¡",__VA_ARGS__); __debugbreak(); } }
#else
	#define CG_ASSERTS(x, ...)
	#define CG_CORE_ASSERTS(x, ...)
#endif

#define BIT(x) (1<<x)

#define CG_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace cdgui
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}