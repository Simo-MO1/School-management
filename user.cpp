#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

User::User() {}
User::User(std::string u, std::string p, std::string r) : Username(u), Password(p), Role(r) {}

string User::getUsername() const { return Username; }
string User::getPassword() const { return Password; }
string User::getRole() const { return Role; }

bool User::authenticate(const string &inputUser, const string &inputPass, string &outRole)
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
    string usern, passw, rol;

    if (getline(ss, usern, ',') &&
        getline(ss, passw, ',') &&
        getline(ss, rol, ','))
    {
      if (usern == inputUser && passw == inputPass)
      {
        outRole = rol;
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
   string Username, Password, Role;
   cout<<"enter your username: "; cin>>Username;
   cout<<"enter your password: "; cin>>Password;
   cout<<"enter your role('admin', 'student', 'professor')"; cin>>Role;

   ofstream outFile("users.txt",ios::app);
    if(outFile.is_open()){
      outFile<<Username<<","<<Password<<","<<Role<<"\n";
      outFile.close();
      cout<<"you've been registered succesfully\n";
    }
   
}
