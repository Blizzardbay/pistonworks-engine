#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono_literals;

//strings
std::string sAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string sHex = "ABCDEF";
std::string sV1 = "T........";
std::string sV2 = ".T.......";
std::string sV3 = "..T......";
std::string sV4 = "...T.....";
std::string sV5 = "....T....";
std::string sV6 = ".....T...";
std::string sV7 = "......T..";
std::string sV8 = ".......T.";
std::string sV9 = "........T";
std::string sV10 = ".......T.";
std::string sV11 = "......T..";
std::string sV12 = ".....T...";
std::string sV13 = "....T....";
std::string sV14 = "...T.....";
std::string sV15 = "..T......";
std::string sV16 = ".T.......";
std::string sV17 = "T........";
//vars
//prototypes
void NumChecker(int b);
void numQuartet();
void AlphabetletterChecker(int RandLetter);
void HexletterChecker(int RandLetter);
void v16Numline();
int animString(int a);
//main
int main()
{
	int NumVar1 = 0;
	int NumVar2 = 0;
	srand(time(0));
	for (int x = 1; x <= 9999999; x++) {
		NumVar1 = NumVar1 + 1;
		NumVar2 = NumVar2 + 1;
		NumChecker(NumVar2);
		for (int i = 1; i <= 8; i++) {
			std::cout << ' ';
			numQuartet();
		}
		std::cout << ' ';
		for (int i = 1; i <= 16; i++) {
			v16Numline();
		}
		std::cout << ' ';
		NumVar1 = animString(NumVar1);
		std::cout << std::endl;
		

		std::this_thread::sleep_for(50ms);
	}
}
//functions
int animString(int a) {
	if (a == 1) {
		std::cout << sV1;
	}
	else if (a == 2) {
		std::cout << sV2;
	}
	else if (a == 3) {
		std::cout << sV3;
	}
	else if (a == 4) {
		std::cout << sV4;
	}
	else if (a == 5) {
		std::cout << sV5;
	}
	else if (a == 6) {
		std::cout << sV6;
	}
	else if (a == 7) {
		std::cout << sV7;
	}
	else if (a == 8) {
		std::cout << sV8;
	}
	else if (a == 9) {
		std::cout << sV9;
	}
	else if (a == 10) {
		std::cout << sV10;
	}
	else if (a == 11) {
		std::cout << sV11;
	}
	else if (a == 12) {
		std::cout << sV12;
	}
	else if (a == 13) {
		std::cout << sV13;
	}
	else if (a == 14) {
		std::cout << sV14;
	}
	else if (a == 15) {
		std::cout << sV15;
	}
	else if (a == 16) {
		std::cout << sV16;
	}
	else if (a == 17) {
		a = a - 16;
		std::cout << sV17;
	}
	else {}
	return(a);
}
void numQuartet() {
	int RandNum;
	for (int i = 1; i <= 4; i++) {
		 RandNum = rand() % 9 + 1;
		if (RandNum >= 6) {
			RandNum = RandNum - 6;
			std::cout << RandNum;
		}
		else {
			HexletterChecker(RandNum);
		}
	}
}
void AlphabetletterChecker(int RandLetter) {
	RandLetter = RandLetter - 1;
	std::cout << sAlphabet.at(RandLetter);
}
void HexletterChecker(int RandLetter) {
	std::cout << sHex.at(RandLetter);
}
void v16Numline() {
	int RandNumLine = 0;
	RandNumLine = rand() % 72 + 1;
	if ((RandNumLine > 26) && (RandNumLine < 37))
	{
		RandNumLine = RandNumLine - 27;
		std::cout << RandNumLine;
	}
	else if (RandNumLine < 27) {
		AlphabetletterChecker(RandNumLine);
		}
		else if (RandNumLine > 36) {
				std::cout << ".";
			}
			else {}
}
void NumChecker(int b) {
	printf("%07d : ", b);
}
