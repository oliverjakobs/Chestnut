project "GLEW"
    kind "StaticLib"
    language "C"
    
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"include/**.h",
		"src/**.cpp"
    }

    includedirs
    {
        "include"
    }
    
	filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
