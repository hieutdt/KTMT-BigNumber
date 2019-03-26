#include "QInt.h"
#include <algorithm>

//PRIVATE METHODS///////////////////////////////////////

int QInt::oddToOne(char c) {
	if (c == '1' || c == '3' || c == '5' || c == '7' || c == '9')
		return 1;
	return 0;
}

string QInt::stringDivTwo(string s) {
	stringstream ss;
	ss << "";

	int additive = 0;
	bool firstZero = true; //dung de xoa cac ky tu '0' o dau chuoi

	for (int i = 0; i < s.length(); i++) {
		int digit = (s[i] - '0') / 2 + additive;

		if (digit != 0)
			firstZero = false;

		if (!firstZero)
			ss << digit;

		additive = QInt::oddToOne(s[i]) * 5;
	}

	return ss.str();
}

void QInt::changeBit(int pos) {
	this->data[QInt::NUM_OF_INT - pos / 32 - 1] ^= (1 << (pos % 32));
}

int QInt::getBit(int pos) {
	int data = this->data[QInt::NUM_OF_INT - pos / 32 - 1];
	data &= (1 << (pos % 32));
	int ans = data >> (pos % 32);
	return abs(ans);
}

void QInt::addToOne() {
	string bytes = this->toBinary();
	int ex = 0;
	for (int i = bytes.length() - 1; i >= 0; i--) {
		if (bytes[i] == '0' && ex == 0) {
			bytes[i] = '1';
			break;
		} 
		else if (bytes[i] == '0' && ex == 1) {
			bytes[i] = '1';
			break;
		}
		else if (bytes[i] == '1' && ex == 0) {
			bytes[i] = '0';
			ex = 1;
		}
		else { //bytes[i] == '1' && ex == 1
			bytes[i] = '0';
		}
	}
	
	//Chuyen ve QInt tu Binary
	for (int i = 0; i < QInt::NUM_OF_INT; i++)
		this->data[i] = 0;

	for (int i = bytes.length() - 1; i >= 0; i--) {
		if (bytes[i] == '1')
			changeBit(127 - i);
	}
}

void QInt::stringToQInt(string val) {
	bool isNegative = false;

	//Neu la so am thi xoa ky tu dau tien
	if (val[0] == '-') {
		isNegative = true;
		val.erase(0, 1);
	}

	//Xoa so 0 thua
	int count = 0;
	for (int i = 0; i < val.length(); i++) {
		if (val[i] != '0')
			break;
		count++;
	}
	val.erase(0, count);

	//Khoi tao mang du lieu la 0
	for (int i = 0; i < QInt::NUM_OF_INT; i++) {
		this->data[i] = 0;
	}

	//So thu tu cua bit tinh tu phai sang trai
	int i = 0;

	while (val != "") {
		int excess = (val[val.length() - 1] - 48) % 2;
		if (excess == 1) {
			changeBit(i);
		}
		val = stringDivTwo(val);
		i++;
	}

	//Truong hop so am thi chuyen sang bu 2
	if (isNegative) {
		for (int i = 0; i < QInt::NUM_OF_INT; i++)
			this->data[i] = ~this->data[i];
		this->addToOne();
	}
}

string QInt::addString(string a, string b) {
	int aLen = a.length();
	int bLen = b.length();
	stringstream ss;
	int ex = 0; //bien nho

	//Doi vi tri de chuoi a la chuoi dai hon
	if (bLen > aLen) {
		string st = a;
		a = b;
		b = st;
		int nt = aLen;
		aLen = bLen;
		bLen = nt;
	}

	for (int i = 0; i < aLen; i++) {
		int digitA = a[aLen - i - 1] - 48;
		int digitB = 0;

		if (i < bLen)
			digitB = b[bLen - i - 1] - 48;
	
		int sum = digitA + digitB + ex;
		ss << sum % 10;

		ex = sum >= 10 ? 1 : 0;
	}

	if (ex == 1) {
		ss << 1;
	}
	
	string ans = ss.str();
	std::reverse(ans.begin(), ans.end());
	return ans;
}

string QInt::twoPowN(int n) {
	string result = "1";
	if (n == 0)
		return "1";

	for (int i = 0; i < n; i++)
		result = QInt::addString(result, result);

	return result;
}

void QInt::binaryShiftLeft(string &bytes, int n) {
	stringstream ss;
	bytes.erase(0, n);
	ss << bytes;
	for (int i = 0; i < n; i++) {
		ss << '0';
	}

	bytes = ss.str();
}

void QInt::binaryShiftRight(string &bytes, int n) {
	stringstream ss;
	bytes.erase(127 - n, n);

	if (bytes[0] == '1') {
		for (int i = 0; i < n; i++)
			ss << "1";
	}
	else {
		for (int i = 0; i < n; i++)
			ss << "0";
	}

	ss << bytes;
	bytes = ss.str();
}

//PUBLIC METHODS ////////////////////////////////////////////

QInt::QInt() {
	for (int i = 0; i < QInt::NUM_OF_INT; i++)
		this->data[i] = 0;
}

QInt::QInt(string val) {
	this->stringToQInt(val);
}

string QInt::toBinary() {
	stringstream ss;
	
	for (int i = 0; i < QInt::NUM_OF_INT * 32; i++) {
		int bit = abs(getBit(i));
		ss << bit;
	}

	string ans = ss.str();
	std::reverse(ans.begin(), ans.end());

	return ans;
}

ostream& operator<<(ostream &os, QInt &n) {
	os << n.toString();
	return os;
}

istream& operator>>(istream &is, QInt &n) {
	string tmp;
	is >> tmp;
	n.stringToQInt(tmp);
	return is;
}

string QInt::toString() {
	string binary;
	string res = "0";
	stringstream ss;

	QInt tmp = *this;

	if (this->getBit(127) == 1) { //so am thi lay bu 2 thanh so duong truoc
		ss << "-";
		for (int i = 0; i < 4; i++)
			tmp.data[i] = ~tmp.data[i];
		tmp.addToOne();
	}
	
	binary = tmp.toBinary();

	for (int i = binary.length() - 1; i >= 0; i--) {
		if (binary[i] == '1') {
			string pow = tmp.twoPowN(binary.length() - i - 1);
			res = tmp.addString(res, pow);
		}
	}

	ss << res;
	res = ss.str();

	return res;
}

string QInt::binaryToDecimal(string binary) {
	string res = "0";
	stringstream ss;

	for (int i = binary.length() - 1; i >= 0; i--) {
		if (binary[i] == '1') {
			string pow = QInt::twoPowN(binary.length() - i - 1);
			res = QInt::addString(res, pow);
		}
	}

	ss << res;
	res = ss.str();

	return res;
}

void QInt::operator=(const QInt &n) {
	for (int i = 0; i < 4; i++)
		this->data[i] = n.data[i];
}

QInt QInt::operator+(QInt &b) {
	int ex = 0;
	QInt ans;

	for (int i = 0; i < 128; i++) {
		int abit = this->getBit(i);
		int bbit = b.getBit(i);

		if (abit + bbit + ex == 0)
			continue;
		else if (abit + bbit + ex == 1) {
			ans.changeBit(i);
			ex = 0;
		}
		else if (abit + bbit + ex == 2) {
			ex = 1;
		}
		else if (abit + bbit + ex == 3) {
			ans.changeBit(i);
			ex = 1;
		}
	}

	return ans;
}

string QInt::sumBinaryString(string &a, string &b) {
	int ex = 0;
	string ans;
	stringstream ss;
	for (int i = 0; i < 128; i++) {
		ss << "0";
	}
	ans = ss.str();

	for (int i = 127; i >= 0; i--) {
		int aDigit = a[i] - 48;
		int bDigit = b[i] - 48;

		if (aDigit + bDigit + ex == 0) {
			continue;
		}
		else if (aDigit + bDigit + ex == 1) {
			ans[i] = '1';
			ex = 0;
		}
		else if (aDigit + bDigit + ex == 2) {
			ex = 1;
		}
		else if (aDigit + bDigit + ex == 3) {
			ans[i] = '1';
			ex = 1;
		}
	}

	return ans;
}

QInt QInt::operator-(QInt &b) {
	QInt tmp = b; //So doi cua b

	for (int i = 0; i < 4; i++) {
		tmp.data[i] = ~tmp.data[i];
	}
	tmp.addToOne();

	return (*this + tmp);
}

bool QInt::operator>(QInt &b) {
	QInt res = *this - b;
	if (res.getBit(127) == '1') {
		return false;
	}
	return true;
}

bool QInt::operator<(QInt &b) {
	QInt res = *this - b;
	if (res.getBit(127) == '1') {
		return true;
	}
	return false;
}

bool QInt::operator==(QInt &b) {
	string bytesA = this->toBinary();
	string bytesB = b.toBinary();

	return bytesA == bytesB;
}

bool QInt::operator!=(QInt &b) {
	string bytesA = this->toBinary();
	string bytesB = b.toBinary();

	return bytesA != bytesB;
}

bool QInt::operator>=(QInt &b) {
	return (*this > b || *this == b);
}

bool QInt::operator<=(QInt &b) {
	return (*this < b || *this == b);
}

QInt QInt::operator<<(int n) {
	stringstream ss;
	string bytes = this->toBinary();
	bytes.erase(0, n);
	ss << bytes;
	for (int i = 0; i < n; i++) {
		ss << '0';
	}

	bytes = ss.str();
	
	for (int i = 0; i < 4; i++)
		this->data[i] = 0;

	for (int i = 0; i < 128; i++) {
		if (bytes[i] == '1') {
			this->changeBit(127 - i);
		}
	}

	return *this;
}

QInt QInt::operator>>(int n) {
	stringstream ss;
	string bytes = this->toBinary();
	bytes.erase(127 - n, n);

	for (int i = 0; i < 4; i++)
		this->data[i] = 0;

	if (bytes[0] == '1') {
		for (int i = 0; i < n; i++)
			ss << "1";
	}
	else {
		for (int i = 0; i < n; i++)
			ss << "0";
	}

	ss << bytes;
	bytes = ss.str();

	for (int i = 0; i < 128; i++) {
		if (bytes[i] == '1') {
			this->changeBit(127 - i);
		}
	}

	return *this;
}

string QInt::binaryToHexa(string bin) {
	if (bin.length() % 8 != 0) {
		stringstream ss;
		for (int i = 0; i < bin.length() % 8; i++)
			ss << '0';
		ss << bin;
		bin = ss.str();
	}

	stringstream ss;
	char hexamap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	int count = 1;

	for (int i = 0; i < bin.length(); i++) {
		int sum = 0;
		for (int j = i; j < i + 4; j++) {
			int digit = bin[j] - 48;
			sum += (digit * pow(2, 3 - (j - i)));
		}

		if (count < 2) {
			ss << hexamap[sum];
			count++;
		}
		else {

			ss << hexamap[sum] << " ";
			count = 1;
		}

		i = i + 3;
	}

	return ss.str();
}

string QInt::toHexa() {
	string bin = this->toBinary();
	return QInt::binaryToHexa(bin);
}

QInt QInt::operator*(QInt b) {
	string A = this->toBinary();
	string B = b.toBinary();

	bool isNegativeA = (A[0] == '1');
	bool isNegativeB = (B[0] == '1');

	if (isNegativeA) {
		//Chuyen sang day nhi phan cua so duong
		for (int i = 0; i < 128; i++) {
			if (A[i] == '1')
				A[i] = '0';
			else
				A[i] = 1;
		}
		
		int ex = 0;
		for (int i = A.length() - 1; i >= 0; i--) {
			if (A[i] == '0' && ex == 0) {
				A[i] = '1';
				break;
			}
			else if (A[i] == '0' && ex == 1) {
				A[i] = '1';
				break;
			}
			else if (A[i] == '1' && ex == 0) {
				A[i] = '0';
				ex = 1;
			}
			else { //bytes[i] == '1' && ex == 1
				A[i] = '0';
			}
		}
	}

	if (isNegativeB) {
		for (int i = 0; i < 128; i++) {
			if (B[i] == '0')
				B[i] = '1';
			else
				B[i] = '0';
		}

		int ex = 0;
		for (int i = B.length() - 1; i >= 0; i--) {
			if (B[i] == '0' && ex == 0) {
				B[i] = '1';
				break;
			}
			else if (B[i] == '0' && ex == 1) {
				B[i] = '1';
				break;
			}
			else if (B[i] == '1' && ex == 0) {
				B[i] = '0';
				ex = 1;
			}
			else { //bytes[i] == '1' && ex == 1
				B[i] = '0';
			}
		}
	}

	stringstream ss;
	for (int i = 0; i < 128; i++)
		ss << "0";
	string sum = ss.str();

	for (int i = 0; i < 128; i++) {
		if (B[127 - i] == '1') {
			string temp = A;
			binaryShiftLeft(temp, i);
			sum = sumBinaryString(sum, temp);
		}
	}

	
	//Truong hop so am
	if (isNegativeA + isNegativeB == 1) {
		for (int i = 0; i < 128; i++)
			if (sum[i] == '0')
				sum[i] = '1';
			else
				sum[i] = '0';

		int ex = 0;
		for (int i = sum.length() - 1; i >= 0; i--) {
			if (sum[i] == '0' && ex == 0) {
				sum[i] = '1';
				break;
			}
			else if (sum[i] == '0' && ex == 1) {
				sum[i] = '1';
				break;
			}
			else if (sum[i] == '1' && ex == 0) {
				sum[i] = '0';
				ex = 1;
			}
			else { //bytes[i] == '1' && ex == 1
				sum[i] = '0';
			}
		}
	}

	//Tra ve gia tri QInt
	for (int i = 0; i < QInt::NUM_OF_INT; i++)
		this->data[i] = 0;

	for (int i = sum.length() - 1; i >= 0; i--) {
		if (sum[i] == '1')
			changeBit(127 - i);
	}

	return *this;
}

