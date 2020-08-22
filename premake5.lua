workspace "OpenGL"

    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
    }

    filter "system:windows"
        startproject "OpenGL"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "OpenGL/vendor/glfw/include"
IncludeDir["Glad"] = "OpenGL/vendor/glad/include"
IncludeDir["glm"] = "OpenGL/vendor/glm"
IncludeDir["stb_image"] = "OpenGL/vendor/stb/include"

group "Dependencies"
    include "OpenGL/vendor/glfw"
    include "OpenGL/vendor/glad"
group ""

project "OpenGL"
    location "OpenGL"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb/include/**.h",
		"%{prj.name}/vendor/stb/include/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GE_BUILD_DLL",
            "GE_PLATFORM_WINDOWS"
        }

        links
        {
            "GLFW",
            "Glad",
            "opengl32.lib"
        }

        postbuildcommands
        {
            ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/")
        }

    filter "system:linux"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        postbuildcommands
        {
            ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/")
        }

        links
        {
            "GLFW",
            "Glad",
            "GL",
            "X11",
            "pthread",
            "Xrandr",
            "Xi",
            "dl"
        }

    filter "configurations:Debug"
        defines "GE_DEBUG"
        symbols "On"
      
    filter "configurations:Release"
        defines "GE_RELEASE"
        optimize "On"
      
    filter "configurations:Dist"
        defines "GE_DIST"
        optimize "On"

