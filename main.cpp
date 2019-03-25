#include <iostream>
#include "QInt.h"

using namespace std;

int main() {
	QInt a, b, c;
	cout << "Nhap so a = ";
	cin >> a;

	cout << "Ma hexa cua a: " << a.toHexa() << endl;

	system("pause");
	return 0;
}