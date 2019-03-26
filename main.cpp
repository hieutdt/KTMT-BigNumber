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
	cout << "a / b = " << c << endl;

	system("pause");
	return 0;
}

