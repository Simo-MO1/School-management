#ifndef user_h
#define user_h
#include <string>

class User
{
private:
  std::string Password, Role; 
  int ID;

public:
  User();
  User(int IDn, std::string passw, std::string rol); 

  int getID() const;
  std::string getPassword() const; 
  std::string getRole() const;     

  static bool authenticate(int inputID, const std::string &inputPass, std::string &outRole);
  static void registerUser();
};
#endif
