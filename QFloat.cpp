#include "QFloat.h"
#include "QInt.h"

void QFloat::DevideFloat(string s, string & sInt, string & sFrac)
{
	size_t found = s.find('.');
<<<<<<< HEAD
	sFrac = "0";
=======

>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
	if (found != std::string::npos) {
		sInt = s.substr(0, found);
		sFrac = s.substr(found + 1);
	}
	else {
		sInt = s.substr(0);
		sFrac = "0";
	}
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
<<<<<<< HEAD
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

	// Xoa so 0 thua o phia ben phai
	while (result[result.length() - 1] == '0')
=======
	result = QInt::addString(a, b);

	while (result[result.length() - 1] == '0') // Xoa so 0 thua o phia ben phai
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
		result.erase(result.length() - 1, 1);
	return result;
}

int QFloat::getExponent() {
<<<<<<< HEAD
	int E = this->exponent.to_ulong() - 16383; // Chuyen to Exponent sang so mu
	if (this->isZero()) E = 0;
	return (E);
}

bool QFloat::isZero()
{
	return (this->exponent.to_string() == string(15, '0')) && (this->mantissa.to_string() == string(112, '0'));
}

bool QFloat::isDenormalized()
{
	return (this->exponent.none() && !this->mantissa.none());
}

bool QFloat::isInfinity()
{
	return (this->exponent.all() && this->mantissa.none());
}

bool QFloat::isNaN()
{
	return (this->exponent.all() && !this->mantissa.none());
}

void QFloat::clean(string & s, bool isLeft, bool isRight, bool deep)
{
	if (deep) {
		if (isLeft)  while (s.substr(0, 1) == "0") s.erase(0, 1);
		if (isRight) while (s.length() >= 1 && s.substr(s.length() - 1, 1) == "0") s.erase(s.length() - 1);
	}
	else {
		if (isLeft)  while (s.substr(0, 2) == "00") s.erase(0, 1);
		if (isRight) while (s.length() >= 2 && s.substr(s.length() - 2, 2) == "00") s.erase(s.length() - 1);
	}
}


QFloat QFloat::zero()
{
	QFloat x;
	return x;
}

QFloat QFloat::infinity()
{
	QFloat x;
	x.exponent = x.exponent.set();
	x.mantissa = x.mantissa.reset();
	return x;
}

QFloat QFloat::NaN()
{
	QFloat x;
	x.exponent = x.exponent.set();
	x.mantissa = x.mantissa.set();
	return x;
}

void QFloat::scanDec(string s)
{
	this->sign = (s[0] == '-' ? 1 : 0); // Kiem tra so am
	if (s[0] == '-' || s[0] == '+') s.erase(0, 1);

	// Xoa so 0 thua ben trai va phai
	this->clean(s);

	//Cat chuoi
	string sInt="0", sFrac;
	this->DevideFloat(s, sInt, sFrac);

	//Chuyen ve nhi phan
=======
	bitset<15> bE; // Exponent
	for (int i = 0; i < 15; i++)
	{
		bE[i] = this->data[126 - 14 + i];
	}

	int E = bE.to_ulong() - 16383; // Chuyen to Exponent sang so mu
	if (E == -16383) E = 0;

	return (E);
}


void QFloat::scanDec(string s)
{
	this->data[127] = (s[0] == '-' ? 1 : 0); // Kiem tra so am
	if(s[0] == '-' || s[0] =='+') s.erase(0, 1);
	// Xoa so 0 thua ben trai va phai
	while(s.substr(0,2) =="00") s.erase(0, 1); 

	string sInt, sFrac;
	this->DevideFloat(s,sInt, sFrac);
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
	QInt qInt(sInt); // Chuyen phan nguyen ve nhi phan
	string qFrac = ""; //  Chuyen phan thap phan ve nhi phan
	stringstream ss;

<<<<<<< HEAD
	if(sFrac.length()>0 && sFrac!="0")
		for (int i = 0; i < 112; i++)
		{
			int y = sFrac.length();
			sFrac = QInt::addString(sFrac, sFrac);
			if (sFrac.length() > y) {
				sFrac.erase(0, 1);
				ss << "1";
				// Kiem tra phan thap phan bang 0 hay chua
				if (sFrac == string(sFrac.length(), '0')) {
					break;
				}
			}
			else
				ss << "0";
=======
	for (int i = 0; i < 112; i++)
	{
		int y = sFrac.length();
		sFrac = QInt::addString(sFrac, sFrac);
		if (sFrac.length() > y) {
			sFrac.erase(0, 1);
			ss << "1";
			if (sFrac == string(sFrac.length(),'0')) { // Kiem tra phan thap phan bang 0 hay chua
				break;
			}
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
		}
	qFrac = ss.str();

	string bInt = qInt.toBinary(1);
	int e = 16383;

	if (sInt == "0") {
		if (qFrac == "") {
			e = 0;
		}
		else {
			size_t found = qFrac.find('1');
			qFrac.erase(0, found + 1);
			e -= found + 1;
		}
	}
	else {
		e += bInt.length() - 1;
	}
	this->exponent = bitset<15>(e);
	string temp = bInt.substr(1) + qFrac;
	for (int i = 0; i < (temp.length()>112?112: temp.length()); i++)
	{
		this->mantissa[112 - 1 - i] = (temp[i]=='1'?1:0);
	}
}

void QFloat::scanBin(string s)
{
	this->sign = (s[0] == '1' ? 1 : 0);
	this->exponent = bitset<15>(s.substr(1, 15));
	this->mantissa = bitset<112>(s.substr(16));
}


<<<<<<< HEAD
=======

>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
string QFloat::toString()
{
	string result = (this->sign == 1 ? "-" : "+"); // Kiem tra dau
	string bInt = "0";
	string bFrac;

<<<<<<< HEAD
	int E = this->getExponent();

	if (this->isZero()) return "0";
=======
	int E = getExponent();
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a

	if (this->data.to_string().substr(1) == string(127, '0')) return "0";
	if (E >= 0) { //So lon hon 1
		bInt = '1' + this->mantissa.to_string().substr(0, E); //Phan nguyen o dang Binary
		bFrac = this->mantissa.to_string().substr(E); // Phan thap phan o dang Binary
		result += QInt::binaryToDecimal(bInt);
	}
	else { //So be hon 1
		bFrac = string(abs(E) - 1, '0') + '1' + this->mantissa.to_string();
		result += "0";
	}
	clean(bFrac, 0, 1, 1);

	result += ".";

	//In phan thap phan
	string sInt = "0";
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

<<<<<<< HEAD
string QFloat::toBinary(bool isClean)
{
	return this->sign.to_string() + (isClean?" ":"")+ this->exponent.to_string() + (isClean ? " " : "")+ this->mantissa.to_string();
=======
string QFloat::toBinary()
{
	return (this->data).to_string();
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
}

QFloat::QFloat()
{
}

QFloat::QFloat(string value) {
	scanDec(value);
}

<<<<<<< HEAD

bool QFloat::operator<(QFloat & b)
{
	int eA = this->getExponent(),
		eB = b.getExponent();

	if (eA < eB) return true;
	else if (eA == eB) {
		for (int i = 111; i >= 0; i--)
			if (this->mantissa[i] < b.mantissa[i])
				return true;
			else if (this->mantissa[i] > b.mantissa[i])
				return false;
	}
	return false;
=======
//QFloat::QFloat(QFloat & x)
//{
//	this->data = x.data;
//}

bool QFloat::operator>(QFloat & b)
{
	bool flag = false;
	int eA = this->getExponent(),
		eB = b.getExponent();
	if (this->data[127] == 0 && b.data[127] == 1) return true;
	else if (this->data[127] == 1 && b.data[127] == 0) return false;

	if (eA > eB) flag = true;
	else if(eA == eB){
		for (int i = 127 - 1 - 15; i >=0; i--)
		{
			if (this->data[i] > b.data[i]) flag= true;
				
		}
	}
	if (this->data[127] == 1 && b.data[127] == 1) flag = !flag;
	return flag;
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
}

ostream & operator<<(ostream & os, QFloat & n)
{
	string res = n.toString();
	os << res;
	return os;
}

istream & operator>>(istream & is, QFloat & n)
{
	string tmp;
	is >> tmp;
	n.scanDec(tmp);
	return is;
}


void QFloat::operator=(const QFloat & n)
{
<<<<<<< HEAD
	this->sign = n.sign;
	this->exponent = n.exponent;
	this->mantissa = n.mantissa;
}

QFloat QFloat::operator+(QFloat &n)
{
	QFloat result, a = *this, b = n;
	if (a.sign == b.sign) result.sign = a.sign;
	if (a < b) {
		QFloat c = a;
		a = b;
		b = c;
=======
	this->data = n.data;
}

QFloat QFloat::operator+(QFloat b)
{
	QFloat result, *a = new QFloat();
	*a = *this;
	if (b > *a) {
		bitset<128> temp = a->data;
		a->data = b.data;
		b.data = temp;
	}

	bitset<15> e(a->data.to_string().substr(1,15));
	int E = e.to_ulong() - bitset<15>(b.data.to_string().substr(1, 15)).to_ulong();
	if (E > 16383) E -= 16383;

	bitset<113> significandA(a->data.to_string().substr(16));
	bitset<113> significandB(b.data.to_string().substr(16));
	if (E > 0) {
		significandB = significandB >> E+1;
		significandB[112 - E-1] = 1;
	}
	else {
		significandB = significandB >> 1;
		significandB[112] = 1;
	}
	significandA = significandA >> 1;
	significandA[112] = 1;

	bitset<113> significand;
	int ex = 0;
	for (int i = 0; i <= 112; i++) {
		int abit = significandA[i];
		int bbit = significandB[i];

		if (abit + bbit + ex == 0)
			continue;
		else if (abit + bbit + ex == 1) {
			significand[i] = 1;
			ex = 0;
		}
		else if (abit + bbit + ex == 2) {
			ex = 1;
		}
		else if (abit + bbit + ex == 3) {
			significand[i] = 1;
			ex = 1;
		}
	}

	if (ex==0) {
		significand = significand << 1;
	}
	else {
		e = bitset<15>(e.to_ulong() + 1);
	}

	for (int i = 0; i < 112; i++)
	{
		result.data[i] = significand[i];
	}
	for (int i = 0; i < 15; i++)
	{
		result.data[i + 112] = e[i];
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
	}
	if (a.sign == 1 && b.sign == 0) result.sign = 1;
	if (a.isZero() && b.isZero()) return QFloat("0");
	else if (a.isZero()) return b;
	else if (b.isZero()) return a;
	result.exponent = a.exponent;

<<<<<<< HEAD
	int E = abs(a.getExponent() - b.getExponent());

	if (E > 0) {
		b.mantissa = b.mantissa >> E + 1;
		b.mantissa[111 - E] = 1;
	}
	else {
		b.mantissa = b.mantissa >> 1;
		b.mantissa[111] = 1;
	}

	a.mantissa = a.mantissa >> 1;
	a.mantissa[111] = 1;

	int ex = 0;
	// Cung dau
	if (a.sign == b.sign){
		for (int i = 0; i <= 111; i++) {
			int abit = a.mantissa[i];
			int bbit = b.mantissa[i];

			if (abit + bbit + ex == 0)
				continue;
			else if (abit + bbit + ex == 1) {
				result.mantissa[i] = 1;
				ex = 0;
			}
			else if (abit + bbit + ex == 2) {
				ex = 1;
			}
			else if (abit + bbit + ex == 3) {
				result.mantissa[i] = 1;
				ex = 1;
			}
		}
		if (ex == 0) {
			result.mantissa = result.mantissa << 1;
		}
		else if (ex == 1) {
			result.exponent = bitset<15>(result.exponent.to_ulong() + 1);
		}
	}
	// Trai dau
	else{
		for (int i = 0; i <= 111; i++) {
			int abit = a.mantissa[i];
			int bbit = b.mantissa[i];

			if (abit - bbit - ex == 0)
				ex = 0;
			else if (abit - bbit - ex == -1) {
				result.mantissa[i] = 1;
				ex = 1;
			}
			else if (abit - bbit - ex == 1) {
				result.mantissa[i] = 1;
				ex = 0;
			}
			else if (abit - bbit - ex == -2) {
				ex = 1;
			}
		}

		if (result.mantissa[111]==0) {
			int j = 0;
			int tempE = result.exponent.to_ulong();

			while (j < 111 && result.mantissa[111 - j] == 0) {
				tempE--;
				j++;
			}
			if (result.mantissa[111 - j] == 0)
				result.exponent = bitset<15>(0);
			else {
				result.exponent = bitset<15>(tempE);
				result.mantissa = result.mantissa << j+1;
			}
		}
		else{
			result.mantissa = result.mantissa << 1;
		}
	}
=======
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
	return result;
}

QFloat QFloat::operator-(QFloat & n)
{
	QFloat a = *this, b = n;
	b.sign = b.sign.flip();
	return a + b;
}

QFloat QFloat::operator/(QFloat &x)
{
	QFloat result, a = *this, b = x;
	if (b.isZero()) {
		if (a.isZero()) return QFloat::NaN();
		else return QFloat::infinity();
	}
	else if (a.isZero()) return QFloat::zero();

<<<<<<< HEAD
	result.sign = a.sign ^ b.sign;
=======
	string A = this->toBinary();
	string B = b.toBinary();
	
	bool isNegativeA = (A[0] == '1');
	bool isNegativeB = (B[0] == '1');
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a

	int E = a.getExponent() - b.getExponent() + 16383;

	string sigA = "1" + a.mantissa.to_string();
	string sigB = "1" + b.mantissa.to_string();

	//Xoa so 0 thua
	this->clean(sigA, 0, 1, 1);
	this->clean(sigB, 0, 1, 1);

	// Thuc hien phep chia 2 mantissa


<<<<<<< HEAD
	result.exponent = bitset<15>(E);
	/*for (int i = 0; i < (sigMul.length() <= 111 ? sigMul.length() : 111); i++)
		result.mantissa[111 - i] = (sigMul[i] == '1' ? 1 : 0);
*/
	return result;
}

QFloat QFloat::operator*(QFloat &x) {
	QFloat ans, a = *this, b = x;

	if (a.isZero() || b.isZero()) return QFloat::zero();

	int E = a.getExponent() + b.getExponent() + 16383;

	string sigA = "1" + a.mantissa.to_string();
	string sigB = "1" + b.mantissa.to_string();

	//Xoa so 0 thua
	this->clean(sigA, 0, 1, 1);
	this->clean(sigB, 0, 1, 1);

	if (sigA.length() > 64)	sigA.erase(64);
	if (sigB.length() > 64)	sigB.erase(64);

	int nA = sigA.length() - 1;
	int nB = sigB.length() - 1;

=======
>>>>>>> 2d9751204fc6e156325cad207560522900fcc68a
	//Nhan 2 phan sig
	QInt int_sigA, int_sigB;
	int_sigA.BinToQInt(sigA);
	int_sigB.BinToQInt(sigB);
	QInt int_mulSig = int_sigA * int_sigB;

	string sigMul = int_mulSig.toBinary(1);

	int n = sigMul.length() - nA - nB;
	if (n > 1) {
		E += (n - 1);
	}
	sigMul.erase(0, 1);

	//Kiem tra truong hop 2 so khac dau -> tra ve so am
	if (a.sign != b.sign)
		ans.sign = 1;
	else
		ans.sign = 0;

	//Ghi phan Exponent vao ans
	ans.exponent = bitset<15>(E);

	//Ghi phan gia tri vao ans
	for (int i = 0; i < (sigMul.length() <= 111 ? sigMul.length() : 111); i++)
		ans.mantissa[111 - i] = (sigMul[i] == '1' ? 1 : 0);

	return ans;
}

QFloat QFloat::operator-(QFloat b) {
	QFloat result, *a = new QFloat();
	*a = *this;
	if (b > *a) {
		bitset<128> temp = a->data;
		a->data = b.data;
		b.data = temp;
	}

	bitset<15> e(a->data.to_string().substr(1, 15));
	int E = e.to_ulong() - bitset<15>(b.data.to_string().substr(1, 15)).to_ulong();
	if (E > 16383) E -= 16383;

	bitset<113> significandA(a->data.to_string().substr(16));
	bitset<113> significandB(b.data.to_string().substr(16));
	if (E > 0) {
		significandB = significandB >> E + 1;
		significandB[112 - E - 1] = 1;
	}
	else {
		significandB = significandB >> 1;
		significandB[112] = 1;
	}
	significandA = significandA >> 1;
	significandA[112] = 1;

	bitset<113> significand;
	int ex = 0;
	for (int i = 0; i <= 112; i++) {
		int abit = significandA[i];
		int bbit = significandB[i];

		if (abit - bbit - ex == 0) {
			significand[i] = 0;
			continue;
		} 
		else if (abit - bbit - ex == -1) {
			significand[i] = 1;
			ex = 1;
			continue;
		}
		else if (abit - bbit - ex == 1) {
			significand[i] = 1;
			ex = 0;
			continue;
		}
		else if (abit - bbit - ex == -2) {
			significand[i] = 0;
			ex = 1;
			continue;
		}
	}

	if (ex == 0) {
		significand = significand << 1;
	}
	else {
		e = bitset<15>(e.to_ulong() + 1);
	}

	cout << significandA.to_string() << endl;
	cout << significandB.to_string() << endl;
	cout << significand.to_string() << endl;

	for (int i = 0; i < 112; i++)
	{
		result.data[i] = significand[i];
	}
	for (int i = 0; i < 15; i++)
	{
		result.data[i + 112] = e[i];
	}

	return result;
}