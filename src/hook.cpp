#include <cstdlib>
#include <glut.h>
#include <iostream>
#include <FileWatcher/FileWatcher.h>
#include "liveGLUT.h"
#include "utils.h"

using namespace FW;

FileWatcher watcher;
WatchID id;
int window = 0;
bool inLoop = false;

class Listener: public FileWatchListener
{
public:
	Listener()
		:dirty(false)
	{}

	void handleFileAction(WatchID watchid, const String& dir, const String& filename, Action action)
	{
		if(filename == "main.cpp")
			dirty = true;
	}

	bool dirty;
}listener;

void update(int)
{
	glutTimerFunc(1000.f / 60.f, &update, 0);
	watcher.update();
	if(listener.dirty)
	{
		listener.dirty = false;
		logMsg("Change detected");
		liveGlutReload();
	}
}

#define HOOKAPI(TYPE) extern __declspec(dllexport) TYPE __stdcall

bool inited = false;

extern "C"
{

HOOKAPI(void) hook_glutMainLoop()
{
	if(inLoop) return;

	id = watcher.addWatch(".", &listener, false);
	glutTimerFunc(0.1f, &update, 0);
	inLoop = true;

	logMsg("Starting");
	writeSeparator();
	glutMainLoop();
}

HOOKAPI(int) hook_glutCreateWindow(const char* title)
{
	if(window != 0)
	{
		glutSetWindowTitle(title);
		return window;
	}

	window = glutCreateWindow(title);
	return window;
}

HOOKAPI(void) hook_glutPostRedisplay()
{
	if(window)
		glutPostRedisplay();
}

HOOKAPI(int) hook_glutCreateWindowWithExit(const char* title, void (__cdecl *exitfunc)(int))
{
	return hook_glutCreateWindow(title);
}

HOOKAPI(void) hook_glutDestroyWindow(int id)
{
	window = 0;
	glutDestroyWindow(id);
}

HOOKAPI(void) hook_glutInit(int *argcp, char **argv)
{
	if(inited) return;
	inited = true;
	glutInit(argcp, argv);
}

HOOKAPI(void) hook_glutInitWithExit(int *argcp, char **argv, void (__cdecl *exitfunc)(int))
{
	hook_glutInit(argcp, argv);
}

HOOKAPI(void) hook_glutInitWindowSize(int width, int height)
{
	glutInitWindowSize(width, height);

	if(window)
	{
		glutReshapeWindow(width, height);
	}
}

}