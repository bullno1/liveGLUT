#include <cstdlib>
#include <exception>
#include <iostream>
#include <boost/filesystem.hpp>
#include "platformGlut.h"
#include "utils.h"
#include "dynLib.h"

namespace fs = boost::filesystem;

#ifdef WIN32
#define COMPILE_SCRIPT "compile.bat"
#define STAGE_SCRIPT "stage.bat"
#endif

#ifdef __linux__
#define COMPILE_SCRIPT "compile.sh"
#define STAGE_SCRIPT "stage.sh"
#endif

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
		return dynLibGet<StartFunc>(module, "main");
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

std::string quote(std::string str)
{
	return "\"" + str + "\"";
}

void liveGlutInit(int argc, char* argv[])
{
	fs::path pathToProgram = fs::system_complete(argv[0]);
	fs::path programFolder = pathToProgram.parent_path();
	compileCmd = quote((programFolder / COMPILE_SCRIPT).string()) + " " + quote(programFolder.string());
	stageCmd = quote((programFolder / STAGE_SCRIPT).string());
#ifdef WIN32
	compileCmd = quote(compileCmd);
	stageCmd = quote(stageCmd);
#endif
	libraryPath = (fs::current_path() / "tmp" / "main.bin").string();
}
