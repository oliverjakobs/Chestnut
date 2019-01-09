workspace "Chestnut"

	configurations
	{
		"Debug",
		"Release"
	}

outputDir = "%{cfg.buildcfg}"   

IncludeDir = {}
IncludeDir["GLFW"] = "Chestnut/external/glfw/include" 
IncludeDir["GLEW"] = "Chestnut/external/glew/include"
IncludeDir["ToolBox"] = "Chestnut/external/toolbox/include"

include "Chestnut/external/glfw"
include "Chestnut/external/glew"

project "Chestnut"
	location "Chestnut"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	links
	{
		"GLFW",
		"GLEW",
		"opengl32"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external/include", 
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.ToolBox}"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CHESTNUT_EXPORTS"
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
		"%{IncludeDir.ToolBox}"
	}

	links
	{
		"Golem"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"