#include "reader.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

// This function returns a percentage of similarity for 2 strings base on a simple algorithm.
float compareStrings(string word, string compareTo) {
	float percentage = 0;

	if (size(word) <= size(compareTo)) {
		for (size_t i = 0; i < size(word); i++) {
			if (word[i] == compareTo[i]) {
				percentage++;
			}
		}

		percentage = (percentage * 100) / size(compareTo);

	}
	else {
		for (size_t i = 0; i < size(compareTo); i++) {
			if (word[i] == compareTo[i]) {
				percentage++;
			}
		}

		percentage = (percentage * 100) / size(word);

	}

	return percentage;

}

reader::reader() 
{
	// Init values.
	_errorFlag = false;

	// Then we make some usefull variable...
	string line;
	string ident, expression;
	char buffer[20];
	ifstream myFile ("read.txt");
	ofstream outFile;
	int lineCount = 0;
	size_t length;
	bool setDec = false;
	bool KeyworDecl = false;
	bool TokenDecl = false;

	// Validating the file open.
	if (myFile.is_open()) {
		// Reading the file line by line
		while (getline(myFile, line)) {
			// we read a line.
			lineCount++;
			ident = "";
			expression = "";

			// First check for comments...
			length = line.find("(.");
			if (length != string::npos) {
				// If it find a comment, then ignore all lines..
				do
				{
					getline(myFile, line);
					length = line.find(".)");
				// Until you find the end of comment line.
				} while (length != string::npos);
			}

			// Then check for blank lines...
			else if (line.empty() || line.find_first_not_of(' ') == std::string::npos) {
				// This is an empy line so we don't count it nor process it.
			}

			// The first line must be "COMPILER [name]"
			else if (lineCount == 1) {
				// First we get the COMPILER word.
				length = line.copy(buffer, 8, 0);
				for (size_t i = 0; i < length; i++) {
					ident += line[i];
				}
				// Then we get the [name].
				for (size_t i = length + 1; i < size(line); i++) {
					expression += line[i];
				}
				// Now we have to check if they are both correct.
				if (compareStrings(ident, "COMPILER") == 100) {
					outFile.open(expression + ".txt");
				}
				else if (compareStrings(ident, "COMPILER") >= 60) {
					cout << "WARNING: You might wanna check your syntax on line: " << lineCount << endl;
					outFile.open(expression + ".txt");
				}
				else {
					cout << "ERROR: 'COOMPILER' word not found in line: " << lineCount << endl;
					_errorFlag = true;
				}

				lineCount++;
			}

			// Then we have to check for the Scanner Specifications.
			// Starting with CHARACTERS...
			else if (compareStrings(line, "CHARACTERS") == 100 ) {
				// Now that we find characters we need to get all the SetDecl.
				setDec = true;
				KeyworDecl = false;
				TokenDecl = false;
				outFile << "CHARACTERS\n";
				lineCount++;
			}
			else if (compareStrings(line, "CHARACTERS") >= 60) {
				cout << "WARNING: You might wanna check your syntax on line: " << lineCount << endl;
				setDec = true;
				KeyworDecl = false;
				TokenDecl = false;
				outFile << "CHARACTERS\n";
				lineCount++;
			}
			// Then KEYWORDS...
			else if (compareStrings(line, "KEYWORDS") == 100) {
				// Now that we find keywords we need to get all the KeyworDecl.
				setDec = false;
				KeyworDecl = true;
				TokenDecl = false;
				outFile << "KEYWORDS\n";
				lineCount++;
			}
			else if (compareStrings(line, "KEYWORDS") >= 60) {
				cout << "WARNING: You might wanna check your syntax on line: " << lineCount << endl;
				setDec = false;
				KeyworDecl = true;
				TokenDecl = false;
				outFile << "KEYWORDS\n";
				lineCount++;
			}
			// Last the TOKENS...
			else if (compareStrings(line, "TOKENS") == 100) {
				// Now that we find tokens we need to get all the TokenDecl.
				setDec = false;
				KeyworDecl = false;
				TokenDecl = true;
				outFile << "TOKENS\n";
				lineCount++;
			}
			else if (compareStrings(line, "TOKENS") >= 60) {
				cout << "WARNING: You might wanna check your syntax on line: " << lineCount << endl;
				setDec = false;
				KeyworDecl = false;
				TokenDecl = true;
				outFile << "TOKENS\n";
				lineCount++;
			} 
			// Now we check if we should check for Character, KeyWord or Token.
			// If set declaration is true, then we must check for characters.
			else if (setDec) {

			}
			// If keword declaration is true, then we must check for keywords.
			else if (KeyworDecl) {

			}
			// If token declaration is true, then we must check for tokens.
			else if (TokenDecl) {

			}
			// If non of the above then it's an error in the line.
			else {
				lineCount++;
				cout << "WARNING: You might wanna check your syntax on line: " << lineCount << endl;
			}

			// Error check...
			if (_errorFlag) {
				break;
			}

		}
	}

}