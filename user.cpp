#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

User::User() {}
User::User(int i, std::string p, std::string r) : ID(i), Password(p), Role(r) {}

int User::getID() const { return ID; }
string User::getPassword() const { return Password; }
string User::getRole() const { return Role; } 

bool User::authenticate(int inputID, const string &inputPass, string &outRole)
{
  ifstream file("users.txt");
  if (!file.is_open())
  {
    cerr << "Error: users.txt not found or could not be opened.\n";
    return false;
  }

  string line;
  while (getline(file, line))
  {
    stringstream ss(line);
    string IDstr, passw, rol;

    if (getline(ss, IDstr, ',') &&
        getline(ss, passw, ',') &&
        getline(ss, rol, ','))
    {

      int fileID=stoi(IDstr);
      if (fileID == inputID && passw == inputPass)
      {
        outRole = rol; //this need to be clarified too
        file.close(); // Close file as soon as authenticated
        return true;
      }
    }
    else
    {
      cerr << "Skipping malformed line in users.txt: " << line << endl;
    }
  }
  file.close();
  return false;
}

void User:: registerUser(){
   string ID, Password, Role;
   cout<<"enter your ID: "; cin>>ID;
   cout<<"enter your password: "; cin>>Password;
   cout<<"enter your role('admin', 'student', 'professor')"; cin>>Role;

   ofstream outFile("users.txt",ios::app);
    if(outFile.is_open()){
      outFile<<ID<<","<<Password<<","<<Role<<"\n";
      outFile.close();
      cout<<"you've been registered succesfully\n";
    }

    if(Role=="professor"){
      int ID;
      string Subject;
      cout<<"Enter your ID:\n";
      cin>>ID;
      cout<<"Enter your Subject:\n";
      cin.ignore();
      getline(cin,Subject);

      ofstream pFile("professor.txt, ios::app");
      if(pFile.is_open()){
        pFile<<ID<<","<<Subject<<endl;
        pFile.close();
        cout<<"Data saved successefully!"<<endl;
      } else{cerr<<"could not open the file!";}
    }
}
