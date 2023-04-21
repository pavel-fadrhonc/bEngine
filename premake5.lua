workspace "bEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "bEngine/vendor/GLFW/include"

-- include GLFW premake file
include "bEngine/vendor/GLFW"

project "bEngine"
	location "bEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}") 
	objdir("bin-int/" .. outputdir .. "/%{prj.name}") 
	
	pchheader "bepch.h"
	pchsource "bEngine/src/bepch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs 
	{
		"%{prj.name}/vendor/spdlog/include",
		"bEngine/src",
		"%{IncludeDir.GLFW}"
	}
	
	links 
	{
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "BE_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}") 
	objdir("bin-int/" .. outputdir .. "/%{prj.name}") 
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs 
	{
		"bEngine/vendor/spdlog/include",
		"bEngine/src"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BE_PLATFORM_WINDOWS"
		}
		
	links
	{
		"bEngine"
	}
		
	filter "configurations:Debug"
		defines "BE_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		optimize "On"
		
	

