#include <iostream>
#include "QInt.h"
#include "QFloat.h"
#include "ManipulationModules.h"
using namespace std;

int main() {
	QFloat a, b;

	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	QFloat c = a + b;
	cout << "a + b = " << c << endl;

	system("pause");
	return 0;
}

