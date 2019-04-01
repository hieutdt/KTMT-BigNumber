#include <iostream>
#include "QInt.h"
#include "QFloat.h"
#include "ManipulationModules.h"
using namespace std;

int main() {
	QFloat a, b;
	cout << "Nhap a = ";
	cin >> a;
	cout << "SO vua nhap: a = " << a << endl;
	/*cout << "So vua nhap a = " << a << endl;
	cout << "Day bit cua a = " << a.toBinary() << endl;*/

	cout << "Nhap b = ";
	cin >> b;
	/*cout << "So vua nhap b = " << b << endl;
	cout << "Day bit cua b = " << b.toBinary() << endl;*/
	
	QFloat c = a * b;
	cout << "a x b = " << c << endl;
	c = a - b;
	cout << "a - b = " << c << endl;
	c = a + b;
	cout << "a + b = " << c << endl;


	system("pause");
	return 0;
}

