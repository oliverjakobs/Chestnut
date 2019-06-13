workspace "Chestnut"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Chestnut/vendor/GLFW/include"
IncludeDir["Glad"] = "Chestnut/vendor/Glad/include"
IncludeDir["ImGui"] = "Chestnut/vendor/imgui"
IncludeDir["glm"] = "Chestnut/vendor/glm"

group "Dependencies"
	include "Chestnut/vendor/GLFW"
	include "Chestnut/vendor/Glad"
	include "Chestnut/vendor/imgui"

group ""

project "Chestnut"
	location "Chestnut"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Chestnut/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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
			"CHST_PLATFORM_WINDOWS",
			"CHST_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CHST_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CHST_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CHST_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Chestnut/vendor/spdlog/include",
		"Chestnut/src",
		"Chestnut/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Chestnut"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CHST_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CHST_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CHST_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CHST_DIST"
		runtime "Release"
		optimize "on"
