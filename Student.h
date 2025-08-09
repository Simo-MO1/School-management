#ifndef student_h
#define student_h
#include "grade.h"
#include <string>
#include <vector>


class Student
{
private:
  int ID, Age;
  std::string First_Name, Last_Name, Sex, Birth_Place, Birth_Date, Nationality;
  std::vector<std::pair<std::string, float>> grades; // need some more exercices on this

public:
  Student();
  Student(int ID, int Age, std::string First_Name, std::string Last_Name, std::string Sex, std::string Birth_Place, std::string Birth_Date, std::string Nationality);

  void displayInfo() const;
  int getID() const;
  std::string getFullName() const;
  void saveToFile() const;
  void loadGradesFromFile();
  void displayGrade() const;
  friend std:: istream& operator >>(std::istream& in, Student& s); // neet to be clarified (what does istream mean and do?)
  void addGrade(const std::string& subject, float grade);
  void displayGradesTable() const;
};
#endif
