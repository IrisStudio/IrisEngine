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
   kind "WindowedApp"
   targetdir "../bin/%{cfg.buildcfg}"
   files { "../IrisEditor/**.h", "../IrisEditor/**.cpp" }
   links {"RenderSystem", "Math", "Common", "loki", "opengl32" }
   includedirs { "../Engine/RenderSystem/ogl" }
   includedirs { "../Engine/RenderSystem/", "../Engine/Common/" }
   includedirs { "../3rdParty/" }
   libdirs { os.findlib("opengl32"), "../3rdParty/loki/bin" }

project "RenderSystem"
    kind "StaticLib"
    files { "../Engine/RenderSystem/**.h", "../Engine/RenderSystem/**.cpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/RenderSystem/" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../3rdParty/" }
    
project "Math"
    kind "StaticLib"
    files { "../Engine/Math/**.h", "../Engine/Math/**.cpp", "../Engine/Math/**.inl" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }
	
project "Common"
    kind "StaticLib"
    files { "../Engine/Common/**.h", "../Engine/Common/**.cpp", "../Engine/Math/**.inl", "../Engine/Common/**.hpp" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }