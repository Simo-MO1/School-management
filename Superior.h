#ifndef superior_h
#define superior_h
#include "grade.h"
#include "Student.h"
#include<string>

class Superior{
    private:
    std::string Fi_Name, La_Name, Email, Phone_Number;
    int ID;

    public:
    Superior();
    Superior(int ID, std::string Fi_Name, std::string La_Name,std::string Email, std::string Phone_Number);
    
    int getID() const;
    std::string getFullName() const;
    std::string getEmail() const;
    std::string getPhNumber() const;
    void displayInfo() const;
    void saveToFile() const;
    void contactProfessors();
};
#endif