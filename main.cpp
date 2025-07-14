#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include "student.h"
#include "professor.h"
#include "user.h"
#include <sstream>

// It's generally better to avoid 'using namespace std;' in headers,
// but for .cpp files, it's common.
using namespace std;

void clearInput()
{
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitEnter()
{
  cout << "Please press Enter to continue...\n";
  // cin.ignore() is already called by clearInput() if there's leftover input.
  // Using cin.get() is sufficient here.
  cin.get();
}

void addStudent(vector<Student> &students)
{
  int ID, Age;
  string First_Name, Last_Name, Sex, Birth_Place, Birth_Date, Nationality;
  float Grade;

  cout << "enter student's ID: \n";
  while (!(cin >> ID))
  {
    cout << "Invalid Input! Enter again!! \n";
    clearInput();
  }
  clearInput(); // Clear buffer after reading ID

  cout << "Enter first name: ";
  getline(cin, First_Name); // Use getline for names to handle spaces

  cout << "Enter last name: ";
  getline(cin, Last_Name);

  cout << "Enter your age: ";
  while (!(cin >> Age))
  {
    cout << "Invalid Input! Enter again!!\n";
    clearInput();
  }
  clearInput(); // Clear buffer after reading Age

  cout << "Enter your birth date (DD/MM/YY): ";
  getline(cin, Birth_Date); // Use getline for birth date

  cout << "Enter your birth place: ";
  getline(cin, Birth_Place); // Use getline for birth place

  cout << "Enter your Gender (Male/Female): ";
  getline(cin, Sex); 

  cout << "Enter your nationality: ";
  getline(cin, Nationality); 

  // Corrected constructor call based on student.h order:
  Student s(ID, Age, First_Name, Last_Name, Sex, Birth_Place, Birth_Date, Nationality, Grade);
  students.push_back(s);
  cout << "✅ Student added!!\n";

  cout<<"Student added!!\n";
  waitEnter();
}

void displayStudents(const vector<Student> students)
{
  if (students.empty())
  {
    cout << "No student in the system\n";
    waitEnter();
    return;
  }

  cout << "\nAll students\n";
  for (const auto &student : students)
  {
    cout << "\n-----------------------\n";
    student.displayInfo();
    cout << "\n-----------------------\n";
  }
  waitEnter();
}

void saveAllToFile(const vector<Student> &students)
{
  ofstream outFile("students.txt");
  if (!outFile.is_open())
  {
    cerr << "ERROR! Unable to open students.txt for writing!\n";
    waitEnter();
    return;
  }

  for (const auto &student : students)
  {
    student.saveToFile(); 
  }
  outFile.close();
  cout << "All students saved to file\n";
  waitEnter();
}

void loadStudentsFromFile(vector<Student> &students)
{
  ifstream file("students.txt");
  if (!file.is_open())
  {
    cout << "students.txt not found or could not be opened. Starting with no students.\n";
    waitEnter();
    return;
  }

  string line;
  while (getline(file, line))
  {
    stringstream ss(line);
    string idstr, agestr, fname, lname, birthp, birthd, gender, natio,gra;

    
    if (getline(ss, idstr, ',') &&
        getline(ss, agestr, ',') &&
        getline(ss, fname, ',') &&
        getline(ss, lname, ',') &&
        getline(ss, birthp, ',') &&
        getline(ss, birthd, ',') &&
        getline(ss, gender, ',') &&
        getline(ss, natio, ',')&&
        getline(ss, gra,','))
    {
      try
      {
        Student s(stoi(idstr), stoi(agestr), fname, lname, gender, birthp, birthd, natio, stof(gra));
        students.push_back(s);
      }
      catch (const std::invalid_argument &e)
      {
        cerr << "Error converting string to int during student load: " << e.what() << " in line: " << line << endl;
      }
      catch (const std::out_of_range &e)
      {
        cerr << "Value out of range during student load: " << e.what() << " in line: " << line << endl;
      }
    }
    else
    {
      cerr << "Skipping malformed line in students.txt: " << line << endl;
    }
  }
  file.close();
  cout << "Students loaded from file.\n";
}

void addProfessor(vector<Professor> &profs)
{
  int ID, Age;
  float Salary; 
  string First_Name, Last_Name, Speciality;

  cout << "Enter Professor ID: ";
  while (!(cin >> ID))
  {
    cout << "Invalid Input! Enter again!! \n";
    clearInput();
  }
  clearInput();

  cout << "Age: ";
  while (!(cin >> Age))
  {
    cout << "Invalid Input! Enter again!!\n";
    clearInput();
  }
  clearInput();

  cout << "First Name: ";
  getline(cin, First_Name);

  cout << "Last Name: ";
  getline(cin, Last_Name);

  cout << "Specialty: ";
  getline(cin, Speciality);

  cout << "Salary: ";
  while (!(cin >> Salary))
  {
    cout << "Invalid Input! Enter again!!\n";
    clearInput();
  }
  clearInput();

  profs.emplace_back(ID, Age, First_Name, Last_Name, Speciality, Salary);
  cout << " Professor added.\n";
  waitEnter();
}

void displayProfessors(vector<Professor> &profs) 
{
  if (profs.empty())
  {
    cout << "No professor available\n";
    waitEnter();
    return;
  }
  cout << "\nAll Professors\n";
  for (const auto &prof : profs)
  {
    cout << "\n-----------------------\n";
    prof.displayInfo();
    cout << "\n-----------------------\n";
  }
  waitEnter();
}

void saveAllProfessorsToFile(vector<Professor> &profs)
{
  ofstream outFile("professor.txt"); // This will truncate (clear) the file
  if (!outFile.is_open())
  {
    cerr << "ERROR! Unable to open professor.txt for writing!\n";
    waitEnter();
    return;
  }

  for (const auto &prof : profs)
  {
    prof.saveToFile(); 
  }
  outFile.close(); 
  cout << "Professors saved.\n";
  waitEnter();
}

void adminMenu(vector<Student> &students, vector<Professor> &profs)
{
  int choice;
  do
  {
    cout<<"\n_________Menu___________\n";
    cout<<"1- Add student\n";
    cout<<"2- Display all Students\n";
    cout<<"3- Save students to file\n";
    cout<<"4- Add professor\n";
    cout<<"5- Display all professors\n";
    cout<<"6- Save professors to file\n";
    cout<<"7- Sign Up\n";
    cout<<"8-Exit\n";
    cout << "\n-------Enter your choice: -------\n";

    cin >> choice; 
    clearInput();  

    if (cin.fail())
    {
      clearInput();
      cout << "Invalid choice! Enter again!\n";
      continue; 
    }

    switch (choice)
    {
    case 1:
      addStudent(students);
      break;

    case 2:
      displayStudents(students);
      break;

    case 3:
      saveAllToFile(students);
      break;

    case 4:
      addProfessor(profs);
      break;

    case 5:
      displayProfessors(profs); 
      break;

    case 6:
      saveAllProfessorsToFile(profs);
      break;

    case 7:
      User::registerUser(); waitEnter();
      break;

    case 8:
      cout << "Logging out...\n";
      break; 

    default:
      cout << "Invalid choice! Try again!\n";
      waitEnter();
    }
  } while (choice != 8);
}

void StudentMenu(const string& Username, const vector<Student>&students){
  cout<<"\nWelcome Student: "<<Username<<endl;
  cout<<"\n=========Student Menu=========\n";
  for(const auto& s:students){
     if(s.getFullName()==Username){
       s.displayInfo();
       break;
     }
  }
}

void ProfessorMenu(vector<Student>&students){
  int choice;
  do{
  cout<<"\nWelcome Professor: "<<endl;
  cout<<"\n=========Professor Meny=========\n";
  cout<<"1-View student list\n 2-Add Grade\n 3-Log out\n";
  cout<<"Enter your choice\n"; cin>>choice;
  if(choice==1){
    displayStudents(students);
  } else if(choice==2){
    int id;
    float grade;
    cout<<"Enter Student's ID: \n"; cin>>id;
    cout<<"Enter his/her grade: \n"; cin>>grade;
    for(auto& s:students){
      if(s.getID()==id){
        s.setGrade(grade);
        cout<<"Grade updated!\n";
        break;
      }
    }
    waitEnter();
  }
  }while(choice!=3);
}

int main()
{
  vector<Student> students;
  vector<Professor> profs;

  loadStudentsFromFile(students);
  // You might want to load professors from file too, similar to students
  // loadProfessorsFromFile(profs);

  string username, password, role;
  cout << "Username: ";
  cin >> username;
  cout << "Password: ";
  cin >> password;
  clearInput(); 

  if (!User::authenticate(username, password, role))
  {
    cout << "Login failed. Exiting...\n";
    waitEnter(); 
    return 0;
  }
  cout << "Welcome " << role << "!\n";
  if (role == "admin")
    adminMenu(students, profs);
  else if(role == "student") StudentMenu(username, students);
  else if(role == "professor") ProfessorMenu(students);
  else
    cout << "Unkown Role!...\n";

  return 0;
}

