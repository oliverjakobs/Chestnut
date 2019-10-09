workspace "Chestnut"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputDir = "%{cfg.buildcfg}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Chestnut/packages/glfw/include"
IncludeDir["Glad"] = "Chestnut/packages/glad/include"
IncludeDir["ImGui"] = "Chestnut/packages/imgui"
IncludeDir["glm"] = "Chestnut/packages/glm"

group "Dependencies"
	include "Chestnut/packages/glfw"
	include "Chestnut/packages/glad"
	include "Chestnut/packages/imgui"

group ""

project "Chestnut"
	location "Chestnut"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "chstpch.h"
	pchsource "Chestnut/src/chstpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/packages/glm/glm/**.hpp",
		"%{prj.name}/packages/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/packages/stb",
		"%{prj.name}/packages/spdlog/include",
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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Chestnut/packages/spdlog/include",
		"Chestnut/src",
		"Chestnut/packages",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}"
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
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"
