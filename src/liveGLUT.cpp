#include <cstdlib>
#include <exception>
#include <iostream>
#include <glut.h>
#include <boost/filesystem.hpp>
#include "utils.h"
#include "dynLib.h"

namespace fs = boost::filesystem;

typedef int(*StartFunc)();

namespace
{

void* module = 0;
std::string compileCmd;
std::string stageCmd;
std::string libraryPath;

}

int compile()
{
	return system(compileCmd.c_str());
}

void stage()
{
	system(stageCmd.c_str());
}

void unload()
{
	if(module) 
	{
		dynLibFree(module);
		module = 0;
	}
}

StartFunc load()
{
	module = dynLibLoad(libraryPath.c_str());
	if(module)
	{
		return dynLibGet<StartFunc>(module, "start");
	}
	else
	{
		std::cout <<"Failed to load: " << std::endl;
		return NULL;
	}
}

void liveGlutReload()
{
	writeSeparator();

	if(compile() == 0)
	{
		logMsg("Unloading old module");
		unload();
		stage();
		std::cout << "Reloading module" << std::endl;
		glLoadIdentity();
		StartFunc start = load();
		start();
		glutPostRedisplay();
	}
	else
	{
		std::cout << "Compilation error" << std::endl;
	}

	writeSeparator();
}

void liveGlutMainLoop()
{
	if(compile() != 0) return;
	stage();
	StartFunc start = load();
	if(start)
		start();
}

void liveGlutInit(int argc, char* argv[])
{
	fs::path pathToProgram = fs::system_complete(argv[0]);
	fs::path programFolder = pathToProgram.parent_path();
	compileCmd = "\"\"" + (programFolder / "compile.bat").string() + "\" \"" + programFolder.string() + "\"\"";
	stageCmd = "\"\"" + (programFolder / "stage.bat").string() + "\"\"";
	libraryPath = (fs::current_path() / "tmp" / "main.bin").string();
}