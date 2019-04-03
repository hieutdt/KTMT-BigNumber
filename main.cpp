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
		cout << "Input file: ";
		std::getline(cin, inPath);
		while (!CheckFileExistence(inPath))
		{
			cout << "Input file: ";
			std::getline(cin, inPath);
		}
		cout << "Output file: ";
		std::getline(cin, outPath);
		cout << "Type (1-Int, 2-Float): ";
		cin >> type;
		while (type != 1 && type != 2)
		{
			cout << "Type (1-Int, 2-Float): ";
			cin >> type;
		}
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

