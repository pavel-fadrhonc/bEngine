workspace "bEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	startproject "Sandbox"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "bEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "bEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "bEngine/vendor/imgui"
IncludeDir["glm"] = "bEngine/vendor/glm"
IncludeDir["stb"] = "bEngine/vendor/stb"

-- include dependency premake file
group "Dependencies"
	include "bEngine/vendor/GLFW"
	include "bEngine/vendor/Glad"
	include "bEngine/vendor/imgui"
group ""

project "bEngine"
	location "bEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}") 
	objdir("bin-int/" .. outputdir .. "/%{prj.name}") 
	
	pchheader "bepch.h"
	pchsource "bEngine/src/bepch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp"
	}
	
	includedirs 
	{
		"%{IncludeDir.glm}",
		"%{prj.name}/vendor/spdlog/include",
		"bEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb}"
	}
	
	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "BE_DEBUG"
		symbols "On"
		runtime "Debug"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		optimize "on"
		runtime "Release"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		optimize "on"
		runtime "Release"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	
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
		"bEngine/src",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}"
	}
	
	filter "system:windows"
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
		symbols "on"
		runtime "Debug"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		optimize "on"
		runtime "Release"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		optimize "on"
		runtime "Release"
