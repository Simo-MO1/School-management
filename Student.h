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
  float Grade;
  std::vector<Grades>grades;

public:
  Student();
  Student(int ID, int Age, std::string First_Name, std::string Last_Name, std::string Sex, std::string Birth_Place, std::string Birth_Date, std::string Nationality, float Grade);

  void displayInfo() const;
  int getID() const;
  std::string getFullName() const;
  void saveToFile() const;
  float getGrade()const;
  void setGrade(float g);
  void addGrade(const std::string& subject, float score);
};
#endif
