#include "Student.h" // Case-sensitive include, ensure it matches "student.h"
#include <iostream>
#include <fstream>

using namespace std; // OK to use in .cpp file

Student::Student(){}
Student::Student(int id, int age, string first, string last, string sex, string BirthP, string BirthD, string nat, float grade)
    : ID(id), First_Name(first), Last_Name(last), Age(age), Sex(sex), Birth_Place(BirthP), Birth_Date(BirthD), Nationality(nat), Grade(grade) {}

void Student::displayInfo() const
{
  cout << "ID: " << ID << "\nAge: " << Age << "\nName: " << First_Name << " " << Last_Name << "\nBirth Information: " << Birth_Date << " in " << Birth_Place << "\nSex: " << Sex << "\nNationality: " << Nationality << endl; // Added space and endl
}

int Student::getID() const
{
  return ID;
}

string Student::getFullName() const
{
  return First_Name + "," + Last_Name;
}

void Student::saveToFile() const
{
  // Open file in append mode (ios::app) to prevent overwriting existing data
  ofstream out("students.txt", ios::app);
  if (out.is_open())
  {
    out << ID << "," << Age << "," << First_Name << "," << Last_Name << "," << Birth_Place << "," << Birth_Date << "," << Sex << "," << Nationality << endl;
    out.close();
  }
  else
  {
    cerr << "Unable to open students.txt for writing!!\n";
  }
}

float Student::getGrade() const{
    return Grade;
  }



