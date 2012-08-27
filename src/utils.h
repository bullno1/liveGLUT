#include <iostream>

template<typename T>
void logMsg(T t)
{
	std::cout << t << std::endl;
}

static inline void writeSeparator()
{
	logMsg("------------------------------------");
}