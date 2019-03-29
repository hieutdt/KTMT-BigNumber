#include "QFloat.h"
#include "QInt.h"

void QFloat::scanDec(string s)
{
	this->data[127] = (s[0] == '-' ? 1 : 0); // Kiem tra so am
	if(s[0] == '-' || s[0] =='+') s.erase(0, 1);
	while(s[0]=='0') s.erase(0, 1); // Xoa so 0 thua ben trai

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
			if (sFrac[sFrac.length()-1] == '0') { // Kiem tra phan thap phan bang 0 hay chua
				break;
			}
		}
		else
			qFrac += "0";
	}
	
	int e = (qInt.toBinary(1).length() - 1) + 16383; // So Exponent, so bias 15 bit
	if (e == 16383 && sInt=="0") e = 0;
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

void QFloat::scanBin(string s)
{
	for (int i = 0; i < (s.length() > 128 ? 128 : s.length()); i++)
	{
		this->data[127 - i] = (s[i] == '1' ? 1 : 0);
	}
}

string QFloat::toString()
{
	string result = (this->data[127] == 1?"-":"+"); // Kiem tra dau

	bitset<15> bE; // Exponent
	for (int i = 0; i < 15; i++)
	{
		bE[i] = this->data[126 - 14 + i];
	}

	int E = bE.to_ulong() - 16383; // Chuyen to Exponent sang so mu
	if (E == -16383) E = 0;

	string bInt = '1' + this->data.to_string().substr(16,E); // Phan nguyen o dang Binary
	string bFrac = this->data.to_string().substr(16 + E); // Phan thap phan o dang Binary
	while (bFrac[bFrac.length() - 1] == '0') // Xoa so 0 thua o phia ben phai phan Thap Phan
		bFrac.erase(bFrac.length() - 1, 1);
	result += QInt::binaryToDecimal(bInt) + '.';
	string sInt = "";
	string pow;
	int tLength = bFrac.length();
	int j = 0;
	for (int i = -1; i >= -tLength; i--)
	{
		if (bFrac[j++] == '0') continue;
		pow = QInt::twoPowN(i);
		sInt = this->addFracString(sInt, pow);
	}

	result += sInt;
	return result;
}

string QFloat::toBinary()
{
	return (this->data).to_string();
}

string QFloat::addFracString(string a, string b)
{
	string result;
	int lA = a.length(),
		lB = b.length(),
		l = abs(lA - lB);
	for (int i = 0; i < l; i++)
	{
		if (lA < lB) a += "0";
		else b += "0";
	}
	result = QInt::addString(a, b);

	while (result[result.length() - 1] == '0') // Xoa so 0 thua o phia ben phai
		result.erase(result.length() - 1, 1);
	return result;
}

QFloat::QFloat()
{
}

ostream & operator<<(ostream & os, QFloat & n)
{
	os << n.toString();
	return os;
}

istream & operator>>(istream & is, QFloat & n)
{
	string tmp;
	is >> tmp;
	n.scanDec(tmp);
	return is;
}
