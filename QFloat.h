#ifndef _QFLOAT_H
#define _QFLOAT_H

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

class QFloat {
private: 
	bitset<128> data;
	string addFracString(string a, string b); // cong phan thap phan
	static void DevideFloat(string s, string &sInt, string &sFrac); // Chia so cham ra 2 phan nguyen & thap phan
	int getExponent();
public:
	QFloat();
	QFloat(string value);
	//QFloat(QFloat &x);

	string toString(); // In ra so cham dong
	string toBinary(); // In ra nhi phan

	void scanDec(string s); // nhap duoi dang so cham dong
	void scanBin(string s); // nhap duoi dang nhi phan

	bool operator>(QFloat &b);

	friend ostream& operator<<(ostream& os, QFloat &n);
	friend istream& operator>>(istream& is, QFloat &n);

	void operator=(const QFloat &n);
	QFloat operator+(QFloat b);
	QFloat operator/(QFloat b);
	QFloat operator*(QFloat b);
	QFloat operator-(QFloat b);
};

#endif