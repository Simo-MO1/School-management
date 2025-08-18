#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include "Student.h"
#include "professor.h"
#include "user.h"
#include <sstream>
#include "ConsoleUtils.h"
#include "Superior.h"

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
  Student s(ID, Age, First_Name, Last_Name, Sex, Birth_Place, Birth_Date, Nationality);
  students.push_back(s);
  cout << " Student added!!\n";

  waitEnter();
}

void displayStudents(const vector<Student> &students)
{
  if (students.empty())
    {
        cout << "No students in the system.\n";
    }
    else
    {
        cout << "\n--- All Students ---\n";
        for (const auto &s : students)
        {
            cout << "---------------------------\n";
            s.displayInfo();
            cout << "---------------------------\n";
        }
    }
    waitEnter();
}

void saveAllToFile(const vector<Student> &students)
{
  ofstream outFile("students.txt", ios::trunc);
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
  students.clear();
  ifstream file("students.txt");
  if (!file.is_open())
  {
    cout << "students.txt not found or could not be opened. Starting with no students.\n";
    waitEnter();
    return;
  }

  string line;
  while (getline(file, line)){
    if (line.empty())
      continue;
  
    stringstream ss(line);
    string idstr, agestr, fname, lname, birthp, birthd, gender, natio, gra;
    float grade = -1.0f; // i forgot what's this

    if (getline(ss, idstr, ',') &&
        getline(ss, agestr, ',') &&
        getline(ss, fname, ',') &&
        getline(ss, lname, ',') &&
        getline(ss, birthp, ',') &&
        getline(ss, birthd, ',') &&
        getline(ss, gender, ',') &&
        getline(ss, natio, ',') &&
        getline(ss, gra, ','))
    {
      if (!gra.empty())
      {
        try
        {
          grade = stof(gra);
        }
        catch (const std::invalid_argument &e)
        {
          cerr << "ERROR!!" << e.what() << endl;
        }
      }

      try
      {
        Student s(stoi(idstr), stoi(agestr), fname, lname, gender, birthp, birthd, natio);
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
  cout << " Students loaded from file: " << students.size() << " student(s).\n";
}

void addProfessor(vector<Professor> &profs)
{
  int ID, Age;
  float Salary;
  string First_Name, Last_Name, Speciality, Email;

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
  cout << "Email: ";
  getline(cin, Email);
  clearInput();

  profs.emplace_back(ID, Age, First_Name, Last_Name, Speciality, Salary, Email);
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
  ofstream outFile("professor.txt"); 
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

void loadAllProfessorsFromFile(vector<Professor> &professors)
{
  ifstream PoutFile("professor.txt");
  if (!PoutFile.is_open())
  {
    cerr << "File is not found or couldn't be opened! Starting with no professors\n";
    waitEnter();
    return;
  }

  string line;

  while (getline(PoutFile, line))
  {
    stringstream ss(line);
    string strID, strAge, fname, lname, spec, sal, email;
    float sala = -1.0f;

    if (getline(ss, strID, ',') &&
        getline(ss, strAge, ',') &&
        getline(ss, fname, ',') &&
        getline(ss, lname, ',') &&
        getline(ss, spec, ',') &&
        getline(ss, sal, ',')&&
        getline(ss, email, ','))
    {
    try
    {
      Professor p(stoi(strID), stoi(strAge), fname, lname, spec, stof(sal), email);
      professors.push_back(p);
    }
    catch (const std::invalid_argument &e)
    {
      cerr << "Error converting string to int during professor load: " << e.what() << "in line" << line << endl;
    }
    catch (const std::out_of_range &e)
    {
      cerr << "Value out of range during student load: " << e.what() << "in line" << line << endl;
    }
  }
  cout << "Professors loaded from file!\n";
}
  PoutFile.close();
}
void addSuperior(vector<Superior> &sup)
{
  string Fi_Name, La_Name, Email, Phone_Number;
    int ID;

  cout << "Enter Superior ID: ";
  while (!(cin >> ID))
  {
    cout << "Invalid Input! Enter again!! \n";
    clearInput();
  }
  clearInput();

  cout << "First Name: ";
  getline(cin, Fi_Name);

  cout << "Last Name: ";
  getline(cin, La_Name);

  cout << "Email: ";
  while (!(cin >> Email))
  {
    cout << "Invalid Input! Enter again!!\n";
    clearInput();
  }
  clearInput();
  cout << "Phone number: ";
  getline(cin, Phone_Number);
  clearInput();

  sup.emplace_back(ID, Fi_Name, La_Name, Email, Phone_Number);
  cout << " Superior added.\n";
  waitEnter();
}

void displaySuperior(vector<Superior> &sup)
{
  if (sup.empty())
  {
    cout << "No Superior available\n";
    waitEnter();
    return;
  }
  cout << "\nAll Professors\n";
  for (const auto &sups : sup)
  {
    cout << "\n-----------------------\n";
    sups.displayInfo();
    cout << "\n-----------------------\n";
  }
  waitEnter();
}

void saveAllSuperiorsToFile(vector<Superior> &sup)
{
  ofstream outFile("superior.txt"); // This will truncate (clear) the file
  if (!outFile.is_open())
  {
    cerr << "ERROR! Unable to open superior.txt for writing!\n";
    waitEnter();
    return;
  }

  for (const auto &sups : sup)
  {
    sups.saveToFile();
  }
  outFile.close();
  cout << "Superiors saved.\n";
  waitEnter();
}

void loadAllSuperiorsFromFile(vector<Superior> &sup)
{
  ifstream PoutFile("superior.txt");
  if (!PoutFile.is_open())
  {
    cerr << "File is not found or couldn't be opened! Starting with no professors\n";
    waitEnter();
    return;
  }

  string line;

  while (getline(PoutFile, line))
  {
    stringstream ss(line);
    string strID, fname, lname, email, pnum;
    float sala = -1.0f;

    if (getline(ss, strID, ',') &&
        getline(ss, fname, ',') &&
        getline(ss, lname, ',') &&
        getline(ss, email, ',')&&
        getline(ss, pnum, ','))
    try
    {
      Superior s(stoi(strID), fname, lname, email, pnum);
      sup.push_back(s);
    }
    catch (const std::invalid_argument &e)
    {
      cerr << "Error converting string to int during professor load: " << e.what() << "in line" << line << endl;
    }
    catch (const std::out_of_range &e)
    {
      cerr << "Value out of range during student load: " << e.what() << "in line" << line << endl;
    }
  }
  PoutFile.close();
  cout << "Superior loaded from file!\n";
}

void adminMenu(vector<Student> &students, vector<Professor> &profs, vector<Superior>&sup)
{
  int choice;
  do
  {
    clearScreen();
    setColor(12); // Light red
    typeWriter("===== ADMIN MENU =====\n", 10);
    resetColor();
typeWriter("1- Add student\n2- Display all Students\n3- Save students to file\n4- Add professor\n5- Display all professors\n6- Save professors to file\n7- Add Superior\n8- Display all Superiors\n9- Save Superiors to file\n10- Sign Up\n11-Exit\n",11);
    setColor(14);
    cout << "\n-------Enter your choice: -------\n";
    resetColor();
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
      addSuperior(sup);
      break;

    case 8:
      displaySuperior(sup);
      break;

    case 9:
      saveAllSuperiorsToFile(sup);
      break;

    case 10:
      User::registerUser();
      waitEnter();
      break;

    case 11:
      cout << "Logging out...\n";
      break;

    default:
      cout << "Invalid choice! Try again!\n";
      waitEnter();
    }
  } while (choice != 11);
}

void StudentMenu(int ID, vector<Student> &students)
{ // IMPORTANT: The 'students' parameter must be a non-const reference
  int studentChoice;
  Student *currentStudent = nullptr; // this need to be clarified

  do
  {
    clearScreen();
    setColor(10); // Light green
    typeWriter("===== STUDENT MENU =====\n", 10);
    resetColor();
    typeWriter("1-View personal information\n2-View Grades\n3-Log out\n",15);
    setColor(14); // Yellow prompt
    cout << "Enter your choice: \n";
    resetColor();
    cin >> studentChoice;
    clearInput();
    bool found = false;
    if (studentChoice == 1)
    {
      for (const auto &s : students)
      {
        if (s.getID() == ID)
        {
          s.displayInfo();
          found = true;
          break; // why break inside if and not outside??
        }
        waitEnter();
      }
      if (!found)
        {
          std::cout << "Student not found!\n";
        }
    }
    for (auto &s : students)
    { // Use non-const reference to modify 's' if needed (e.g., load grades)
      // Assuming Username is "First_Name Last_Name"
      // If Username is just First_Name, adjust getFullName() or comparison
      if (s.getID() == ID)
      {
        currentStudent = &s;
        found = true;
        break;
      }
    }

    if (!found)
    {
      cout << "Student not found in the system!\n";
      waitEnter();
      continue; // Go back to menu if student not found
    }

    switch (studentChoice)
    {
    case 1:
      currentStudent->displayInfo();
      waitEnter();
      break;
    case 2:
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

void ProfessorMenu(int ProfID, const vector<Professor> &professors, vector<Student> &students)
{
  int choice;
  const Professor *currentProfessor = nullptr;
  bool found = false;
  for (const auto &prof : professors)
  {
    if (prof.getID() == ProfID)
    {
      currentProfessor = &prof; // need to be clarified tooo
      found = true;
      break;
    }
  }

  if (!found)
  {
    cout << "Professor is not found!\n";
    return;
  }

  do
  {
    clearScreen();
    setColor(13); // Light purple
    typeWriter("===== PROFESSOR MENU =====\n", 10);
    resetColor();
    typeWriter("1. View Personal Info\n2. Add Grade\n3. Edit Grade\n4. Delete Grade\n5. Logout\n",15);
    setColor(14);
    cout << "Enter choice: ";
    resetColor();
    cin >> choice;
    clearInput();

    switch (choice)
    { // NOTE: if we declare new variables inside a case we should add {} for all case
    case 1:
      currentProfessor->displayInfo();
      break;

    case 2:
    {
      Grades g;
      g.addGrade();
      waitEnter();
      break;
    }

    case 3:
    {
      int ID;
      string Subject;
      cout << "Enter Student ID: \n";
      cin >> ID;
      clearInput();
      cout << "Enter Grade: \n";
      getline(cin, Subject);
      Grades::editGrade(ID, Subject);
      waitEnter();
      break;
    }

    case 4:
    {
      int ID;
      string Subject;
      cout << "Enter Student ID: \n";
      cin >> ID;
      clearInput();
      cout << "Enter Grade: \n";
      getline(cin, Subject);
      Grades::deleteGrade(ID, Subject);
      waitEnter();
      break;
    }

    case 5:
      cout << "Logging out!\n";
      break;

    default:
      cout << "Invalid choice!Try again\n";
    }

  } while (choice != 5);
}

void SuperiorMenu(const vector<Professor> &professors, vector<Student> &students) { 
    clearScreen();
    setColor(10); // green
    typeWriter("===== SuperiorMenu =====\n", 15);
    resetColor();

    typeWriter("1. View child's grades\n2. Contact professors\n", 15);

    int choice;
    if (!(cin >> choice)) { // prevent crash on invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        waitEnter();
        return;
    }

    switch (choice) {
        case 1: {
            int childID;
            cout << "Enter child's ID: ";
            if (!(cin >> childID)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID!\n";
                waitEnter();
                break;
            }

            bool found = false;
            for (auto &st : students) {
                if (st.getID() == childID) {
                    st.displayGrade();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Student not found!\n";
            }
            waitEnter();
            break;
        }
        case 2:
            cout << "Contacting professors...\n";
            for (const auto &prof : professors) {
                cout << "- " << prof.getFullName() << " (" << prof.getEmail() << ")\n";
            }
            waitEnter();
            break;
        default:
            cout << "Invalid choice.\n";
            waitEnter();
            break;
    }
}


int main()
{
  vector<Student> students;
  vector<Professor> profs;
  vector<Superior> sup;

  clearScreen();
    setColor(11); // Light Aqua
    typeWriter("===== WELCOME TO SCHOOL MANAGEMENT SYSTEM =====\n", 15);
    resetColor();
    loadingAnimation("Initializing system", 5, 200);

    std::this_thread::sleep_for(std::chrono::seconds(1));

  loadStudentsFromFile(students);
  loadAllProfessorsFromFile(profs);

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
  for (auto &c : role)
    c = tolower(c); // everything wil be in lowercase
  if (role == "admin")
    adminMenu(students, profs, sup);
  else if (role == "student")
    StudentMenu(ProfID, students);
  else if (role == "professor")
    ProfessorMenu(ProfID, profs, students);
    else if (role == "superior")
    SuperiorMenu(profs, students);
  else
    cout << "Unkown Role!...\n";

  return 0;
}
