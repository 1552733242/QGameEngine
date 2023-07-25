workspace "QGameEngine"
	architecture "x64"
	
	startproject "SandBox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



IncludeDir = {}
LibDir = {}
IncludeDir["spdlog"] = "%{prj.name}/vendor/spdlog/include"
IncludeDir["GLAD"] = "%{prj.name}/vendor/GLAD/include"
IncludeDir["GLFW"] = "%{prj.name}/vendor/GLFW/include"
IncludeDir["imgui"] = "%{prj.name}/vendor_src/imgui"
IncludeDir["glm"] = "%{prj.name}/vendor_src/glm"
LibDir["GLFW"] = "%{prj.name}/vendor/GLFW"
LibDir["GLAD"] = "%{prj.name}/vendor/GLAD"




project "Engine"
	
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir   ("Build/" .. outputdir .. "/%{prj.name}")

	pchheader "qgpch.h"
	pchsource "Engine/src/qgpch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor_src/imgui/imgui*.cpp",
		"%{prj.name}/vendor_src/imgui/imgui*.h",
	}

	includedirs{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}",
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
		systemversion "10.0"
		defines{
			"GAME_PLATFORM_WINDOWS",
			"GAME_BUILD_DLL"
		}
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox\"") 
		}

		filter "configurations:Debug"
		defines "QG_DEBUG"
		runtime	"Debug"
		symbols "on"


    filter "configurations:Release"
		defines "QG_RELEASE"
		runtime	"Release"
		symbols "on"
	filter "configurations:Dist"
		defines "QG_DIST"
		runtime	"Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir   ("Build/" .. outputdir .. "/%{prj.name}")
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"Engine/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"Engine/src",
	}

	links{
		"Engine" 
	}

	filter "system:windows"
		systemversion "10.0"

		defines{
			"GAME_PLATFORM_WINDOWS"
		}


		
	filter "configurations:Debug"
		defines "QG_DEBUG"
		runtime	"Debug" 
		symbols "on"
    filter "configurations:Release"
		defines "QG_RELEASE"
		runtime	"Release"
		symbols "on"
	filter "configurations:Dist"
		defines "QG_DIST"
		runtime	"Release"
		symbols "on"

