#include "professor.h"
#include <iostream>
#include <fstream>

using namespace std; 

Professor::Professor(){};
Professor::Professor(int id, int age, string first, string last, string spec, float sal, string email)
    : ID(id), Age(age), First_Name(first), Last_Name(last), Speciality(spec), Salary(sal), Email(email) {}

void Professor::displayInfo() const
{
  cout << "ID: " << ID << "\nAge: " << Age << "\nName: " << First_Name << " " << Last_Name << "\nSpecialty: " << Speciality << "\nSalary: " << Salary <<  "\nEmail: "<< Email<< endl; 
}

int Professor::getID() const
{
  return ID;
}

string Professor::getFullName() const
{
  return First_Name + "," + Last_Name;
}

void Professor::saveToFile() const
{
  // Open file in append mode (ios::app) to prevent overwriting existing data
  ofstream file("professor.txt", ios::app);
  if (file.is_open())
  {
    file << ID << "," << Age << "," << First_Name << "," << Last_Name << "," << Speciality << "," << Salary <<","<<Email<< endl;
    file.close();
  }
  else
  {
    cerr << "ERROR! Unable to open professor.txt for writing!\n";
  }
}

string Professor::getEmail() const{
   return Email;
}