#pragma once

#include<memory>

#ifdef  GAME_PLATFORM_WINDOWS

#if 0 
#ifdef GAME_BUILD_DLL
	#define GAME_API __declspec(dllexport)
#else 
	#define GAME_API __declspec(dllimport)
#endif // GAME_BUILD_DL
#else 
	#define GAME_API
#endif

#else
#error Game only support Windows!;
#endif //  HZ_PLATFORM_WINDOWS

#ifdef QG_DEBUG
#define GAME_ENABLE_ASSERTS
#endif // QG_DEBUG



#ifdef GAME_ENABLE_ASSERTS
#define GAME_ASSERT(x,...){ if( !(x) ){ QG_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak(); } }
#define GAME_CORE_ASSERT(x, ... ){ if( !(x) ){ QG_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak(); } }

#else 
#define GAME_ASSERT(x,...)
#define GAME_CORE_ASSERT(x,...)


#endif // !GAME_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define QG_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)


namespace QGame {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}