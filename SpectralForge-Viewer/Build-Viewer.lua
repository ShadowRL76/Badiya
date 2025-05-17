project "SpectralForge-Viewer"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

	  -- Include Core
      "../SpectralForge-Core/Source",
	  "../SpectralForge-Core/Source/dependencies/include",
      "../SpectralForge-Core/Source/dependencies/include/imgui",
      "../SpectralForge-Core/Source/dependencies/include/imgui/imgui.h",
      "../SpectralForge-Core/Source/dependencies/include/GL",
      "../SpectralForge-Core/Source/dependencies/include/GLFW",
      "../SpectralForge-Core/Source/dependencies/include/glm",
      "../SpectralForge-Core/Source/dependencies/include/stb"
      "../SpectralForge-Core/Source/dependencies/include/entt"
   }

   links
   {
      "SpectralForge-Core",
      "glfw3.lib",
      "glew32.lib",
      "opengl32.lib"
   }
   
   libdirs
    {
        "../Binaries/" .. OutputDir .. "/SpectralForge-Core",
        "../SpectralForge-Core/Source/dependencies/lib"
    }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"