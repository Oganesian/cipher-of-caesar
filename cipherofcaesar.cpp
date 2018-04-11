#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

char encrypt(char, short, bool);
char decrypt(char, short, bool);
char(*func)(char, short, bool);

int main()
{
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string sourceFilePath;
	char* outputFileName;
	unsigned short offset;
	std::string sourceText;
	int mode;

	do {
		std::cout << "Type 1 if you want to encrypt\n";
		std::cout << "And 2 if you want to decrypt\n";
		std::cin >> mode;
		if (mode < 1 || mode > 2)
			std::cout << "Incorrect mode\n";
		else
			break;
	} while (true);
	
	if (mode == 1) {
		func = &encrypt;
		outputFileName = "encrypted.txt";
	}
	else {
		func = &decrypt;
		outputFileName = "decrypted.txt";
	}
		

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
			sourceText[i] = func(sourceText[i], offset, isCharInUpperCase);
		}
	}
	
	std::ofstream outputFile(outputFileName);
	outputFile << sourceText;

	sourceFile.close();
	outputFile.close();

	system("pause");
    return 0;
}

char encrypt(char old, short offset, bool isCharInUpperCase) {
	if (isCharInUpperCase && (old + offset) > 90) return (old + offset - 26);
	else if (!isCharInUpperCase && (old + offset) > 122) return (old + offset - 26);
	return (old + offset);
}

char decrypt(char old, short offset, bool isCharInUpperCase) {
	if (isCharInUpperCase && (old - offset) < 65) return (old - offset + 26);
	else if (!isCharInUpperCase && (old - offset) < 97) return (old - offset + 26);
	return (old - offset);
}