#pragma once

#define glutInit hook_glutInit
#define __glutInitWithExit hook_glutInitWithExit
#define glutMainLoop hook_glutMainLoop
#define glutPostRedisplay hook_glutPostRedisplay
#define glutDestroyWindow hook_glutDestroyWindow
#define glutCreateWindow hook_glutCreateWindow
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
