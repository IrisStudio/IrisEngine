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
   links {"RenderSystem", "Math", "glfw3", "opengl32", "glew32s" }
   includedirs { "../Engine/RenderSystem/", "../Engine/Common/" }
   libdirs { os.findlib("opengl32"), "../3rdParty/glfw_WIN32/lib-vc2015/", "../3rdParty/glew_WIN32/lib/Release/Win32" }

project "RenderSystem"
    kind "StaticLib"
    files { "../Engine/RenderSystem/**.h", "../Engine/RenderSystem/**.cpp" }
	includedirs { "../Engine/Common/" }
	includedirs { "../3rdParty/glfw_WIN32/include/", "../3rdParty/glew_WIN32/include" }
    
project "Math"
    kind "StaticLib"
    files { "../Engine/Math/**.h", "../Engine/Math/**.cpp", "../Engine/Math/**.inl" }
	
project "Common"
    kind "StaticLib"
    files { "../Engine/Common/**.h", "../Engine/Common/**.cpp", "../Engine/Math/**.inl" }