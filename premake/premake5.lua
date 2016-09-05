-- premake5.lua

workspace "IrisEditor"
   configurations { "Debug_Render_Calls", "Debug", "Release", "Final" }
   platforms { "x32", "x64" }
   location "../EditorDevEnv"
   language "C++"
   
   filter "configurations:Debug_Render_Calls"
      defines { "DEBUG", "DEBUG_RENDER_CALLS" , "LUA_REAL_FLOAT"}
      flags { "Symbols" }
   
   filter "configurations:Debug"
      defines { "DEBUG" , "LUA_REAL_FLOAT" }
      flags { "Symbols" }

   filter "configurations:Release"
      defines { "NO_DEBUG" , "LUA_REAL_FLOAT" }
      optimize "On"
	  
	filter "configurations:Final"
      defines { "NO_DEBUG", "NO_LOG", "LUA_REAL_FLOAT" }
      optimize "On"

	 targetdir "../bin/%{cfg.buildcfg}"
	  
project "IrisEditor"
   kind "ConsoleApp"
   flags { "ExtraWarnings", "NoRTTI" }
   files { "../IrisEditor/**.h", "../IrisEditor/**.cpp" }
   links {"RenderSystem", "Common", "User", "entityx", "opengl32", "Scripting", "Graphics", "flatbuffers", "Hierarchy", "winmm", "gainput", "imgui", "lua"}
   includedirs { "../Engine/RenderSystem/", "../Engine/Scripting/", "../Engine/Common/", "../Engine/User/", "../Engine/Hierarchy", "../Engine/Graphics"}
   includedirs { "../3rdParty/" }
   libdirs { os.findlib("opengl32")  }
   
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
	includedirs { "../Engine/Scripting/" }
	includedirs { "../3rdParty/lua/" }
	
project "Scripting"
    kind "StaticLib"
    files { "../Engine/Scripting/**.h", "../Engine/Scripting/**.cpp", "../Engine/Scripting/**.inl" }
	includedirs { "../Engine/Common/" }
	includedirs { "../Engine/Scripting/" }
	includedirs { "../3rdParty/lua/" }
	
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
	includedirs { "../Engine/Scripting/" }
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

project "lua"
    kind "StaticLib"
    files { "../3rdParty/lua/**.cpp", "../3rdParty/lua/**.c", "../3rdParty/lua/**.hpp", "../3rdParty/lua/**.h" }
	includedirs { "../3rdParty/lua/" }


project "flatbuffers"
    kind "StaticLib"
    files { "../3rdParty/flatbuffers/**.h", "../3rdParty/flatbuffers/src/**.cpp" }
	includedirs { "../3rdParty/" }
	
project "imgui"
    kind "StaticLib"
    files { "../3rdParty/imgui/**.h", "../3rdParty/imgui/**.cpp" }
	includedirs { "../3rdParty/imgui" }
	excludes { "../3rdParty/imgui/examples/**"  }