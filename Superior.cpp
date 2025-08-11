#include "grade.h"
#include "Student.h"
#include "Superior.h"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

Superior::Superior() {};
Superior::Superior(int id, string fname, string lname,string email, string Pnumber): ID(id),  Fi_Name(fname),  La_Name(lname), Email(email), Phone_Number(Pnumber) {}

void Superior::displayInfo()const{
  cout << "ID: " << ID << "\nName: " << Fi_Name << " " << La_Name << "\nEmail: " << Email << " Phone number " << Phone_Number<<endl;
}

int Superior::getID() const{
    return ID;
}
string Superior::getFullName()const{
    return Fi_Name + La_Name;
}

string Superior::getEmail() const{
    return Email;
}

string Superior::getPhNumber()const{
    return Phone_Number;
}

void Superior::saveToFile() const{
    ofstream outFile("parents.txt");
    if(outFile.is_open()){
        outFile << "ID: " << ID << "\nName: " << Fi_Name << " " << La_Name << "\nEmail: " << Email << " Phone number " << Phone_Number<<endl;
        outFile.close();
    }else
  {
    cerr << "Unable to open students.txt for writing!!\n";
  }
}