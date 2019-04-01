#include <iostream>
#include "QInt.h"
#include "QFloat.h"
#include "ManipulationModules.h"
using namespace std;

int main() {
<<<<<<< HEAD
	QFloat a, b;
	cout << "a = ";
	cin >> a;
	cout << "So vua nhap: " << a << endl;
	cout << a.toBinary() << endl;
	cout << "b = ";
	cin >> b;
	cout << "So vua nhap: " << b << endl;
	cout << b.toBinary() << endl;
	cout << endl;
	QFloat c = a + b;
	cout << "a + b = " << c << endl;

=======
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
>>>>>>> 7858626d3af643f04626795fa53046f0b5003ab5
	system("pause");
	return 0;
}

