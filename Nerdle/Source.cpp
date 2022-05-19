#include <iostream>
#include <string>
#include <locale>
#include <array>
#include <vector>
#include "tinyexpr-master/tinyexpr.h"

char genOperator() {
	switch (rand() % 4) {
	case(0):
		return '+';
	case(1):
		return '-';
	case(2):
		return'*';
	case(3):
		return'/';
	default:
		std::cout << "Error: genOperator Function made a number out of bounds" << std::endl;
		return'+';
	}
}

char* generateEquation() {
	static char myEq[8];
	//srand(rand());
	myEq[0] = char(rand() % 9 + 49);
	for (int i = 1; i < 8; i++) {
		myEq[i] = char(rand() % 10 + 48); //48 is ascii code to get to the numbers
	}
	int equalsSpot = rand() % 3 + 4;
	myEq[equalsSpot] = '=';
	myEq[7] = '\0';

	//need to add operators now, nums and = sign working as intended
	int quant;
	if (equalsSpot == 4) { // checks to make sure the number of signs works correctly
		quant = 1;
	}
	else {
		quant = rand() % 2 + 1;
		myEq[equalsSpot + 1] = char(rand() % 9 + 49);
	}
	//std::cout << "quant = " << quant << std::endl;

	//Just missing the case for quant == 2 and equalsSpot == 6
	if (quant == 1) {
		int tempPos = rand() % (equalsSpot - 2) + 1;
		myEq[tempPos] = genOperator();
		myEq[tempPos+1] = char(rand() % 9 + 49);
	}
	else if (equalsSpot == 5) {
		myEq[1] = genOperator();
		myEq[2] = char(rand() % 9 + 49);
		myEq[3] = genOperator();
		myEq[4] = char(rand() % 9 + 49);
	}
	else {
		quant = rand() % 2 + 1; //reusing quant here to keep track of where the first operator is since it isnt needed anymore
		myEq[quant] = genOperator();
		myEq[quant+1] = char(rand() % 9 + 49);
		if (quant == 2) {
			myEq[4] = genOperator();
			myEq[5] = char(rand() % 9 + 49);
		}
		else {
			int tempPos = rand() % 2 + 3;
			myEq[tempPos] = genOperator();
			myEq[tempPos + 1] = char(rand() % 9 + 49);

		}
		
	}


	return myEq;
}

int calcExpression(char(&operations)[3], int(&terms)[3]) {
	int num = 0;
	
	std::vector<char> ops;
	std::vector<int> ters;
	for (int i = 2; i >= 0; i--) {
		ops.push_back(operations[i]);
		ters.push_back(terms[i]);
	}
	//std::cout << "step one" << std::endl;

	for (int i = ops.size()-1; i >= 0; i--) {
		std::cout << ops.at(i) << ters.at(i) << " ";
	}
	std::cout << std::endl;


	int j = ops.size();
	for (int i = ops.size()-1; i >= 0; i--) {
		//std::cout << "Error -1" << i << std::endl;
		if (ops.at(i) == '*') {
			std::cout << "Error 0: " << std::endl;
			ters.at(i) *= ters.at(i+1);
			ters.at(i + 1) = 0;
			ops.at(i + 1) = 0;
			/*ters.erase(ters.begin() + i + 1);
			ops.erase (ops.begin()+i+1);*/
			//std::cout << "Error 1" << std::endl;
		}
		if (ops.at(i) == '/' && ters.at(i) == 0) return -1;
		if (ops.at(i) == '/') {
			//std::cout << "Error 2" << std::endl;
			if (ters.at(i + 1) % ters.at(i) != 0) return -1;
			ters.at(i) = ters.at(i + 1) / ters.at(i);
			ters.at(i + 1) = 0;
			ops.at(i + 1) = 0;
			/*ters.erase(ters.begin() + i + 1);
			ops.erase(ops.begin() + i+1);*/
			//std::cout << "Error 3" << std::endl;
		}
	}
	//std::cout << "step two" << std::endl;
	std::cout << "Simplified Equation: ";
	for (int i = ters.size()-1; i >= 0; i--) {
		std::cout << ops.at(i) << ters.at(i)<< " ";
		if (ops.at(i) == '-') num -= ters.at(i);
		else num += ters.at(i);
	}
	std::cout << std::endl;
	return num;

	
}

bool isValidEquation(char* thing) { //does not work at all, dw about it for now
	//char thing[8];
	double calc = 0;
	int goal = 0;
	bool helper = false;
	//int equalsPos = 8;
	char stringExpression[8];
	for (int i = 0; i < 8; i++) {
		if (thing[i] == '\0') break; //dog tier debugging
		if (helper) {
			goal *= 10;
			goal += (int)thing[i] - '0';
			//std::cout << thing[i] << std::endl;
		}
		if (thing[i] == '=') {
			helper = true;
			//equalsPos = i;
			stringExpression[i] = '\0';
			//std::cout << "equals at: " << i << std::endl;
		}
		if (!helper) {
			stringExpression[i] = thing[i];
		}
	}
	//std::cout << goal << std::endl;
	calc = te_interp(stringExpression, 0);
	


	/*char operations[3];
	int terms[3];
	operations[2] = '+';
	terms[2] = 0;
	int termNumber = 0;
	
	for (int i = 0; i< equalsPos; i++) {
		char mathOperator;
		if (i == 0) mathOperator = '+';
		else mathOperator = thing[i];
		if (i != 0) i++;
		int currentNum = 0;
		//std::cout << currentNum << std::endl;
		
		while (isdigit(thing[i])) {
			currentNum *= 10;
			currentNum += (int)thing[i] - '0';
			i++;
		}

		if (mathOperator != '=') {
			operations[termNumber] = mathOperator;
			terms[termNumber] = currentNum;
			termNumber++;
		}

	}
	calc = calcExpression(operations, terms);*/
	std::cout << "my equation: " << calc << '=' << goal << std::endl;
	if (calc - (int)calc != 0) return false;
	return calc == goal;
}

int main() {
	//IT WORKS
	srand(time(NULL));
	std::cout << "Generating equation, please wait" << std::endl;
	char* equation;
	equation = generateEquation();

	while (isValidEquation(equation) == false) {
		for (int i = 0; i < 9; i++) {
			std::cout << equation[i];
		}
		equation = generateEquation();
		std::cout << std::endl << std::endl;
	}
	
	for (int i = 0; i < 9; i++) {
		std::cout << equation[i];
	}
	std::cout << std::endl;


	return 1;
}




/*Nerdle in c++

Generates equation
-= sign 1 / 3 chance
- rand from 0 - 13, 0 - 9 if no operator
-checks for valid equation

Takes in equation
- Checks for valid equation

Checking for valid equation
- find next non - number character to calc 1st side
- use while loop for this

Generate feedback
- Store input and equation as strings
- Check if the exact characters match first
- Check for wrong spot next
- Initial feedback is all wrong, modify once answers found

Limiting options
- Display availible characters after all responses*/
