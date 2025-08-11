#ifndef professor_h
#define professor_h
#include <string>

// It's generally better to avoid 'using namespace std;' in headers.
// Qualify names with std:: or put 'using namespace std;' in .cpp files.
// using namespace std; // Removed from header

class Professor
{
private:
  int ID, Age;
  float Salary; 
  std::string First_Name, Last_Name, Speciality,Email; 

public:
  Professor();
  Professor(int ID, int Age, std::string First_Name, std::string Last_Name, std::string Speciality, float Salary, std::string Email);

  void displayInfo() const;
  int getID() const;
  std::string getFullName() const;
  void saveToFile() const;
  void addGrade();
  std::string getEmail() const;
};
#endif
