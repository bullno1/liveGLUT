#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void* dynLibLoad(const char* libname)
{
	return LoadLibraryA(libname);
}

void* dynLibGet(void* lib, const char* funcName)
{
	return GetProcAddress((HMODULE)lib, funcName);
}

void dynLibFree(void* lib)
{
	FreeLibrary((HMODULE)lib);
}
