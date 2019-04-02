#include <iostream>
#include "QInt.h"
#include "QFloat.h"
#include "ManipulationModules.h"
using namespace std;

int main() {
	QFloat a, b;
	cout << "Nhap a = ";
	cin >> a;
<<<<<<< HEAD
	cout << "So vua nhap: " << a << endl;
	cout << a.toBinary(1) << endl;
	cout << "b = ";
	cin >> b;
	cout << "So vua nhap: " << b << endl;
	cout << b.toBinary(1) << endl;
	cout << endl;
	QFloat c = a / b;
	cout << "a / b = " << c << endl;
=======
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


>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
	system("pause");
	return 0;
}

