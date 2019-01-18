project "FMT"
    kind "StaticLib"
    language "C"
    
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
        "include/fmt/*.h",
        "src/format.cc",
        "src/posix.cc"
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
