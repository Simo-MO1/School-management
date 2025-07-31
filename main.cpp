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
    string idstr, agestr, fname, lname, birthp, birthd, gender, natio, gra;
    float grade=-1.0f;  //i forgot what's this 
    
    if (getline(ss, idstr, ',') &&
        getline(ss, agestr, ',') &&
        getline(ss, fname, ',') &&
        getline(ss, lname, ',') &&
        getline(ss, birthp, ',') &&
        getline(ss, birthd, ',') &&
        getline(ss, gender, ',') &&
        getline(ss, natio, ',')&&
        getline(ss, gra,',')
        )
    { if(ss, gra,','){
       if(!gra.empty()){
        try{
          grade=stof(gra);
        } catch(const std::invalid_argument &e){
            cerr<<"ERROR!!"<<e.what()<<endl;
        }
       }
    }
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

void loadAllProfessorsFromFile(vector<Professor>&professors){
 ifstream PoutFile("professor.txt");
 if(!PoutFile.is_open()){
  cerr<<"File is not found or couldn't be opened! Starting with no professors\n";
  waitEnter();
  return;
 }

 string line;

 while(getline(PoutFile,line)){
  stringstream ss(line);
  string strID, strAge, fname, lname, spec, sal;
  float sala=-1.0f;

  if(getline(ss,strID,',')&&
     getline(ss,strAge,',')&&
     getline(ss, fname,',')&&
     getline(ss,lname,',')&&
     getline(ss,spec,',')&&
     getline(ss,sal,',')){
      if(ss,sal,','){
         if(!sal.empty()){
          try{
            sala=stof(sal);
          }catch(const std::invalid_argument &e){
            cerr<<"Error!"<<e.what()<<endl;
          }
         }
      }
     }try{
  Professor p(stoi(strID),stoi(strAge), fname, lname, spec, stof(sal));
  professors.push_back(p);
 } catch(const std::invalid_argument &e){
    cerr<<"Error converting string to int during professor load: "<<e.what()<<"in line"<<line<<endl;
 } catch(const std::out_of_range &e){
    cerr<<"Value out of range during student load: "<<e.what()<<"in line"<<line<<endl;
 } 
 } 
 PoutFile.close();
 cout<<"Professors loaded from file!\n";
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

void StudentMenu(int ID, vector<Student>&students){ // IMPORTANT: The 'students' parameter must be a non-const reference
  int studentChoice;
  do{cout<<"\nWelcome Student: "<<ID<<endl;
  cout<<"\n=========Student Menu=========\n";
  cout<<"1-View personal information\n2-View Grades\n3-Log out\n";
  cout<<"Enter your choice: \n";
  cin>>studentChoice;
  clearInput();
  bool found=false;
  if(studentChoice==1){
    for(const auto& s:students){
     if(s.getID()==ID){
       s.displayInfo();
       found=true;
       break;
     }
     if(!found){std::cout<<"Student not found!\n";}
     waitEnter();
     }
  }
  Student* currentStudent = nullptr;
        for (auto& s : students) { // Use non-const reference to modify 's' if needed (e.g., load grades)
            // Assuming Username is "First_Name Last_Name"
            // If Username is just First_Name, adjust getFullName() or comparison
            if (s.getID() == ID) {
                currentStudent = &s;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Student not found in the system!\n";
            waitEnter();
            continue; // Go back to menu if student not found
        }

        switch (studentChoice) {
            case 1:
                currentStudent->displayInfo();
                waitEnter();
                break;
            case 2:
                currentStudent->loadGradesFromFile(); 
                currentStudent->displayGrade();       
                waitEnter();
                break;
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                waitEnter();
                break;
        }
    } while (studentChoice != 3);
}

void ProfessorMenu(int ProfID, const vector<Professor>&professors, vector<Student>&students){
  int choice;
  Professor currentProfessor;
  bool found=false;
  for(const auto& prof:professors){
    if(prof.getID()==ProfID){
       currentProfessor=prof; //need to be clarified tooo
       found=true;
       break;
    }
  }

  if(!found){
    cout<<"Professor is not found!\n";
    return;
  }

  do{cout << "\n===== Professor Menu =====\n";
        cout << "1. View Personal Info\n";
        cout << "2. Add Grade\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice){
          case 1:
          currentProfessor.displayInfo();
          break;

          case 2:
          currentProfessor.addGrade();
          break;

          case 3:
          cout<<"Logging out!\n";
          break;

          default:
          cout<<"Invalid choice!Try again\n";
        }

      }while(choice!=3);
}

int main()
{
  vector<Student> students;
  vector<Professor> profs;

  loadStudentsFromFile(students);
  loadAllProfessorsFromFile(profs);
  // You might want to load professors from file too, similar to students
  // loadProfessorsFromFile(profs);

  string password, role;
  int ProfID;
  cout << "Enter your ID: ";
  cin >> ProfID;
  cout << "Password: ";
  cin >> password;
  clearInput(); 

  if (!User::authenticate(ProfID, password, role))
  {
    cout << "Login failed. Exiting...\n";
    waitEnter(); 
    return 0;
  }
  cout << "Welcome " << role << "!\n";
  for(auto&c:role) c=tolower(c);  //everything wil be in lowercase
  if (role == "admin")
    adminMenu(students, profs);
  else if(role == "student") StudentMenu(ProfID, students);
  else if(role == "professor") ProfessorMenu( ProfID, profs, students);
  else
    cout << "Unkown Role!...\n";

  return 0;
}

