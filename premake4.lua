
solution ("rot")
	configurations { "Debug", "Release" }

	project ("rot")
		kind "ConsoleApp"
		language "C++"
		location "build"
		files { "src/*.cpp" }
		includedirs { "include" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

