#ifndef professor_h
#define professor_h
#include<string>
using namespace std;

class Professor{
    private:
     int ID, Age, Salary;
     string First_Name, Last_Name, Speciality;
     
     public:
     Professor();
     Professor(int ID, int Age, string First_Name, string Last_Name, string Speciality, float Salary);
     
     void displayInfo() const;
     int getID() const;
     string getFullName() const;
     void saveToFile() const;
};
#endif