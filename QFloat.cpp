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
	
	int e = 0;
	string bInt = qInt.toBinary();
	bool founded = false;
	for (int i = bInt.length() - 1; i >= 0; i--)
		if (bInt[i] == '1') {
			e = bInt.length() - i;
			founded = true;
			break;
		}

	if (!founded) { //phan so nguyen la 0
		for (int i = 0; i < qFrac.length(); i++) {
			if (qFrac[i] == '1') {
				e = - (i + 1);
				founded = true;
				break;
			}
		}
	}

	e += 16383; // So Exponent, so bias 15 bit
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

	cout << this->data.to_string() << endl;
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
	string bInt;
	string bFrac;

	bitset<15> bE; // Exponent
	for (int i = 0; i < 15; i++)
	{
		bE[i] = this->data[126 - 14 + i];
	}

	int E = bE.to_ulong() - 16383; // Chuyen to Exponent sang so mu
	if (E == -16383) E = 0;


	if (E >= 0) {
		bInt = '1' + this->data.to_string().substr(16, E); // Phan nguyen o dang Binary
		bFrac = this->data.to_string().substr(16 + E); // Phan thap phan o dang Binary
		// Xoa so 0 thua o phia ben phai phan Thap Phan
	}
	else {
		bFrac = this->data.to_string().substr(16);
	}

	//Xoa so 0 thua sau phan thap phan
	int count = 0;
	for (int i = bFrac.length() - 1; i >= 0; i--)
		if (bFrac[i] != '0')
			break;
		else
			count++;
	bFrac.erase(bFrac.length() - count);

	//In phan nguyen
	if (E >= 0)
		result += QInt::binaryToDecimal(bInt) + '.';
	else {
		result += "0.";
	}

	//In phan thap phan
	stringstream ss;
	for (int i = 0; i < (-1 - E) - 1; i++) {
		ss << "0";
	}
	ss << bFrac;
	bFrac = ss.str();
	
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

QFloat::QFloat(string value) {
	scanDec(value);
}

ostream & operator<<(ostream & os, QFloat & n)
{
	string res = n.toString();
	if (res[res.length() - 1] == '.')
		res += "0";
	cout << res;
	return os;
}

istream & operator>>(istream & is, QFloat & n)
{
	string tmp;
	is >> tmp;
	n.scanDec(tmp);
	return is;
}

int QFloat::getExponent() {
	bitset<15> bE; // Exponent
	for (int i = 0; i < 15; i++)
	{
		bE[i] = this->data[126 - 14 + i];
	}

	int E = bE.to_ulong() - 16383; // Chuyen to Exponent sang so mu
	if (E == -16383) E = 0;

	return E;
}

QFloat QFloat::operator*(QFloat b) {
	QFloat zero("0");
	QFloat ans;

	if (this->data == 0 || b.data == 0) {
		return zero;
	}

	string A = this->toBinary();
	string B = b.toBinary();
	
	bool isNegativeA = A[0] == '1';
	bool isNegativeB = B[0] == '1';

	int expA = this->getExponent();
	int expB = b.getExponent();
	int exp = expA + expB;

	string sigA = "1" + A.substr(16);
	string sigB = "1" + B.substr(16);

	//Xoa so 0 thua
	int count = 0;
	for (int i = sigA.length() - 1; i >= 0; i--) {
		if (sigA[i] != '0')
			break;
		else
			count++;
	}
	sigA.erase(sigA.length() - count);

	count = 0;
	for (int i = sigB.length() - 1; i >= 0; i--) {
		if (sigB[i] != '0')
			break;
		else
			count++;
	}
	sigB.erase(sigB.length() - count);

	if (sigA.length() > 64)
		sigA.erase(64);
	if (sigB.length() > 64)
		sigB.erase(64);

	int nA = sigA.length() - 1;
	int nB = sigB.length() - 1;



	//Nhan 2 phan sig
	QInt int_sigA;
	int_sigA.BinToQInt(sigA);
	QInt int_sigB;
	int_sigB.BinToQInt(sigB);
	QInt int_mulSig = int_sigA * int_sigB;

	string sigMul = int_mulSig.toBinary(1);
	
	int n = sigMul.length() - nA - nB;
	if (n > 1) {
		exp += (n - 1);
	}
	sigMul.erase(0, 1);

	exp += 16383; //chuyen ve dang Bias

	//Kiem tra truong hop 2 so khac dau -> tra ve so am
	if (isNegativeA + isNegativeB == 1)
		ans.data[127] = 1;
	else
		ans.data[127] = 0;

	//Ghi phan Exponent vao ans
	for (int i = 1; i < 16; i++) {
		ans.data[127-(16 - i)] = exp % 2;
		exp /= 2;
	}

	//Ghi phan gia tri vao ans
	for (int i = 0; i < (sigMul.length() <= 111 ? sigMul.length() : 111); i++)
		ans.data[127-(17 + i - 1)] = sigMul[i] == '1' ? 1 : 0;

	return ans;
}