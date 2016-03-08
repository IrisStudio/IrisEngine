-- premake5.lua
workspace "IrisEditor"
   configurations { "Debug", "Release", "Final" }
   platforms { "x32", "x64" }
   location "../vs2015"
   language "C++"
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

   filter "configurations:Release"
      defines { "NO_DEBUG", "NO_LOG" }
      optimize "On"

project "IrisEditor"
   kind "ConsoleApp"
   targetdir "../bin/%{cfg.buildcfg}"
   files { "../IrisEditor/**.h", "../IrisEditor/**.cpp" }
   links {"RenderSystem", "Math", "Common", "User", "entityx", "ChaiScript", "opengl32", "Script", "Graphics", "flatbuffers", "Hierarchy" }
   includedirs { "../Engine/RenderSystem/ogl", "../Engine/Script/chai" }
   includedirs { "../Engine/RenderSystem/", "../Engine/Common/", "../Engine/User/", "../Engine/Hierarchy"}
   includedirs { "../3rdParty/ChaiScript/include/" }
   includedirs { "../3rdParty/entityx/" }
   includedirs { "../3rdParty/" }
   libdirs { os.findlib("opengl32") }

group "FileSystem"
project "effects"
    kind "None"
    files { "../data/effects/**.xml", "../data/effects/**.xml" }
   
group "Engine"
project "Math"
    kind "StaticLib"
    files { "../Engine/Math/**.h", "../Engine/Math/**.cpp", "../Engine/Math/**.inl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }

project "User"
    kind "StaticLib"
    files { "../Engine/User/**.h", "../Engine/User/**.cpp", "../Engine/User/**.inl" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../Engine/RenderSystem" }
	includedirs { "../Engine/Common/" }
    includedirs { "../Engine/Hierarchy/" }
	includedirs { "../3rdParty/" }
    includedirs { "../3rdParty/entityx/" }
	
project "Script"
    kind "StaticLib"
    files { "../Engine/Script/**.h", "../Engine/Script/**.cpp", "../Engine/Script/**.inl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/Script/" }
	includedirs { "../Engine/RenderSystem/ogl" }
	includedirs { "../Engine/RenderSystem" }
	includedirs { "../3rdParty/" }
	includedirs { "../3rdParty/ChaiScript/include/" }
	
project "Common"
    kind "StaticLib"
    files { "../Engine/Common/**.h", "../Engine/Common/**.cpp", "../Engine/Math/**.inl", "../Engine/Common/**.hpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/" }

project "RenderSystem"
    kind "StaticLib"
    files { "../Engine/RenderSystem/**.h", "../Engine/RenderSystem/**.cpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/RenderSystem/", "../Engine/RenderSystem/ogl/" }
	includedirs { "../3rdParty/" }

project "Graphics"
    kind "StaticLib"
    files { "../Engine/Graphics/**.h", "../Engine/Graphics/**.cpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/RenderSystem/ogl" }
    includedirs { "../Engine/Graphics/" }
	includedirs { "../3rdParty/" }
    
project "Hierarchy"
    kind "StaticLib"
    files { "../Engine/Hierarchy/**.h", "../Engine/Hierarchy/**.cpp" }
	includedirs { "../Engine/Common/" }
    includedirs { "../Engine/RenderSystem/", "../Engine/RenderSystem/ogl/" }
	includedirs { "../3rdParty/entityx/" }
    includedirs { "../3rdParty/" }
    
group "3rdParty"
project "ChaiScript"
    kind "SharedLib"
    files { "../3rdParty/ChaiScript/src/**.cpp", "../3rdParty/ChaiScript/include/chaiscript/**.hpp" }
	includedirs { "../3rdParty/ChaiScript/include/" }
    
project "entityx"
    kind "StaticLib"
    files { "../3rdParty/entityx/entityx/**.cpp", "../3rdParty/entityx/entityx/**.cc", "../3rdParty/entityx/entityx/**.hpp", "../3rdParty/entityx/entityx/**.h" }
    excludes { "../3rdParty/entityx/entityx/**test.cc" }
	includedirs { "../3rdParty/entityx/" }

project "flatbuffers"
    kind "StaticLib"
    files { "../3rdParty/flatbuffers/**.h", "../3rdParty/flatbuffers/src/**.cpp" }
	includedirs { "../3rdParty/" }