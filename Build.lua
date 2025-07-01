-- premake5.lua
workspace "SpectralForge"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SpectralForge-Viewer"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/utf-8" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "SpectralForge-Core/Build-Core.lua"
group ""

include "SpectralForge-Viewer/Build-Viewer.lua"