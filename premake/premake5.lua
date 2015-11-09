-- premake5.lua
workspace "IrisEditor"
   configurations { "Debug", "Release", "Final" }
   location "../vs2015"
   language "C++"
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

project "IrisEditor"
   kind "ConsoleApp"
   targetdir "../bin/%{cfg.buildcfg}"
   files { "../IrisEditor/**.h", "../IrisEditor/**.cpp" }
   links {"RenderSystem", "Math"}
   includedirs { "../Engine/Math/" }

project "RenderSystem"
    kind "StaticLib"
    files { "../Engine/RenderSystem/**.h", "../Engine/RenderSystem/**.cpp" }
    
project "Math"
    kind "StaticLib"
    files { "../Engine/Math/**.h", "../Engine/Math/**.cpp", "../Engine/Math/**.inl" }