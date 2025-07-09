#ifndef student_h
#define student_h
#include<string>
using namespace std;

class Student{
    private:
    int ID, Age;
    string First_Name, Last_Name, Sex, Birth_Place, Birth_Date, Nationality;

    public:
    Student();
    Student(int ID, int Age, string First_Name, string Last_Name, string Sex, string Birth_Place, string Birth_Date, string Nationality);

    void displayInfo() const;
    int getID() const;
    string getFullName() const;
    void saveToFile() const;
};

#endif