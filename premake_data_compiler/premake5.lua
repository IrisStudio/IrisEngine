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
   links { "Common", "flatbuffers",  "assimp" }
   includedirs { "../Engine/Common/",}
   includedirs { "../3rdParty/" }
   includedirs { "../DataCompiler/" }
   includedirs { "../Engine/Graphics/" }
   includedirs { "../Engine/Graphics/io/fbs/" }
   includedirs { "../3rdParty/assimp/include/" }
   libdirs { "../3rdParty/assimp/lib64/" }
   
project "Common"
    kind "StaticLib"
    files { "../Engine/Common/**.h", "../Engine/Common/**.cpp", "../Engine/Common/**.hpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }

group "3rdParty"

project "flatbuffers"
    kind "StaticLib"
    files { "../3rdParty/flatbuffers/**.h", "../3rdParty/flatbuffers/src/**.cpp" }
	includedirs { "../3rdParty/" }
