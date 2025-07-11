#ifndef user_h
#define user_h
#include <string>

class User
{
private:
  std::string Username, Password, Role; 

public:
  User();
  User(std::string usern, std::string passw, std::string rol); 

  std::string getUsername() const;
  std::string getPassword() const; 
  std::string getRole() const;     

  static bool authenticate(const std::string &inputUser, const std::string &inputPass, std::string &outRole);
  static void registerMenu(); 
};
#endif
