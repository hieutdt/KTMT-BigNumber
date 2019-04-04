#include <iostream>
#include "QInt.h"
#include "QFloat.h"
#include "ManipulationModules.h"
using namespace std;

int main(int argc, char **argv) {
	if (!CheckArguments(argc,argv))
	{
		return -1;
	}
	std::string inPath;
	std::string outPath;
	int type;
	if (argc == 1)
	{
		ExecuteScreen();
		return 0;
	}
	else
	{
		inPath = argv[1];
		outPath = argv[2];
		type = argv[3][0] - '0';
	}
	solveAFile(inPath, outPath, type);
	return 0;
}

