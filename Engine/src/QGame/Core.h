#pragma once
#ifdef  GAME_PLATFORM_WINDOWS
#ifdef GAME_BUILD_DLL
#define GAME_API __declspec(dllexport)
#else 
#define GAME_API __declspec(dllimport)
#endif // GAME_BUILD_DLL
#else
#error Game only support Windows!;
#endif //  HZ_PLATFORM_WINDOWS


#ifdef GAME_ENABLE_ASSERTS
#define GAME_ASSERT(x,...){ if( !(x) ){ GAME_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak(); } }
#define GAME_CORE_ASSERT(x, ... ){ if( !(x) ){ GAME_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak(); } }

#else 
#define GAME_ASSERT(x,...)
#define GAME_CORE_ASSERT(x,...)


#endif // !GAME_ENABLE_ASSERTS

#define BIT(x) (1 << x)