// AssessmentOne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Methods.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


int main()
{
	bool DontExitLoop = true;
	while (DontExitLoop)
	{

		//Ask user what they would like to do
		cout << "\nWhat would you like to do?\n";
		cout << "\n0. Change colour theme.";
		cout << "\n1. Take the quiz.";
		cout << "\n2. Sort and search a list of numbers.";
		cout << "\n3. Save a string to a binary file.";
		cout << "\n4. Take the quiz but it uses objects this time.";
		cout << "\n5. Use the calculator.";
		cout << "\n6. Exit the program.\n";

		//Get users answer
		string Input;
		cin >> Input;
		char Selection = Input[0];

		//Use switch statement to do the selected task
		switch (Selection)
		{
		case '0' :
			Methods::Background();
			break;
		case '1':
			Methods::Quiz();
			break;
		case '2':
			Methods::NumbersList();
			break;
		case '3':
			Methods::BinaryFile();
			break;
		case '4':
			Methods::ObjectQuiz();
			break;
		case '5':
			Methods::Calculator();
			break;
		case '6':
			DontExitLoop = false;
			break;
		default:
			break;
		}
	}
	//Must adjust to fit all questions
    return 0;
}

