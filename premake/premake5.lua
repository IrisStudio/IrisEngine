-- premake5.lua
workspace "IrisEditor"
   configurations { "Debug", "Release", "Final" }
   location "../vs2015"
   language "C++"
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

   filter "configurations:Release"
      defines { "NO_DEBUG", "NO_LOG" }
      optimize "On"

project "IrisEditor"
   kind "WindowedApp"
   targetdir "../bin/%{cfg.buildcfg}"
   files { "../IrisEditor/**.h", "../IrisEditor/**.cpp" }
   links {"RenderSystem", "Math", "Common", "chaiscript_stdlib-5.7.1", "loki", "opengl32", "Script" }
   includedirs { "../Engine/RenderSystem/ogl", "../Engine/Script/chai" }
   includedirs { "../Engine/RenderSystem/", "../Engine/Common/" }
   includedirs { "../3rdParty/ChaiScript/include/" }
   includedirs { "../3rdParty/" }
   libdirs { os.findlib("opengl32"), "../3rdParty/loki/bin" }

project "RenderSystem"
    kind "StaticLib"
    files { "../Engine/RenderSystem/**.h", "../Engine/RenderSystem/**.cpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../3rdParty/" }

project "Graphics"
    kind "StaticLib"
    files { "../Engine/Graphics/**.h", "../Engine/Graphics/**.cpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/RenderSystem/ogl" }
    includedirs { "../Engine/Graphics/" }
	includedirs { "../3rdParty/" }
    
project "Math"
    kind "StaticLib"
    files { "../Engine/Math/**.h", "../Engine/Math/**.cpp", "../Engine/Math/**.inl" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }

project "chaiscript_stdlib-5.7.1"
    kind "SharedLib"
    files { "../3rdParty/ChaiScript/src/**.cpp", "../3rdParty/ChaiScript/include/chaiscript/**.hpp" }
	includedirs { "../3rdParty/ChaiScript/include/" }
	
project "Script"
    kind "StaticLib"
    files { "../Engine/Script/**.h", "../Engine/Script/**.cpp", "../Engine/Script/**.inl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/Script/" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../3rdParty/" }
	includedirs { "../3rdParty/ChaiScript/include/" }
	
project "Common"
    kind "StaticLib"
    files { "../Engine/Common/**.h", "../Engine/Common/**.cpp", "../Engine/Math/**.inl", "../Engine/Common/**.hpp" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }