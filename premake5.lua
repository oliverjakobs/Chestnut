workspace "Chestnut"

	configurations
	{
		"Debug",
		"Release"
	}

outputDir = "%{cfg.buildcfg}"   

IncludeDir = {}
IncludeDir["GLFW"] = "Chestnut/external/glfw/include" 
IncludeDir["GLAD"] = "Chestnut/external/glad/include"
IncludeDir["FMT"] = "Chestnut/external/fmt/include"

include "Chestnut/external/glfw"
include "Chestnut/external/glad"
include "Chestnut/external/fmt"

project "Chestnut"
	location "Chestnut"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "chstpch.h"
	pchsource "Chestnut/src/chstpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	links
	{
		"GLFW",
		"GLAD",
		"FMT",
		"opengl32"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external/include", 
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.FMT}"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CHST_EXPORTS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Frost")
		}

-- Sandbox
project "Frost"
	location "Frost"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Chestnut/src",
		"Chestnut/external/include", 
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.FMT}"
	}

	links
	{
		"FMT",
		"Chestnut"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"