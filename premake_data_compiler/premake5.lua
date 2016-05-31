-- premake5.lua

workspace "DataCompiler"
   configurations { "Debug", "Release", "Final" }
   platforms { "x64" }
   location "../DataCompilerDevEnv"
   language "C++"
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

   filter "configurations:Release"
      defines { "NO_DEBUG" }
      optimize "On"
	  
	filter "configurations:Final"
      defines { "NO_DEBUG", "NO_LOG" }
      optimize "On"

project "DataCompiler"
   kind "ConsoleApp"
   targetdir "../bin/%{cfg.buildcfg}"
   flags { "ExtraWarnings", "NoRTTI" }
   files { "../DataCompiler/**.h", "../DataCompiler/**.cpp" }
   links { "Common", "Graphics", "flatbuffers", "winmm" }
   includedirs { "../Engine/Common/", "../Engine/Graphics", "RenderSystem" }
   includedirs { "../3rdParty/" }
   
group "FileSystem"
project "effects"
    kind "None"
    files { "../data/effects/**.xml", "../data/effects/**.xml" }
   
group "Engine"
project "Common"
    kind "StaticLib"
    files { "../Engine/Common/**.h", "../Engine/Common/**.cpp", "../Engine/Common/**.hpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }

project "RenderSystem"
    kind "StaticLib"
    files { "../Engine/RenderSystem/**.h", "../Engine/RenderSystem/**.cpp" }
	includedirs { "../Engine/Common/" }
    includedirs { "../Engine/Graphics/" }
	includedirs { "../Engine/RenderSystem/", "../Engine/RenderSystem/ogl/" }
	includedirs { "../3rdParty/" }

project "Graphics"
    kind "StaticLib"
    files { "../Engine/Graphics/**.h", "../Engine/Graphics/**.cpp", "../Engine/Graphics/**.cc" }
	includedirs { "../Engine/Common/" }
    includedirs { "../Engine/RenderSystem/" }
    includedirs { "../Engine/Graphics/" }
	includedirs { "../3rdParty/" }
    
group "3rdParty"

project "flatbuffers"
    kind "StaticLib"
    files { "../3rdParty/flatbuffers/**.h", "../3rdParty/flatbuffers/src/**.cpp" }
	includedirs { "../3rdParty/" }
