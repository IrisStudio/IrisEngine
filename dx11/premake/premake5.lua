-- premake5.lua
workspace "IrisEditor"
   configurations { "Debug_DX11", "Release_DX11", "Final_DX11" }
   platforms { "x32", "x64" }
   location "../bin/"
   language "C++"
   
   filter "configurations:Debug_DX11"
      defines { "_DEBUG", "WIN64", "_WIN64", "_WINDOWS", "_USRDLL", "TW_EXPORTS" }
      flags { "Symbols" }

   filter "configurations:Release_DX11"
      defines { "NDEBUG", "WIN64", "_WIN64", "_WINDOWS", "_USRDLL", "TW_EXPORTS" }
      optimize "On"

project "IrisEditor"
   kind "WindowedApp"
   targetdir "../bin/%{cfg.buildcfg}"
   files { "../Source/**.h", "../Source/**.cpp", "../ThirdParty/expat/**.h", "../ThirdParty/expat/**.cpp" }
   libdirs { "../ThirdParty/expat", "../ThirdParty/AntTweakBar/bin", "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64" }
   links {"AntTweakBar64", "d3d11", "d3dcompiler", "d3dx11", "dxerr", "dxguid", "winmm", "comctl32", "libexpat64", "dinput8", "DXGI", "D2D1", "dwrite"}
   includedirs { "../ThirdParty/" }
   includedirs { "../ThirdParty/expat" }
   includedirs { "../ThirdParty/AntTweakBar" }
   includedirs { "../ThirdParty/AntTweakBar/include/" }
   includedirs { "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include" }