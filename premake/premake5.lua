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
   links {"RenderSystem", "Math", "Common", "User", "chaiscript_stdlib-5.7.1", "loki", "opengl32", "Script", "Graphics" }
   includedirs { "../Engine/RenderSystem/ogl", "../Engine/Script/chai" }
   includedirs { "../Engine/RenderSystem/", "../Engine/Common/", "../Engine/User/"}
   includedirs { "../3rdParty/ChaiScript/include/" }
   includedirs { "../3rdParty/" }
   libdirs { os.findlib("opengl32") }

project "loki"
    kind "StaticLib"
    files { "../3rdParty/loki/**.h", "../3rdParty/loki/**.cpp" }
	includedirs { "../3rdParty/" }
	
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
	
project "effects"
    kind "None"
    files { "../data/effects/**.xml", "../data/effects/**.xml" }
    
project "Math"
    kind "StaticLib"
    files { "../Engine/Math/**.h", "../Engine/Math/**.cpp", "../Engine/Math/**.inl" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }

project "User"
    kind "StaticLib"
    files { "../Engine/User/**.h", "../Engine/User/**.cpp", "../Engine/User/**.inl" }
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