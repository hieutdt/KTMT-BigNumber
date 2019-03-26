#include <iostream>
#include "QInt.h"

using namespace std;

int main() {
	QInt a, b, c;
	cout << "Nhap so a = ";
	cin >> a;
	cout << "Nhap so b = ";
	cin >> b;

	c = a / b;
	cout << "c = " << c << endl;
	cout << "a = " << a << endl;
	c = ~a;
	cout << c << endl;

	system("pause");
	return 0;
}

