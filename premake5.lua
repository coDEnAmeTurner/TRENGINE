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
IncludeDir["GLAD"] = "vendor/GLAD/include"

include "vendor/GLFW"

include "vendor/GLAD"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}"
    }

    links {
        "GLFW",
        "GLAD",
        "opengl32.lib"
    }

    filter "system:windows" 
        cppdialect "C++17"
        staticruntime "On"  
        systemversion "latest"

        defines {
            "TR_PLATFORM_WINDOWS",
            "TR_BUILD_DLL",
			"TR_ENABLE_ASSERTS", 
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug" 
        defines "TR_DEBUG"
        symbols "On"
        buildoptions "/MDd"

    filter "configurations:Release" 
        defines "TR_RELEASE"
        symbols "On"
        buildoptions "/MD"

    filter "configurations:Dist" 
        defines "TR_DIST"
        symbols "On"
        buildoptions "/MD"

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
			"TR_ENABLE_ASSERTS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug" 
        defines "TR_DEBUG"
        symbols "On"
        buildoptions "/MDd"

    filter "configurations:Release" 
        defines "TR_RELEASE"
        symbols "On"
        buildoptions "/MD"

    filter "configurations:Dist" 
        defines "TR_DIST"
        symbols "On"
        buildoptions "/MD"
