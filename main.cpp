#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "quiz.h"

using namespace std;

unordered_map<int, vector<string> > prompt_for_question(const std::string &questionType) {

	int numOfQuestion;
	std::unordered_map<int, vector<string> > question;

	//Ask for number of questions
	cout << "How many " << questionType << " questions would you like to have in your quiz?\n";
	cin >> numOfQuestion;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	
	for (int i = 1; i <= numOfQuestion; i++) {
		cout << "For question " << i << " (" << questionType << ")\n";
		
		//Multiple Choice Questions
		if (questionType == "Multiple Choice") {

			//Ask for question
			cout << "What is the question?\n";
			string temp;
			getline(cin, temp);
			question[i].push_back(temp);
			
			//Ask for num of answer choice
			cout << "How many answer choices will there be for that question?\n";
			int answerNum;
			cin >> answerNum;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			//Store each answer into the vector
			string tempAns;
			for (int j = 1; j <= answerNum; j++) {
				cout << "What will be answer choice " << j << " to that question?\n";
				getline(cin, tempAns);
				question[i].push_back(tempAns);
			}
		}
		else if(questionType == "Short Answer") {
			//Ask for question
			cout << "What is the question?\n";
			string temp;
			getline(cin, temp);
			question[i].push_back(temp);

			//Ask for num of lines
			cout << "How many lines of blank space should we leave for that question?\n";
			string lineNum;
			cin >> lineNum;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			question[i].push_back(lineNum);
		}
		else if(questionType == "Mix & Match") {
			//Ask for question
			cout << "What is the question?\n";
			string temp;
			getline(cin, temp);
			question[i].push_back(temp);

			//Ask for num of lines
			cout << "What is the correct answer for that question?\n";
			string tempAns;
			getline(cin, tempAns);
			question[i].push_back(tempAns);
		}

	}
	return question;
}

int main(){
	std::string userInput = "";
	bool MC = true, SA = true, MM = true;
	cout << "Hello user!\nWelcome to the mini quiz generator.\nTo get started, what types of questions will be in your test?\n";
	cout << "1. Multiple Choice Questions\n2. Short Answer Questions\n3. Mix & Match Questions.\n";
	cout << "Simply type the number next to the Type of questions (123 would include all three types)\n";
	cin >> userInput;

	if (userInput.find("1") == string::npos) MC = false;
	if (userInput.find("2") == string::npos) SA = false;
	if (userInput.find("3") == string::npos) MM = false;
	
	cout << "\nThank you! We will be generating a quiz with ";
	std::string tempout = "";

	if (MC == true && SA == true && MM == true) {
		tempout += "\nMultiple Choice, Short Answer and Mix & Match ";
	}
	else {
		
		if (MC) tempout += "\nMultiple Choice and ";
		if (SA) tempout += "\nShort Answer and ";
		if (MM) tempout += "\nMix & Match and ";
		tempout.erase(tempout.length() - 5, 4);
		
	}
	cout << tempout << "questions!\n";


	std::unordered_map<int, vector<string> > MCMap;
	std::unordered_map<int, vector<string> > SAMap;
	std::unordered_map<int, vector<string> > MMMap;
	if (MC == true) MCMap = prompt_for_question("Multiple Choice");
	if (SA == true) SAMap = prompt_for_question("Short Answer");
	if (MM == true) MMMap = prompt_for_question("Mix & Match");



	std::vector<std::unordered_map<int, std::vector<std::string> > > mapList;

    if (MC == true) {
        mapList.push_back(MCMap);
    }

    if (SA == true) {
        mapList.push_back(SAMap);
    }

    if (MM == true) {
        mapList.push_back(MMMap);
    }

    Quiz quiz(mapList, MC, SA, MM);

    std::ofstream out;
    out.open("quiz.txt");

    if (!out.good()) {
        std::cerr << "Can't open quiz.txt to write." << std::endl;
        return 1;
    }

    quiz.PrintStudentQuiz(out);

    out.close();

    return 0;
}