#include "ManipulationModules.h"
#include "QInt.h"
#include "QFloat.h"
#include <iostream>
#include <vector>

using namespace std;

void PrepareQInt(QInt& target, string data, int base) {
	switch (base)
	{
	case 2:
		target.BinToQInt(data);
		break;
	case 10:
		target.DecToQInt(data);
		break;
	case 16:
		target.HexToQInt(data);
		break;
	default:
		throw "Invalid Base.";
		break;
	}
}


//Thuc hien phep tinh voi du lieu data1 va data2
void DoCalculate(QInt data1, string operation, QInt data2, ofstream& output) {
	QInt result;
	// Chon phep tinh tuong ung voi operation
	{
		if (operation == "+")
		{
			result = data1 + data2;
		}
		else if (operation == "-")
		{
			result = data1 - data2;
		}
		else if (operation == "*")
		{
			result = data1 * data2;
		}
		else if (operation == "/")
		{
			result = data1 / data2;
		}
		else if (operation == "&")
		{
			result = data1 & data2;
		}
		else if (operation == "|")
		{
			result = data1 | data2;
		}
		else if (operation == "^")
		{
			result = data1 ^ data2;
		}
		else if (operation == ">>")
		{
			int n = data2.QInt::data[3];
			result = data1 >> n;
		}
		else if (operation == "<<")
		{
			int n = data2.QInt::data[3];
			result = data1 << n;
		}
	}

	output << result << endl;
	cout << " = " << result << endl;
}

void DoCalculate(QFloat data1, string operation, QFloat data2, ofstream& output) {
	QFloat result;
	// Chon phep tinh tuong ung voi operation
	{
		if (operation == "+")
		{
			result = data1 + data2;
		}
		else if (operation == "-")
		{
			result = data1 - data2;
		}
		else if (operation == "*")
		{
			result = data1 * data2;
		}
		else if (operation == "/")
		{
			result = data1 / data2;
		}
	}

	output << result << endl;
	cout << " = " << result << endl;
}

//Thuc hien chuyen he so tu co so nay sang co so khac voi du lieu la string
void TransferBase(int fromBase, int toBase, string data, ofstream& output) {
	QInt tmpQInt;
	PrepareQInt(tmpQInt, data, fromBase);
	string result;
	switch (toBase)
	{
	case 2:
		result = tmpQInt.toBinary();
		break;
	case 10:
		output << tmpQInt << endl;
		return;
		break;
	case 16:
		result = tmpQInt.toHexa();
		break;
	default:
		throw "Invalid Base.";
		break;
	}
	output << result << endl;
}
 

//Giai mot hang trong file
void SolveALine(ifstream& input, ofstream& output) {
	string aLine;
	//Doc nguyen string
	getline(input, aLine);

	//Xoa dau cach o dau, o cuoi, dau cach doi
	int fukSpaces = -1;
	while (aLine[fukSpaces+1] == ' ')
	{
		fukSpaces++;
	}
	if (fukSpaces > -1) {
		aLine.erase(0, fukSpaces+1);
	}
	fukSpaces = aLine.length();
	while (aLine[fukSpaces - 1] == ' ')
	{
		fukSpaces--;
	}
	if (fukSpaces < aLine.length()) {
		aLine.erase(fukSpaces, aLine.length() - fukSpaces);
	}
	for (unsigned int i = 1; i < aLine.length() - 1; i++)
	{
		while (aLine[i] == ' ' && aLine[i + 1] == ' ')
		{
			aLine.erase(i + 1, 1);
		}
	}

	//Luu lai vi tri cac dau cach trong string
	vector<int> spacePos;
	for (unsigned int i = 0; i < aLine.length(); i++)
	{
		if (aLine[i] == ' ')
		{
			spacePos.push_back(i);
		}
	}
	if (spacePos.size() < 2 || spacePos.size() > 3)
	{
		throw "Invalid data count.";
	}

	// 2 dau cach -> doi he co so

	if (spacePos.size() == 2)
	{
		int fromBase, toBase;
		fromBase = stoi(aLine.substr(0, spacePos[0]));
		toBase = stoi(aLine.substr(spacePos[0] + 1, spacePos[1] - spacePos[0] - 1));
		string data = aLine.substr(spacePos[1] + 1, aLine.size() - spacePos[1] - 1);
		cout << fromBase << " " << toBase << " " << data << endl;
		TransferBase(fromBase, toBase, data, output);
	}

	// 3 dau cach -> phep tinh

	if (spacePos.size() == 3)
	{
		//Doc vao he so phep tinh. "F" la floating point, "2F" la bieu dien nhi phan cua dau cham dong
		bool isQFloat = false;
		string baseName = aLine.substr(0, spacePos[0]);
		int base;
		if (baseName == "F" || baseName == "f" ||
			baseName == "2F" || baseName == "2f")
		{
			isQFloat = true;
		}
		else
		{
			base = stoi(aLine.substr(0, spacePos[0]));
		}

		//Doc vao du lieu cua 2 so va phep tinh
		string data1 = aLine.substr(spacePos[0] + 1, spacePos[1] - spacePos[0] - 1);
		//operation sign
		string operat = aLine.substr(spacePos[1] + 1, spacePos[2] - spacePos[1] - 1);
		//the second operant
		string data2 = aLine.substr(spacePos[2] + 1, aLine.size() - spacePos[2] - 1);

		//Check the reading
		cout << base << " " << data1 << " " << operat << " " << data2;

		//Thuc hien phep tinh
		if (isQFloat)
		{
			//Chuan bi 2 so QFloat de truyen vao
			QFloat float1, float2;
			if (baseName[0] == '2')
			{
				float1.scanBin(data1);
				float2.scanBin(data2);
			}
			else
			{
				float1.scanDec(data1);
				float2.scanDec(data2);
			}
			DoCalculate(float1, operat, float2, output);
		}
		else{
			//Chuan bi 2 so QInt de truyen vao
			QInt int1, int2;
			PrepareQInt(int1, data1, base);
			PrepareQInt(int2, data2, base);
			DoCalculate(int1, operat, int2, output);
		}
	}
} 

void solveAFile(string inPath, string outPath) {
	ifstream input;
	input.open(inPath.data());
	ofstream output;
	output.open(outPath.data());
	while (!input.eof())
	{
		SolveALine(input, output);
	}
}