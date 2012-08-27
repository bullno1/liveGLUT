#pragma once

//#define glutInit hook_glutInit
#define __glutInitWithExit hook_glutInitWithExit
#define glutMainLoop hook_glutMainLoop
#define glutPostRedisplay hook_glutPostRedisplay
#define glutDestroyWindow hook_glutDestroyWindow
//#define glutCreateWindow hook_glutCreateWindow
#define __glutCreateWindowWithExit hook_glutCreateWindowWithExit
#define glutInitWindowSize hook_glutInitWindowSize

#include <cstdlib>

int main(int, char**);

#ifdef __cplusplus
extern "C" {
#endif

extern __declspec(dllexport) int start()
{
	return main(__argc, __argv);
}

#ifdef __cplusplus
}
#endif