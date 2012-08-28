#include <dlfcn.h>

void* dynLibLoad(const char* libname)
{
	return dlopen(libname, RTLD_NOW);
}

void* dynLibGet(void* lib, const char* funcName)
{
	return dlsym(lib, funcName);
}

void dynLibFree(void* lib)
{
	dlclose(lib);
}
