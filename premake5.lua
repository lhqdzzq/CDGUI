workspace "CDGUI"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Relaese",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "CDGUI/vendor/GLFW/include"
IncludeDir["Glad"] = "CDGUI/vendor/Glad/include"
IncludeDir["glm"] = "CDGUI/vendor/glm"
IncludeDir["stb_image"] = "CDGUI/vendor/stb_image"

include"CDGUI/vendor/GLFW"
include"CDGUI/vendor/Glad"

project "CDGUI"
	location "CDGUI"
	kind "StaticLib"
	language "c++"
	cppdialect "c++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cgpch.h"
	pchsource "CDGUI/src/cgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CG_PLATFORM_WINDOWS",
			"CG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	--postbuildcommands
	--{
		--("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
	--}
		
	filter "configurations:Debug"
		defines "CG_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "CG_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "CG_DIST"
		buildoptions "/MD"
		optimize "on"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "c++"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"CDGUI/src",
		"CDGUI/vendor/spdlog/include",
		"%{IncludeDir.glm}"
	}

	links
	{
		"CDGUI"
	}

	filter "system:windows"
		cppdialect "c++17"
		systemversion "latest"

		defines
		{
			"CG_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "CG_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "CG_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "CG_DIST"
		buildoptions "/MD"
		optimize "on"