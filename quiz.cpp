#include "quiz.h"

Quiz::Quiz(
    std::vector<std::unordered_map<int, std::vector<std::string> > > mapList,
    bool MC, bool SA, bool MM)
    : MC(MC), SA(SA), MM(MM) {
    if (mapList.size() == 3) {
        for (auto &element : mapList[0]) {
            AddMultipleChoiceQuestion(element.first, element.second);
        }

        for (auto &element : mapList[1]) {
            AddShortAnswerQuestion(element.first, element.second);
        }

        for (auto &element : mapList[2]) {
            AddMixAndMatchQuestion(element.first, element.second);
        }
    } else if (mapList.size() == 2) {
        if (MC && SA) {
            for (auto &element : mapList[0]) {
                AddMultipleChoiceQuestion(element.first, element.second);
            }

            for (auto &element : mapList[1]) {
                AddShortAnswerQuestion(element.first, element.second);
            }
        } else if (SA && MM) {
            for (auto &element : mapList[0]) {
                AddShortAnswerQuestion(element.first, element.second);
            }

            for (auto &element : mapList[1]) {
                AddMixAndMatchQuestion(element.first, element.second);
            }
        } else if (MC && MM) {
            for (auto &element : mapList[0]) {
                AddMultipleChoiceQuestion(element.first, element.second);
            }

            for (auto &element : mapList[1]) {
                AddMixAndMatchQuestion(element.first, element.second);
            }
        }
    } else if (mapList.size() == 1) {
        if (MC) {
            for (auto &element : mapList[0]) {
                AddMultipleChoiceQuestion(element.first, element.second);
            }
        } else if (SA) {
            for (auto &element : mapList[0]) {
                AddShortAnswerQuestion(element.first, element.second);
            }
        } else if (MM) {
            for (auto &element : mapList[0]) {
                AddMixAndMatchQuestion(element.first, element.second);
            }
        }
    }
}

void Quiz::AddMultipleChoiceQuestion(int question_number,
                                     const std::vector<std::string> &answers) {
    multiple_choice_questions.insert({question_number, answers});
}

void Quiz::AddShortAnswerQuestion(int question_number,
                                  const std::vector<std::string> &question) {
    short_answer_questions.insert({question_number, question});
}

void Quiz::AddMixAndMatchQuestion(int question_number,
                                  const std::vector<std::string> &problems) {
    mix_and_match_questions.insert({question_number, problems});
}

void Quiz::PrintStudentQuiz(std::ostream &out) const {
    int part = 0;

    if (MC) {
        out << "Part " << ++part << ": Multiple Choice" << std::endl;
        for (auto &question : multiple_choice_questions) {
            out << question.first << ") " << question.second.front()
                << std::endl;

            char choice = 'A';
            for (unsigned int i = 1; i < question.second.size(); ++i) {
                out << choice << ". " << question.second[i] << std::endl;
                ++choice;
            }
        }

        out << std::endl;
    }

    if (SA) {
        out << "Part " << ++part << ": Short Answer" << std::endl;
        for (auto &question : short_answer_questions) {
            out << question.first << ") " << question.second.front();

            for (int i = 0; i < std::stoi(question.second.back()); ++i) {
                out << std::endl;
            }
        }

        out << std::endl;
    }

    if (MM) {
        out << "Part " << ++part << ": Mix and Match" << std::endl;
        for (auto &question : mix_and_match_questions) {
            std::vector<std::string> questions;
            for (unsigned int i = 0; i < question.second.size(); i += 2) {
                questions.push_back(question.second[i]);
            }
            
            std::vector<std::string> answers;
            for (unsigned int i = 1; i < question.second.size(); i += 2) {
                answers.push_back(question.second[i]);
            }

            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(answers.begin(), answers.end(), g);

            out << question.first << ") " << std::endl;

            char choice = 'A';

            int max_length = questions[0].length();
            for (unsigned int i = 1; i < questions.size(); ++i) {
                if (questions[i].length() > static_cast<unsigned int>(max_length)) {
                    max_length = questions[i].length();
                }
            }

            for (unsigned int i = 0; i < questions.size(); ++i) {
                out << choice << ". " << questions[i];

                out << '\t' << std::setw(max_length) << std::left;

                out << answers[i] << std::endl;

                ++choice;
            }
        }

        out << std::endl;
    }
}
