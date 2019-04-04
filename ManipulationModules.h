#include <fstream>
#include <string>

#define SHOW_PROGRAM_PARAMETERS cout << "<ProgramName> <input File> <output File> <type>." << endl;

bool CheckFileExistence(std::string fPath);
bool CheckArguments(int argc, char **argv);
void solveAFile(std::string, std::string, int type);

void ExecuteScreen();