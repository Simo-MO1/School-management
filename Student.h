#ifndef student_h
#define student_h
#include <string>

class Student
{
private:
  int ID, Age;
  std::string First_Name, Last_Name, Sex, Birth_Place, Birth_Date, Nationality;

public:
  Student();
  Student(int ID, int Age, std::string First_Name, std::string Last_Name, std::string Sex, std::string Birth_Place, std::string Birth_Date, std::string Nationality);

  void displayInfo() const;
  int getID() const;
  std::string getFullName() const;
  void saveToFile() const;
};
#endif
