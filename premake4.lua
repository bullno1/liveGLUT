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
			"src/FileWatcher/FileWatcherImpl.h"
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
			prebuildcommands {
				"copy /Y ..\\src\\hook.h ..\\bin\\win > NUL"
			}

		configuration "linux"
			targetdir "bin/linux"
			defines {
				"LINUX"
			}
			files {
				"src/linux/dynLib.cpp",
				"src/FileWatcher/FileWatcherLinux.cpp"
			}
			links {
				"dl",
				"GL",
				"glut",
				"boost_filesystem",
				"boost_system"
			}
			linkoptions{
				"-rdynamic"
			}
			prebuildcommands {
				"cp ../src/hook.h ../bin/linux"
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
