#include "stdafx.h"
#include "Methods.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include "windows.media.h"
#pragma comment (lib, "winmm.lib")

using namespace std;

Methods::Methods()
{
}


Methods::~Methods()
{
}

class Question
{
private:
	//Variables
	string AskedQuestion;
	string Answer1;
	string Answer2;
	string Answer3;
	string Answer4;
	int CorrectAnswer;
	int GivenAnswer;
	bool AnsweredCorrectly;

public:
	//NullConstructor
	Question()
	{

	}
	//Constructor
	Question(string askedQuestion, string ans1, string ans2, string ans3, string ans4, int correctAns)
	{
		AskedQuestion = askedQuestion;
		Answer1 = ans1;
		Answer2 = ans2;
		Answer3 = ans3;
		Answer4 = ans4;
		CorrectAnswer = correctAns;
		GivenAnswer = 0;
		AnsweredCorrectly = false;
	}

	//Input details from question being answered
	bool QuestionAnswered(int givenAns)
	{
		GivenAnswer = givenAns;
		if (CorrectAnswer == GivenAnswer)
		{
			AnsweredCorrectly = true;
		}
		return AnsweredCorrectly;
	}

	//Getters
	string GetAskedQuestion()
	{
		return AskedQuestion;
	}

	string GetAnswer1()
	{
		return Answer1;
	}
	string GetAnswer2()
	{
		return Answer2;
	}
	string GetAnswer3()
	{
		return Answer3;
	}
	string GetAnswer4()
	{
		return Answer4;
	}

	int GetGivenAnswer()
	{
		return GivenAnswer;
	}

	bool GetAnsweredCorrectly()
	{
		return AnsweredCorrectly;
	}

	int GetCorrectAnswer()
	{
		return CorrectAnswer;
	}
};

void Methods::Quiz()
{
	//Play music
	PlaySound(TEXT("eshop.wav"), NULL,SND_FILENAME | SND_LOOP | SND_ASYNC);
	//Read from file to array

	//Create array [rows][columns]
	string QuestionsArray[9][6];
	//Set filestream
	ifstream QuestionFile("questions.txt");
	//Set string for info to be passed to
	string line;
	//Check if file can be opened
	if (QuestionFile.is_open())
	{
		//Loop through each line
		for (int IndexRow = 0;IndexRow < 9;IndexRow++)
		{
			//Loop through each column
			for (int IndexColumn = 0; IndexColumn < 6; IndexColumn++)
			{
				getline(QuestionFile, line, ';');
				line.erase(remove(line.begin(), line.end(), '\n'), line.end());
				QuestionsArray[IndexRow][IndexColumn] = line;
			}
		}
	}

	//Loop through questions

	//Find number of questions and set value for tracking correct answers
	int NumberOfQuestions = 9;
	int CorrectAnswers = 0;

	//Loop through each question
	for (int index = 0;index < 9;index++)
	{
		//Display the question and the answers
		std::cout << "\nQuestion " + to_string(index + 1) + ": " + QuestionsArray[index][0] + "\n\n";
		for (int answerindex = 0; answerindex < 4;answerindex++)
		{
			std::cout << to_string(answerindex + 1) + ": " + QuestionsArray[index][answerindex + 1] + "\n";
		}

		//Take users answer
		string answer;
		cin >> answer;

		//Check if answer is correct
		if (answer == QuestionsArray[index][5])
		{
			//If correct display correct message
			std::cout << "\nCorrect Answer!";
			//Add to the correct answers number
			CorrectAnswers++;
		}
		else
		{
			//If incorrect sisplay incorrect message
			std::cout << "\nIncorrect Answer! Correct answer was "+QuestionsArray[index][5]+".";
		}
	}

	//Stop music
	PlaySound(NULL, 0, 0);

	//Show final results
	std::cout << "\nYou got " + to_string(CorrectAnswers) + "/" + to_string(NumberOfQuestions) + " questions correct.";
}

void Methods::NumbersList()
{
	//Read numbers from file

	//Create array to put numbers in
	int NumbersArray[10];

	//Set filestream
	ifstream NumbersFile("numbers.txt");

	//Set string for into to be passed through
	string NumberString;
	//Check if file can be opened
	if (NumbersFile.is_open())
	{
		//Loop through each item
		for (int index=0;index<10;index++)
		{
			getline(NumbersFile, NumberString, ';');
			NumbersArray[index] = stoi(NumberString,nullptr,10);
		}
	}
	//Display unsorted list of numbers
	std::cout << "\nUnsorted List\n\n";
	for (int index = 0;index<10;index++)
	{
		std::cout << to_string(NumbersArray[index])+"\n";
	}
	//Sort list of numbers
	SortArray(NumbersArray);

	//Display sorted list of numbers
	std::cout << "\nSorted List\n\n";
	for (int index = 0;index<10;index++)
	{
		std::cout << to_string(NumbersArray[index]) + "\n";
	}

	//Allow user to search for number
	
	int SearchNumber = 0;
	bool ExitLoop = false;
	while (ExitLoop == false)
	{
		//Ask user for number to search for
		std::cout << "\nPlease enter a number to search for.\n";
		cin >> NumberString;

		//Check if string can be converted to int
		if (NumberString.find_first_not_of("1234567890") == string::npos)
		{
			//Convert string to int
			SearchNumber = stoi(NumberString, nullptr, 10);
			ExitLoop = true;
		}
		else
		{
			//Display error message
			std::cout << "\nThat is not a number.";
		}
	}

	//Search for the number in the array using binary search
	int SearchIndex;
	int Min = 0;
	int Max = 9;

	//Start at middle position in array
	SearchIndex = (Min + Max) / 2;

	while ((NumbersArray[SearchIndex] != SearchNumber) && (Min <= Max))
	{
		//Check if selected number is greater than the number searched for
		if (NumbersArray[SearchIndex] > SearchNumber)
		{
			//Set the max search area to under the selected number
			Max = SearchIndex - 1;
		}
		else
		{
			//Set the min search area to over the selected number
			Min = SearchIndex + 1;
		}
		//Reselect the middle position of newly defined search area
		SearchIndex = (Min + Max) / 2;
	}
	//Check if the number was found
	if (Min <= Max)
	{
		//Display the numbers position in the list
		std::cout << "The searched number was No." + to_string(SearchIndex+1) + " in the list.";
	}
	else
	{
		//If the number wasnt found show error message
		std::cout << "Your number could not be found in the list";
	}

}

void Methods::SortArray(int NumberArray[10])
{
	sort(NumberArray,NumberArray+10);
}

void Methods::BinaryFile()
{
	//Ask user for a string to write to the file
	string InputString;
	std::cout << "Please enter the string you want saved to the binary file.\n\n";
	cin >> InputString;

	//Write string to binary file
	fstream BinaryFile("binary.bin", ios::binary | ios::out | ios::in);
	BinaryFile.clear();
	BinaryFile.write(InputString.c_str(), InputString.size());
	BinaryFile.close();
}

void Methods::ObjectQuiz()
{
	//Play music
	PlaySound(TEXT("eshop.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

	//Read from file to question objects

	//Set filestream
	ifstream QuestionFile("questions.txt");
	//Set string for info to be passed to
	string line;
	//Create object array for questions to be added to
	Question QuestionArray[9];
	//Check if file can be opened
	if (QuestionFile.is_open())
	{
		//Loop through each line
		for (int IndexRow = 0;IndexRow < 9;IndexRow++)
		{
			//Create string array for each item to be added to
			string StringArray[6];

			//Loop through each column and add to string array
			for (int IndexColumn = 0; IndexColumn < 6; IndexColumn++)
			{
				getline(QuestionFile, line, ';');
				line.erase(remove(line.begin(), line.end(), '\n'), line.end());
				StringArray[IndexColumn] = line;
			}
			//Create question object to add to object array
			QuestionArray[IndexRow] = Question(StringArray[0], StringArray[1], StringArray[2], StringArray[3], StringArray[4], stoi(StringArray[5], nullptr, 10));
		}
	}

	//Loop through questions

	//Find number of questions
	int NumberOfQuestions = 9;

	//Loop through each question
	for (int index = 0;index < 9;index++)
	{
		//Display the question and the answers
		std::cout << "\nQuestion " + to_string(index + 1) + ": " + QuestionArray[index].GetAskedQuestion() + "\n\n";
		std::cout << "1: " + QuestionArray[index].GetAnswer1() + "\n";
		std::cout << "2: " + QuestionArray[index].GetAnswer2() + "\n";
		std::cout << "3: " + QuestionArray[index].GetAnswer3() + "\n";
		std::cout << "4: " + QuestionArray[index].GetAnswer4() + "\n";

		//Take users answer and check if can be converted to int
		int Answer;
		string AnswerString;

		bool ExitLoop = false;
		while (ExitLoop == false)
		{
			//Check if string can be converted to int
			cin >> AnswerString;
			if (AnswerString.find_first_not_of("1234567890") == string::npos)
			{
				//Convert string to int
				Answer = stoi(AnswerString, nullptr, 10);
				ExitLoop = true;
			}
			else
			{
				//Display error message
				std::cout << "\nThat is not a number.\n";
			}
		}

		//Check if answer is correct
		bool AnswerCorrect = QuestionArray[index].QuestionAnswered(Answer);
		if (AnswerCorrect)
		{
			//If correct display correct message
			std::cout << "\nCorrect Answer!";
		}
		else
		{
			//If incorrect sisplay incorrect message
			std::cout << "\nIncorrect Answer! Correct answer was "+to_string(QuestionArray[index].GetCorrectAnswer())+".";
		}
	}

	//Stop music
	PlaySound(NULL, 0, 0);

	//Find final results
	int CorrectAnswers = 0;
	for (int index = 0;index < 9;index++)
	{
		if (QuestionArray[index].GetAnsweredCorrectly())
		{
			CorrectAnswers++;
		}
	}

	//Show final results
	std::cout << "\nYou got " + to_string(CorrectAnswers) + "/" + to_string(NumberOfQuestions) + " questions correct.";
}

void Methods::Calculator()
{
	//Values
	float Num1;
	float Num2;
	string Input;
	char Selection;
	float Result;
	bool DontExitLoop = true;

	while (DontExitLoop)
	{
		//Ask the user what type of operation they want to do
		cout << "\nWhat would you like to do?\n";
		cout << "\n1. Addition";
		cout << "\n2. Subtraction";
		cout << "\n3. Multiplication";
		cout << "\n4. Division\n";
		cin >> Input;
		Selection = Input[0];

		if (Selection == '1' || Selection == '2' || Selection == '3' || Selection == '4')
		{
			DontExitLoop = false;
		}
		else
		{
			cout << "Please enter one of the given options.";
		}
	}

	//Ask the user for two numbers
	DontExitLoop = true;
	string NumberString;

	//Ask for first number
	while (DontExitLoop)
	{
		cout << "Enter the first number\n";
		cin >> NumberString;
		//Check if string can be converted to double
		if (NumberString.find_first_not_of("1234567890.") == string::npos)
		{
			//Convert string to double
			Num1 = stof(NumberString);
			DontExitLoop = false;
		}
	}

	//Ask for second number
	DontExitLoop = true;
	while (DontExitLoop)
	{
		cout << "Enter the second number\n";
		cin >> NumberString;
		//Check if string can be converted to double
		if (NumberString.find_first_not_of("1234567890.") == string::npos)
		{
			//Convert string to double
			Num2 = stof(NumberString);
			DontExitLoop = false;
		}
	}

	//Use switch statemnt to do the appropriate operation
	switch (Selection)
	{
	case '1':
		Result = Num1 + Num2;
		cout << Result;
		break;
	case '2':
		Result = Num1 - Num2;
		cout << Result;
		break;
	case '3':
		Result = Num1 * Num2;
		cout << Result;
		break;
	case '4':
		Result = Num1 / Num2;
		cout << Result;
		break;
	default:
		cout << "Oops something has gone wrong.";
	}

}

void Methods::Background()
{
	string Input;
	char Selection;
	bool DontExitLoop = true;
	while (DontExitLoop)
	{
		//Ask the user which theme they want
		cout << "\nWhat theme would you like\n";
		cout << "\n1. Default.";
		cout << "\n2. White.";
		cout << "\n3. Hotdog Stand.";
		cout << "\n4. A E S T H E T I C\n";
		cin >> Input;
		Selection = Input[0];

		//Apply the theme using a switch statement
		switch (Selection)
		{
		case '1':
			system("color 0F");
			DontExitLoop = false;
			break;
		case '2':
			system("color F0");
			DontExitLoop = false;
			break;
		case '3':
			system("color 4E");
			DontExitLoop = false;
			break;
		case '4':
			system("color BD");
			DontExitLoop = false;
			break;
		default:
			cout << "Please enter one of the given options.";
			break;

		}
	}
	

}