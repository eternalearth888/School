#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Framework.h"

using std::cout;
using std::endl;

using PlayerCSharpAI::Framework;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	Framework framework(argc, argv);
	framework.Run();

	return 0;
}