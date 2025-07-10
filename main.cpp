#include<iostream>
#include<limits>
#include<vector>
#include<fstream>
#include "student.h"
#include "professor.h"
#include "user.h"
#include<sstream>
using namespace std;

void clearInput(){
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void waitEnter(){
  cout<<"Please press Enter to continue...\n";
  cin.ignore();
  cin.get();
}
void addStudent(vector<Student>&students){
  int ID, Age;
  string First_Name, Last_Name, Sex, Birth_Place, Birth_Date, Nationality;

  cout<<"enter student's ID: \n";
  while(!(cin>>ID)){
    cout<<"Invalild Input! Enter again!! \n";
    clearInput();
  }

  cout<<"Enter you name: ";
  cin>>First_Name>>Last_Name;

  cout<<"Enter your age: ";
  while(!(cin>>Age)){
    cout<<"Invalid Input! Enter again!!\n";
    clearInput();
  }

  cout<<"Enter your birth informations ( 'DD/MM/YY' in 'Place'): \n";
  cin>>Birth_Date>>Birth_Place;

  cout<<"Enter your Gender(Male/Female): \n";
  cin>>Sex;

  cout<<"Enter your personality: \n";
  cin>>Nationality;

  Student s(ID,Age,First_Name,Last_Name,Birth_Place,Birth_Date,Sex,Nationality);
  students.push_back(s);
  cout<<"Student added!!\n";
  waitEnter();
}

void displayStudents(const vector<Student>students){
  if(students.empty()){
    cout<<"No student in the system\n";
    return;
  }

  cout<<"\nAll students\n";
  for(const auto&student:students){
    cout<<"-----------------------\n";
    student.displayInfo();
    cout<<"-----------------------\n";
  }
  waitEnter();
}

void saveAllToFile(const vector<Student>&students){
  for(const auto& student:students){
    student.saveToFile();
  }
  cout<<"All students saved to file\n";
  waitEnter();
}

void loadStudentsFromFile(vector<Student>&students){
  ifstream file("students.txt");
  string line;
  while(getline(file,line)){
  stringstream ss(line);
  string idstr, agestr, fname, lname, birthp, birthd, gender, natio;
  getline(ss, idstr,',');
  getline(ss, agestr,',');
  getline(ss, fname,',');
  getline(ss, lname,',');
  getline(ss, birthp,',');
  getline(ss, birthd,',');
  getline(ss, gender,',');
  getline(ss, natio,',');

  Student s(stoi(idstr), stoi(agestr), fname, lname, birthp, birthd, gender, natio);
  students.push_back(s);
  waitEnter();
  }
}

void addProfessor(vector<Professor>&profs){
  int ID, Age, Salary;
  string First_Name, Last_Name, Speciality;
  cout << "Enter Professor ID: "; cin >> ID;
  cout << "Age: "; cin >> Age;
  cout << "First Name: "; cin >> First_Name;
  cout << "Last Name: "; cin >> Last_Name;
  cout << "Specialty: "; cin >> Speciality;
  cout << "Salary: "; cin >> Salary;
  profs.emplace_back(ID, Age, Salary, First_Name, Last_Name, Speciality);
  cout << "✅ Professor added.\n";
  waitEnter();
}

void displayPrfessors(vector<Professor>&profs){
  if(profs.empty()){cout<<"No professor available\n";}
  for(const auto& prof:profs){
    prof.displayInfo();
  }
  waitEnter();
}

void saveAllProfessorsToFile(vector<Professor>profs){
  for(const auto&prof:profs){
    prof.saveToFile();
    cout << "💾 Professors saved.\n";
  }
  waitEnter();
}

void adminMenu(vector<Student>&students, vector<Professor>&profs){
  int choice;
  do{
    cout<<"\n_________Menu___________\n";
    cout<<"1- Add sudent\n";
    cout<<"2- Display all Students\n";
    cout<<"3- Save students to file\n";
    cout<<"4- Add professor\n";
    cout<<"5- Display all professors\n";
    cout<<"6- Save professors to file\n";
    cout<<"7- Exit\n";

    if(cin.fail()){
       clearInput();
       cout<<"Invalid choice! Enter again!";
       continue;
    }

    switch(choice){
      case 1 : addStudent(students);
      break;

      case 2 : displayStudents(students);
      break;

      case 3 : saveAllToFile(students);
      break;

      case 4 : addProfessor(profs);
      break;

      case 5 : displayPrfessors(profs);
      break;

      case 6 : saveAllProfessorsToFile(profs);
      break;

      case 7: cout << "Logging out...\n"; break;
      break;

      default : cout<<"Invalid choice! Try again!\n";
    }
}while(choice!=7);
}

int main(){
  vector<Student>students;
  vector<Professor>profs;
  loadStudentsFromFile(students);
  string username, password, role;
  cout << "Username: "; cin >> username;
  cout << "Password: "; cin >> password;

  if (!User::authenticate(username, password, role)) {
      cout << "Login failed. Exiting...\n";
      return 0;
  }
  cout << "Welcome " << role << "!\n";
  if (role == "admin") adminMenu(students, profs);
  else cout << "Other roles coming soon...\n";

 return 0;
}
