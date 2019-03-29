#include <iostream>
#include "QInt.h"
#include "QFloat.h"
using namespace std;

int main() {
	QFloat qfA;
	qfA.scanDec("1.2");
	cout << qfA.toBinary() << endl;
	cout << qfA.toString() << endl;
	/*QInt a, b, c;
	cout << "Nhap so a = ";
	cin >> a;
	cout << "Nhap so b = ";
	cin >> b;
	c = a / b;
	cout << "c = " << c << endl;
	cout << "a = " << a << endl;
	c = ~a;
	cout << c << endl;

	a.rol(5);
	cout << "a = " << a << endl;

	a.ror(5);
	cout << "a = " << a << endl;
*/
	system("pause");
	return 0;
}

