workspace "OGLBP"

    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
    }

    filter "system:windows"
        startproject "OGLBP"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "OGLBP/Vendor/GLFW/include"
IncludeDir["Glad"] = "OGLBP/Vendor/glad/include"
IncludeDir["glm"] = "OGLBP/Vendor/glm"
IncludeDir["stb_image"] = "OGLBP/Vendor/stb/include"

group "Dependencies"
    include "OGLBP/Vendor/GLFW"
    include "OGLBP/Vendor/glad"
group ""

project "OGLBP"
    location "OGLBP"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Vendor/stb/include/**.h",
		"%{prj.name}/Vendor/stb/include/**.cpp",
		"%{prj.name}/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.inl",
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

    filter "system:linux"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

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

--postbuildcommands
--{
--    ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/")
--}
