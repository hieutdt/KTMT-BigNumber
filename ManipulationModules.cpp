#include "ManipulationModules.h"
#include "QInt.h"
#include "QFloat.h"
#include <iostream>
#include <vector>

#define OUTBASE_BINA 2 
#define OUTBASE_DECI 10
#define OUTBASE_HEXA 16

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
void DoCalculate(QInt data1, string operation, QInt data2, ofstream& output, int outputBase) {
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
			try
			{
				result = data1 / data2;

			}
			catch (char * ex)
			{
				output << ex << endl;
				cout << " = " << ex << endl;
				return;
			}
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

	if (outputBase == OUTBASE_BINA)
	{
		string finalRes = result.toBinary();
		int lastZero = 0;
		while (finalRes[lastZero] == '0')
		{
			lastZero++;
		}
		if (lastZero > 0) {
			finalRes.erase(0, lastZero);
		}
		if (finalRes.length() == 0) {
			finalRes = "0";
		}
		output << finalRes << endl;
		cout << " = " << finalRes << endl;
		return;
	}
	if (outputBase == OUTBASE_DECI)
	{
		output << result << endl;
		cout << " = " << result << endl;
		return;
	}
	if (outputBase == OUTBASE_HEXA)
	{
		output << result.toHexa() << endl;
		cout << " = " << result.toHexa() << endl;
		return;
	}
}

void DoCalculate(QFloat data1, string operation, QFloat data2, ofstream& output, int outputBase) {
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
	if (outputBase == OUTBASE_BINA)
	{
		output << result.toBinary() << endl;
		cout << " = " << result.toBinary() << endl;
	}
	else
	{
		output << result << endl;
		cout << " = " << result << endl;
	}
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
		result = tmpQInt.toString();
		break;
	case 16:
		result = tmpQInt.toHexa();
		break;
	default:
		throw "Invalid Base.";
		break;
	}
	output << result << endl;
	cout << " = " << result << endl;
}
 

//Giai mot hang trong file
void SolveIntLine(ifstream& input, ofstream& output) {
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
		cout << fromBase << " " << toBase << " " << data;
		TransferBase(fromBase, toBase, data, output);
	}

	// 3 dau cach -> phep tinh

	if (spacePos.size() == 3)
	{
		int base = stoi(aLine.substr(0, spacePos[0]));

		//Doc vao du lieu cua 2 so va phep tinh
		string data1 = aLine.substr(spacePos[0] + 1, spacePos[1] - spacePos[0] - 1);
		//operation sign
		string operat = aLine.substr(spacePos[1] + 1, spacePos[2] - spacePos[1] - 1);
		//the second operant
		string data2 = aLine.substr(spacePos[2] + 1, aLine.size() - spacePos[2] - 1);

		//Check the reading
		cout << base << " " << data1 << " " << operat << " " << data2;

		//Chuan bi 2 so QInt de truyen vao
		QInt int1, int2;
		PrepareQInt(int1, data1, base);
		PrepareQInt(int2, data2, base);
		DoCalculate(int1, operat, int2, output, base);
	}
} 

void SolveFloatLine(ifstream& input, ofstream& output) {
	string aLine;
	//Doc nguyen string
	getline(input, aLine);

	//Xoa dau cach o dau, o cuoi, dau cach doi
	int fukSpaces = -1;
	while (aLine[fukSpaces + 1] == ' ')
	{
		fukSpaces++;
	}
	if (fukSpaces > -1) {
		aLine.erase(0, fukSpaces + 1);
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

	// 3 dau cach -> phep tinh

	if (spacePos.size() == 3)
	{
		string base = aLine.substr(0, spacePos[0]);
		bool isBinFloat = false;
		if (base == "2F" || base == "2f")
		{
			isBinFloat = true;
		}
		else
		{
			if (base != "F" && base != "f")
			{
				cout << "Unknown Base." << endl;
				output << "Unknown Base." << endl;
			}

		}

		//Doc vao du lieu cua 2 so va phep tinh
		string data1 = aLine.substr(spacePos[0] + 1, spacePos[1] - spacePos[0] - 1);
		//operation sign
		string operat = aLine.substr(spacePos[1] + 1, spacePos[2] - spacePos[1] - 1);
		//the second operant
		string data2 = aLine.substr(spacePos[2] + 1, aLine.size() - spacePos[2] - 1);

		// Show the operation
		cout << base << " " << data1 << " " << operat << " " << data2;

		QFloat float1, float2;
		int outBase = OUTBASE_DECI;
		//Thuc hien phep tinh
		if (isBinFloat)
		{
			float1.scanBin(data1);
			float2.scanBin(data2);
			outBase = OUTBASE_BINA;
		}
		else {
			float1.scanDec(data1);
			float2.scanDec(data2);
		}
		DoCalculate(float1, operat, float2, output,outBase);
	}
}

void solveAFile(string inPath, string outPath, int type) {
	ifstream input;
	input.open(inPath.data());
	ofstream output;
	output.open(outPath.data());
	if (type == 1) {
		while (!input.eof())
		{
			SolveIntLine(input, output);

		}
	}
	else
	{
		while (!input.eof())
		{
			SolveFloatLine(input, output);
		}
	}
}

bool CheckFileExistence(string fPath) {
	ifstream inp(fPath);
	if (!inp)
	{
		SHOW_PROGRAM_PARAMETERS
			cout << "Input file not existing." << endl;
		return false;
	}
}

bool CheckArguments(int argc, char ** argv) {
	if (argc == 1) {
		return true;
	}
	if (argc != 4) {
		cout << "Parameter count is not valid." << endl;
		SHOW_PROGRAM_PARAMETERS
		return false;
	}
	if (!CheckFileExistence(argv[1]))
	{
		return false;
	}
	int typeStrLen = strlen(argv[3]);
	if ((argv[3][0] != '1' && argv[3][0] != '2')||(typeStrLen != 1))
	{
		SHOW_PROGRAM_PARAMETERS
		cout << "<type> must be 1 or 2." << endl;
	}
	return true;
}


void ExecuteScreen() {
	int choice = 0, type;
	string inPath, outPath;
	string userInput;
	ofstream tmpOut;
	char c;
	while (choice != 4)
	{
		cout << " --- Bang chon ---" << endl;
		cout << "1. Phep tinh voi so nguyen lon" << endl;
		cout << "2. Phep tinh voi so thuc do chinh xac cao" << endl;
		cout << "3. Doc Du lieu dau vao tu tap tin" << endl;
		cout << "4. THOAT" << endl;
		cout << " > Lua chon (1->4): ";
		cin >> choice;
		cin.clear();
		cin.ignore(10000, '\n');
		switch (choice)
		{
		case 1:
		case 2:
			inPath = "tempInput.txt";
			outPath = "tempOutput.txt";
			cout << "Phep tinh:" << endl;
			cout << ">> ";
			getline(cin, userInput);
			tmpOut.open(inPath);
			tmpOut << userInput;
			tmpOut.close();
			solveAFile(inPath, outPath, choice);
			break;
		case 3:
			cout << "Input file: ";
			std::getline(cin, inPath);
			while (!CheckFileExistence(inPath))
			{
				cout << "Input file: ";
				std::getline(cin, inPath);
			}
			cout << "Output file: ";
			std::getline(cin, outPath);
			cout << "Type (1-Int, 2-Float): ";
			cin >> type;
			while (type != 1 && type != 2)
			{
				cout << "Type (1-Int, 2-Float): ";
				cin >> type;
			}
			solveAFile(inPath, outPath, type);
			break;
		case 4:
			break;
		default:
			cout << endl << "/!\\ LUA CHON TU 1 DEN 4" << endl << endl;
			break;
		}
	}
}