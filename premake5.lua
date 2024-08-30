workspace "Trengine"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"  
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include relative to the root folder (sln dir)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"

include "vendor/GLFW"

project "Trengine"
    location "Trengine"
    kind "SharedLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "trpch.h"
	pchsource "Trengine/src/trpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
		"%{prj.name}/src",
        "%{prj.name}/src/../../vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows" 
        cppdialect "C++17"
        staticruntime "On"  
        systemversion "latest"

        defines {
            "TR_PLATFORM_WINDOWS",
            "TR_BUILD_DLL",
			"TR_ENABLE_ASSERTS"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug" 
        defines "TR_DEBUG"
        symbols "On"

    filter "configurations:Release" 
        defines "TR_RELEASE"
        symbols "On"

    filter "configurations:Dist" 
        defines "TR_DIST"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src/../../vendor/spdlog/include",
        "%{prj.name}/src/../../vendor/GLFW/include",
        "Trengine/src"
    }

    links {
        "Trengine"
    }

    filter "system:windows" 
        cppdialect "C++17"
        staticruntime "On"  
        systemversion "latest"

        defines {
            "TR_PLATFORM_WINDOWS",
			"TR_ENABLE_ASSERTS"
        }

    filter "configurations:Debug" 
        defines "TR_DEBUG"
        symbols "On"

    filter "configurations:Release" 
        defines "TR_RELEASE"
        symbols "On"

    filter "configurations:Dist" 
        defines "TR_DIST"
        symbols "On"