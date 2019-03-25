#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


class QInt {
public:
	const static int NUM_OF_INT = 4;
	int data[NUM_OF_INT];


	int oddToOne(char c);
	void changeBit(int pos);
	int getBit(int post);
	void addToOne();
	void stringToQInt(string val);
	static string addString(string a, string b);
	string stringDivTwo(string s);
	static string twoPowN(int n);

public:
	QInt();
	QInt(string x);

	string toBinary();
	string toString();
	string toHexa();

	void operator=(const QInt &n);
	QInt operator+(QInt &b);
	QInt operator-(QInt &b);
	//QInt operator*(QInt &b);
	//QInt operator/(QInt &b);
	QInt operator<<(int n);
	QInt operator>>(int n);

	bool operator>(QInt &b);
	bool operator<(QInt &b);
	bool operator>=(QInt &b);
	bool operator<=(QInt &b);
	bool operator!=(QInt &b);
	bool operator==(QInt &b);

	static string binaryToDecimal(string binary);
	static string binaryToHexa(string binary);

	friend ostream& operator<<(ostream& os, QInt &n);
	friend istream& operator>>(istream& is, QInt &n);
};