#include <iostream>
#include "QInt.h"
#include "QFloat.h"
using namespace std;

int main() {
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

	system("pause");
	return 0;
}

