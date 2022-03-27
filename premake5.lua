include "build/conan/conanbuildinfo.premake.lua"
workspace "gcode_tool"
	conan_basic_setup()
	configurations { "Debug", "Release" }

project "gcode_tool"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++17"
	location "build/program"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.cpp", "src/**.h" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"

	linkoptions { conan_exelinkflags }
