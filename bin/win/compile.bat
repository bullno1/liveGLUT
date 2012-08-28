@echo off
cl liveGLUT.lib main.cpp -DWIN32 /nologo /Fotmp\ /Zi /MD /I%1 /FI"hook.h" /EHsc /link /DLL /OUT:tmp\main.tmp /LIBPATH:%1