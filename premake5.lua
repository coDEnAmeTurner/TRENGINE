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
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["entt"] = "vendor/entt/include"

group "Dependencies"

    include "vendor/GLFW"

    include "vendor/GLAD"

    include "vendor/imgui"

group ""


project "Trengine"
    location "Trengine"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "trpch.h"
	pchsource "Trengine/src/trpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/../vendor/stb_image/**.h",
        "%{prj.name}/../vendor/stb_image/**.cpp",
    }

    includedirs {
		"%{prj.name}/src",
        "%{prj.name}/src/../../vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}"
    }

    links {
        "GLFW",
        "GLAD",
        "opengl32.lib",
        "ImGui"
    }

    filter "system:windows" 
        systemversion "latest"

        defines {
            "TR_PLATFORM_WINDOWS",
            "TR_BUILD_DLL",
			"TR_ENABLE_ASSERTS", 
            "GLFW_INCLUDE_NONE",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug" 
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release" 
        defines "TR_RELEASE"
        runtime "Release"
        symbols "On"
        optimize "on"

    filter "configurations:Dist" 
        defines "TR_DIST"
        runtime "Release"
        symbols "on"

project "Trengine Editor"
    location "Trengine Editor"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs {
        "%{prj.name}/src/../../vendor/spdlog/include",
        "%{prj.name}/src/../../vendor/GLFW/include",
        "%{IncludeDir.glm}",
        "Trengine/src",
        "%{IncludeDir.entt}"
    }

    links {
        "ImGui",
        "Trengine"
    }

    filter "system:windows" 
        systemversion "latest"

        defines {
            "TR_PLATFORM_WINDOWS",
			"TR_ENABLE_ASSERTS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug" 
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release" 
        defines "TR_RELEASE"
        runtime "Release"
        symbols "On"

    filter "configurations:Dist" 
        defines "TR_DIST"
        runtime "Release"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs {
        "%{prj.name}/src/../../vendor/spdlog/include",
        "%{prj.name}/src/../../vendor/GLFW/include",
        "%{IncludeDir.glm}",
        "Trengine/src",
        "%{IncludeDir.entt}"
    }

    links {
        "Trengine"
    }

    filter "system:windows" 
        systemversion "latest"

        defines {
            "TR_PLATFORM_WINDOWS",
			"TR_ENABLE_ASSERTS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug" 
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release" 
        defines "TR_RELEASE"
        runtime "Release"
        symbols "On"

    filter "configurations:Dist" 
        defines "TR_DIST"
        runtime "Release"
        symbols "On"
