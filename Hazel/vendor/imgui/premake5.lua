project "imgui"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "imconfig.h",
        "imgui.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_internal.h",
        "imstb_truetype.h",
        "imgui_demo.cpp",
        "imgui_draw.cpp",
        "imgui_widgets.cpp",
        "imgui.cpp",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
		}

		defines 
		{
            --"IMGUI_API=__declspec(dllexport)"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
