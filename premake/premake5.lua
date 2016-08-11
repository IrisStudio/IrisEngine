-- premake5.lua

workspace "IrisEditor"
   configurations { "Debug_Render_Calls", "Debug", "Release", "Final" }
   platforms { "x64" }
   location "../EditorDevEnv"
   language "C++"
   
   filter "configurations:Debug_Render_Calls"
      defines { "DEBUG", "DEBUG_RENDER_CALLS" }
      flags { "Symbols" }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

   filter "configurations:Release"
      defines { "NO_DEBUG" }
      optimize "On"
	  
	filter "configurations:Final"
      defines { "NO_DEBUG", "NO_LOG" }
      optimize "On"

project "IrisEditor"
   kind "WindowedApp"
   targetdir "../bin/%{cfg.buildcfg}"
   flags { "ExtraWarnings", "NoRTTI" }
   files { "../IrisEditor/**.h", "../IrisEditor/**.cpp" }
   links {"RenderSystem", "Common", "User", "entityx", "opengl32", "Logic", "Graphics", "flatbuffers", "Hierarchy", "winmm", "gainput", "imgui" }
   includedirs { "../Engine/RenderSystem/", "../Engine/Common/", "../Engine/User/", "../Engine/Hierarchy", "../Engine/Graphics"}
   includedirs { "../3rdParty/" }
   libdirs { os.findlib("opengl32") }
   
group "FileSystem"
project "effects"
    kind "None"
    files { "../data/effects/**.xml", "../data/effects/**.xml" }
   
group "Engine"
project "User"
    kind "StaticLib"
    files { "../Engine/User/**.h", "../Engine/User/**.cpp", "../Engine/User/**.inl" }
	includedirs { "../Engine/RenderSystem" }
	includedirs { "../Engine/Common/" }
    includedirs { "../Engine/Hierarchy/" }
    includedirs { "../Engine/Graphics/" }
	includedirs { "../3rdParty/" }
    includedirs { "../3rdParty/entityx/" }
	includedirs { "../3rdParty/gainput-master/lib/include/" }
	includedirs { "../3rdParty/imgui" }
	
project "Logic"
    kind "StaticLib"
    files { "../Engine/Logic/**.h", "../Engine/Logic/**.cpp", "../Engine/Logic/**.inl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/Logic/" }
	
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
	includedirs { "../3rdParty/gainput-master/lib/include/" }
	includedirs { "../3rdParty/imgui" }

project "Graphics"
    kind "StaticLib"
    files { "../Engine/Graphics/**.h", "../Engine/Graphics/**.cpp", "../Engine/Graphics/**.cc" }
	includedirs { "../Engine/Common/" }
    includedirs { "../Engine/RenderSystem/" }
    includedirs { "../Engine/Graphics/" }
	includedirs { "../3rdParty/" }
    
project "Hierarchy"
    kind "StaticLib"
    files { "../Engine/Hierarchy/**.h", "../Engine/Hierarchy/**.cpp" }
	includedirs { "../Engine/Common/" }
    includedirs { "../Engine/User/" }
    includedirs { "../Engine/Graphics/" }
    includedirs { "../Engine/RenderSystem/", "../Engine/RenderSystem/ogl/" }
	includedirs { "../3rdParty/entityx/" }
    includedirs { "../3rdParty/" }
    
group "3rdParty"
project "gainput"
    kind "StaticLib"
    files { "../3rdParty/gainput-master/lib/source/gainput/**.cpp", "../3rdParty/gainput-master/lib/source/gainput/**.h", "../3rdParty/gainput-master/lib/include/gainput/**.h" }
	includedirs { "../3rdParty/gainput-master/lib/include" }
	
project "entityx"
    kind "StaticLib"
    files { "../3rdParty/entityx/entityx/**.cpp", "../3rdParty/entityx/entityx/**.cc", "../3rdParty/entityx/entityx/**.hpp", "../3rdParty/entityx/entityx/**.h" }
    excludes { "../3rdParty/entityx/entityx/**test.cc" }
	includedirs { "../3rdParty/entityx/" }

project "flatbuffers"
    kind "StaticLib"
    files { "../3rdParty/flatbuffers/**.h", "../3rdParty/flatbuffers/src/**.cpp" }
	includedirs { "../3rdParty/" }
	
project "imgui"
    kind "StaticLib"
    files { "../3rdParty/imgui/**.h", "../3rdParty/imgui/**.cpp" }
	includedirs { "../3rdParty/imgui" }
	excludes { "../3rdParty/imgui/examples/**"  }
