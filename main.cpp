#include <iostream>
#include "QInt.h"
#include "QFloat.h"
#include "ManipulationModules.h"
using namespace std;

int main() {
	//QFloat a, b;
	//cout << "a = ";
	//cin >> a;
	//cout << "So vua nhap: " << a << endl;
	//cout << "b = ";
	//cin >> b;
	//cout << "So vua nhap: " << b << endl;
	//QFloat c = a * b;
	//cout << "a * b = " << c << endl;
	solveAFile("input.txt", "output.txt");
	system("pause");
	return 0;
}

