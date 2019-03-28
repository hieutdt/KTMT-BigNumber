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
	void scan(string s);
public:
	QFloat();
	QFloat(string s);

	friend ostream& operator<<(ostream& os, QFloat &n);
	friend istream& operator>>(istream& is, QFloat &n);
};

#endif