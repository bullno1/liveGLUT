#pragma once

void* dynLibLoad(const char* libname);
void* dynLibGet(void* lib, const char* funcName);
void dynLibFree(void* lib);

template<typename T>
inline T dynLibGet(void* lib, const char* funcName)
{
	return reinterpret_cast<T>(dynLibGet(lib, funcName));
}
