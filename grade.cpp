#include "grade.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iostream>
#include<iomanip>

Grades::Grades(const int& id, const std::string& subject, const std::vector<int>& scores):ID(id),Subject(subject),Scores(scores){}
int Grades::getID() const {return ID;}
std::string Grades::getSubject() const{return Subject;}
std::vector<int> Grades::getScores() const{return Scores;}

void Grades::displayGrades() const{
  if(Scores.empty()){
     std::cout<<"No grade available yet!\n";
     return;
  }
    std::cout << "\n--- Grades Details ---\n";
  std::cout << std::left << std::setw(15) << "Student ID:" << ID << "\n";
  std::cout << std::left << std::setw(15) << "Subject:" << Subject << "\n";
  std::cout << std::left << std::setw(15) << "Scores:";
  
  for (size_t i = 0; i < Scores.size(); ++i) {
      std::cout << Scores[i];
      if (i < Scores.size() - 1) {
          std::cout << ", "; 
      }
  }
  std::cout << "\n"; // Newline after all scores are printed
  std::cout << "----------------------\n";
}

