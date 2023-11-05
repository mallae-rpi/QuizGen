
#ifndef QUIZ
#define QUIZ

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Quiz {
   public:
    Quiz(std::vector<std::unordered_map<int, std::vector<std::string> > >,
         bool MC, bool SA, bool MM);

    void AddMultipleChoiceQuestion(int question_number,
                                   const std::vector<std::string> &answers);

    void AddShortAnswerQuestion(int question_number,
                                const std::vector<std::string> &question);

    void AddMixAndMatchQuestion(int question_number,
                                const std::vector<std::string> &problems);

    void PrintStudentQuiz(std::ostream &out) const;

   private:
    bool MC;
    bool SA;
    bool MM;


    // Multiple Choice
    std::unordered_map<int, std::vector<std::string> >
        multiple_choice_questions;

    // Short Answer
    std::unordered_map<int, std::vector<std::string> > short_answer_questions;

    // MixNMatch
    std::unordered_map<int, std::vector<std::string> > mix_and_match_questions;
};

#endif