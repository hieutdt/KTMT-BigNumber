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
	bitset<1> sign;
	bitset<15> exponent;
	bitset<112> mantissa;

	string addFracString(string a, string b); // cong phan thap phan
	static void DevideFloat(string s, string &sInt, string &sFrac); // Chia so cham ra 2 phan nguyen & thap phan
	int getExponent();

	// Kiem tra cac truong hop dac biet
	bool isZero(); // So 0
	bool isDenormalized(); // So khong the chuan hoa
	bool isInfinity(); // So vo cung
	bool isNaN(); //S bao loi NaN - Not a Number
	void clean(string &s, bool isLeft = 1, bool isRight = 1, bool deep = 0); // Xoa so 0 thua;
	void round(string &a);
public:
	QFloat();
	QFloat(string value);

	static QFloat zero();
	static QFloat infinity(); 
	static QFloat NaN();

	static int compareBinaryString(string A, string B);
	static string subBinaryString(string A, string B);

	void scanDec(string s); // nhap duoi dang so cham dong
	void scanBin(string s); // nhap duoi dang nhi phan

	string toString(); // In ra so cham dong
	string toBinary(bool isClean = 0); // In ra nhi phan

	bool operator<(QFloat &b);

	friend ostream& operator<<(ostream& os, QFloat &n);
	friend istream& operator>>(istream& is, QFloat &n);

	void operator=(const QFloat &n);
	QFloat operator+(QFloat &n);
	QFloat operator-(QFloat &n);
	QFloat operator/(QFloat &n);
	QFloat operator*(QFloat &x);
};

#endif