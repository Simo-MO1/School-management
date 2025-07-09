#ifndef user_h
#define user_h
#include<string>
using namespace std;

class User{
  private:
  string Username, Password, Role;

  public:
  User();
  User(string usern, string passw, string rol);

  string getUsername()const;
  string getPassword()const;
  string getRole()const;
  
  static bool authenticate(const string& inputUser, const string& inputPass,  string& outRole);
};
#endif