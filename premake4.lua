solution "liveGLUT"
	configurations {"Develop"}
	location "build"

	project "liveGLUT"
		kind "ConsoleApp"
		language "C++"
		files {
			"src/*.h",
			"src/*.cpp",
			"src/FileWatcher/FileWatcher.h",
			"src/FileWatcher/FileWatcher.cpp",
			"src/FileWatcher/FileWatcherImpl.h",
			"src/FileWatcher/FileWatcherImpl.cpp"
		}
		includedirs {
			"src"
		}

		configuration "windows"
			targetdir "bin/win"
			defines {
				"WIN32",
				"_CONSOLE"
			}
			files {
				"src/win/dynLib.cpp",
				"src/FileWatcher/FileWatcherWin32.cpp"
			}

		configuration "Develop"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize",
				"OptimizeSpeed",
				"Symbols",
				"NoEditAndContinue"
			}
