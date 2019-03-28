#include "QFloat.h"
#include "QInt.h"

void QFloat::scan(string s)
{
	this->data[127] = (s[0] == '-' ? 1 : 0); // Kiem tra so am
	if(s[0] == '-') s.erase(0, 1);
	size_t found = s.find('.');
	string sInt; // Lay phan nguyen
	string sFrac = "";// Lay phan thap phan

	if (found != std::string::npos) {
		sInt = s.substr(0, found);
		sFrac = s.substr(found +1);
	}
	else {
		sInt = s.substr(0);
	}

	QInt qInt(sInt); // Chuyen phan nguyen ve nhi phan
	string qFrac = ""; //  Chuyen phan thap phan ve nhi phan

	if(sFrac.length()>0)
	for (int i = 0; i < 112; i++)
	{
		int y = sFrac.length();
		sFrac = QInt::addString(sFrac, sFrac);
		if (sFrac.length() > y) { 
			sFrac.erase(0,1);
			qFrac += "1";
			if (sFrac[0] == '0') { // Kiem tra phan thap phan bang 0 hay chua
				break;
			}
		}
		else
			qFrac += "0";
	}

	int e = (qInt.toBinary(1).length() - 1) + 16383; // So Exponent, so bias 15 bit
	bitset<15> bE(e); // Exponent sang Binary

	for (int i = 0; i <15; i++)
	{
		this->data[127 - 15 + i] = bE[i];
	}
	
	string significand = qInt.toBinary(1).substr(1) + qFrac;
	
	for (int i = 0; i < (significand.length()>112?112:significand.length()); i++)
	{
		this->data[127 - 1 - 15 - i] = (significand[i] == '1' ? 1 : 0);
	}
}

QFloat::QFloat()
{
}

QFloat::QFloat(string s)
{
	this->scan(s);
}

ostream & operator<<(ostream & os, QFloat & n)
{
	os << n.data;
	return os;
}

istream & operator>>(istream & is, QFloat & n)
{
	string tmp;
	is >> tmp;
	n.scan(tmp);
	return is;
}
