workspace "QGameEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


IncludeDir = {}
LibDir = {}
IncludeDir["GLAD"] = "Engine/vendor/GLAD/include"
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
LibDir["GLFW"] = "Engine/vendor/GLFW"
LibDir["GLAD"] = "Engine/vendor/GLAD"

project "Engine"
	
	location "Engine"
	
	kind "SharedLib"
	
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir   ("Build/" .. outputdir .. "/%{prj.name}")

	pchheader "qgpch.h"
	pchsource "Engine/src/qgpch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
	}
	libdirs{
		"%{LibDir.GLFW}",
		"%{LibDir.GLAD}",
	}

	links{
		
		"glfw3_mt.lib",
		"glad.lib",
		"opengl32.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

		defines{
			"GAME_PLATFORM_WINDOWS",
			"GAME_BUILD_DLL"
		}
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "QG_DEBUG"
		symbols "On"
    filter "configurations:Release"
		defines "QG_RELEASE"
		symbols "On"
	filter "configurations:Dist"
		defines "QG_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir   ("Build/" .. outputdir .. "/%{prj.name}")
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"Engine/vendor/spdlog/include",
		"Engine/src"
	}

	links{
		"Engine" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

		defines{
			"GAME_PLATFORM_WINDOWS"
		}


		
	filter "configurations:Debug"
		defines "QG_DEBUG"
		symbols "On"
    filter "configurations:Release"
		defines "QG_RELEASE"
		symbols "On"
	filter "configurations:Dist"
		defines "QG_DIST"
		symbols "On"

