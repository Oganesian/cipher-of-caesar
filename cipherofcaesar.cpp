#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

char getNewChar(char, short, bool);

int main()
{
	std::string alphabet = "ABCDEFGHIKLMNOPQRSTVXYZ";
	std::string sourceFilePath;
	unsigned short offset;
	std::string sourceText;

	std::cout << "Enter the path to the source file: ";
	std::cin >> sourceFilePath;
	do {
		std::cout << "Enter the offset(1 - 25): ";
		std::cin >> offset;
	} while (offset < 1 || offset > 25);

	std::ifstream sourceFile(sourceFilePath.c_str());
	std::getline(sourceFile, sourceText, '\0');

	for (unsigned i = 0; i < sourceText.length(); i++) {
		int index = alphabet.find(toupper(sourceText[i]));
		bool isCharInUpperCase = false;
		if (index != -1) {
			if (sourceText[i] >= 65 && sourceText[i] <= 90)
				isCharInUpperCase = true;
			sourceText[i] = getNewChar(sourceText[i], offset, isCharInUpperCase);
		}
	}
	
	std::ofstream outputFile("output.txt");
	outputFile << sourceText;

	sourceFile.close();
	outputFile.close();

	system("pause");
    return 0;
}

char getNewChar(char old, short offset, bool isCharInUpperCase) {
	if (isCharInUpperCase && (old + offset) > 90) return old + offset - 26;
	else if (!isCharInUpperCase && (old + offset) > 122) return old + offset - 26;
	return old + offset;
}
