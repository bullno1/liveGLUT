#pragma once

#ifndef WIN32
#define glutInit hook_glutInit
#define glutCreateWindow hook_glutCreateWindow
#endif

#define __glutInitWithExit hook_glutInitWithExit
#define glutMainLoop hook_glutMainLoop
#define glutPostRedisplay hook_glutPostRedisplay
#define glutDestroyWindow hook_glutDestroyWindow
#define __glutCreateWindowWithExit hook_glutCreateWindowWithExit
#define glutInitWindowSize hook_glutInitWindowSize


#ifdef __cplusplus
extern "C" {
#endif

extern
#ifdef WIN32
__declspec(dllexport)
#endif
int main(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif
