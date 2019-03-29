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
public:
	QFloat();

	string toString(); // In ra so cham dong
	string toBinary(); // In ra nhi phan

	void scanDec(string s); // nhap duoi dang so cham dong
	void scanBin(string s); // nhap duoi dang nhi phan

	friend ostream& operator<<(ostream& os, QFloat &n);
	friend istream& operator>>(istream& is, QFloat &n);
};

#endif