#include "grade.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>

Grades::Grades() {}
Grades::Grades(const int &id, const std::string &subject, const std::vector<float> &scores) : ID(id), Subject(subject), Scores(scores) {}
int Grades::getID() const { return ID; }
std::string Grades::getSubject() const { return Subject; }
std::vector<float> Grades::getScores() const { return Scores; }

void Grades::addGrade()
{

  std::cout << "\n Enter student's ID:\n";
  std::cin >> ID;

  std::cout << "\Enter the subject:\n";
  std::cin.ignore();
  std::getline(std::cin, Subject);

  Scores.clear();
  std::cout << "How many grades do you want to enter?\n";
  int count;
  std::cin >> count;

  std::cout << "\nEnter his/her grades:\n";
  for (int i = 0; i < count; ++i)
  {
    float score;
    std::cin >> score;
    Scores.push_back(score);
  }

  saveGradesToFile();
  std::cout << "Grades saved successfully!\n";
}

void Grades::saveGradesToFile() const
{
  std::ofstream out("grades.txt", std::ios::app);
  if (out.is_open())
  {
    out << ID << ", " << Subject;
    for (float score : Scores)
    {
      out << "," << score;
    }
    out << "\n";
    out.close();
  }
  else
  {
    std::cerr << "Unable to open the file!\n";
  }
}

void Grades::displayGrades() const
{
  if (Scores.empty())
  {
    std::cout << "No grade available yet!\n";
    return;
  }
  std::cout << "\n--- Grades Details ---\n";
  std::cout << std::left << std::setw(15) << "Student ID:" << ID << "\n";
  std::cout << std::left << std::setw(15) << "Subject:" << Subject << "\n";
  std::cout << std::left << std::setw(15) << "Scores:";

  for (size_t i = 0; i < Scores.size(); ++i)
  {
    std::cout << Scores[i];
    if (i < Scores.size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << "\n"; 
  std::cout << "----------------------\n";
}

std::vector<Grades> Grades::loadGradesFromFile(int gID)
{
  std::ifstream file("grades.txt");
  std::vector<Grades> result;
  if (!file.is_open())
  {
    std::cerr << "Error: Could not open grades.txt for reading!";
    return result; //why return result here
  }
  // static functions don’t have access to this pointer. They operate at class level, not instance level.
  std::string line;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string idstr, subjectstr, markstr;
    std::getline(ss, idstr, ',');
    std::getline(ss, subjectstr, ',');

    if(!std::getline(ss,idstr,','))continue; // Handle empty line or missing ID (need to be clarified)
    int curentID = std::stoi(idstr);

    std::vector<float> currentScores;  // Local vector for scores
    while (std::getline(ss, markstr, ',')) //why??
    {
      try
      {
        currentScores.push_back(std::stof(markstr));
      }
      catch (const std::invalid_argument &e)
      {
        std::cerr << "Error! invalid score found in line"<<line<<"Details: "<<e.what() << std::endl;
      }
    }
    result.push_back(Grades(curentID, subjectstr, currentScores));
  }

  file.close();
  return result; // why??
}
