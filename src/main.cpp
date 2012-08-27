#include <iostream>
#include "liveGLUT.h"

using namespace std;

int main(int argc, char* argv[])
{
	liveGlutInit(argc, argv);
	liveGlutMainLoop();
	return 0;
}