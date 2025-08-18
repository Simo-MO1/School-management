#include "Student.h" // Case-sensitive include, ensure it matches "student.h"
#include "grade.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std; // OK to use in .cpp file

Student::Student() {}
Student::Student(int id, int age, string first, string last, string sex, string BirthP, string BirthD, string nat)
    : ID(id), First_Name(first), Last_Name(last), Age(age), Sex(sex), Birth_Place(BirthP), Birth_Date(BirthD), Nationality(nat) {}

void Student::displayInfo() const
{
  cout << "ID: " << ID << "\nAge: " << Age << "\nName: " << First_Name << " " << Last_Name << "\nBirth Information: " << Birth_Date << " in " << Birth_Place << "\nSex: " << Sex << "\nNationality: " << Nationality << endl; 
}

int Student::getID() const
{
  return ID;
}

string Student::getFullName() const
{
  return First_Name + " " + Last_Name;
}

void Student::addGrade(const std::string& subject, float grade) {
    grades.push_back({subject, grade});
}

void Student::saveToFile() const
{
  // Open file in append mode (ios::app) to prevent overwriting existing data
  ofstream out("students.txt", ios::app);
  if (out.is_open())
  {
    out << ID << "," << Age << "," << First_Name << "," << Last_Name << "," << Birth_Place << "," << Birth_Date << "," << Sex << "," << Nationality <<endl;
    out.close();
  }
  else
  {
    cerr << "Unable to open students.txt for writing!!\n";
  }
}

void Student::displayGrade() const{
  
    std::vector<Grades> allGrades = Grades::loadGradesFromFile(this->ID);

    if (allGrades.empty()) {
        std::cout << "No grades available for " << First_Name << " " << Last_Name << "\n";
        return;
    }

    std::cout << "\nGrades for " << First_Name << " " << Last_Name << ":\n";
    std::cout << std::left << std::setw(20) << "Subject" << "Scores\n";
    std::cout << "-----------------------------------\n";

    for (const auto& grade : allGrades) {
        std::cout << std::left << std::setw(20) << grade.getSubject();

        const auto& scores = grade.getScores();
        for (size_t i = 0; i < scores.size(); ++i) {
            std::cout << scores[i];
            if (i < scores.size() - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }

    std::cout << "-----------------------------------\n";
}

void Student::loadGradesFromFile(){
   Grades g;
  g.displayGrades();
}

std::istream& operator>>(std::istream& in, Student& s){  //this is confusing
   in>>s.ID;
   in>>s.Age;
   std::getline(in, s.First_Name);
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   std::getline(in, s.Last_Name);
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   std::getline(in, s.Birth_Place);
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   std::getline(in, s.Birth_Date);
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   
   std::getline(in, s.Sex);
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   
   std::getline(in, s.Nationality);
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   
   return in;
}