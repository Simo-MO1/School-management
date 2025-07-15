#include "Student.h" // Case-sensitive include, ensure it matches "student.h"
#include "grade.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std; // OK to use in .cpp file

Student::Student() {}
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

float Student::getGrade() const
{
  return Grade;
}

void Student::setGrade(float g)
{
  Grade = g;
}

void Student:: addGrade(const std::string& subject, float score){
  grades.emplace_back(subject,score);
}

void Student::displayGrade() const{
  if(grades.empty()){
     cout<<"No grade available yet!\n";
     return;
  }
  std::cout<<"\nGraeds for "<<getFullName()<<":\n";
  std::cout << "-------------------------------\n";
  std::cout<<std::left<<std::setw(15)<<"subject"<<"score";
  std::cout << "-------------------------------\n";
  
  for(const auto&grade: grades){
     std::cout<<std::left<<std::setw(15)<<grade.getSubject()<<grade.getScore()<<"\n";
  }
}

void Student::loadGradesFromFile(){
  ifstream file("grades.txt");
  string line;
  while(getline(file,line)){
    stringstream ss(line);
    std::string idStr, subject, scoreStr;
    getline(ss,idStr,',');
    getline(ss,subject,',');
    getline(ss,scoreStr,',');

    if(std::stoi(idStr)==this->getID()){
       try{
        float score=stof(scoreStr);
        addGrade(subject, score);
       } catch (const std::invalid_argument &e){
           cerr<<"Invalid score!"<<e.what()<<"\n";
       }
    }
  }
}