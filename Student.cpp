#include "Student.h"
#include<iostream>
#include<fstream>
using namespace std;

Student::Student(){}
Student::Student(int id, int age, string first, string last, string BirthP, string BirthD, string sex, string nat):ID(id),First_Name(first),Last_Name(last),Age(age),Birth_Place(BirthP),Birth_Date(BirthD),Sex(sex),Nationality(nat){}

void Student::displayInfo()const{
    cout<<"ID: "<<ID<<"\n Age: "<<Age<<"\nName: "<<First_Name<<" , "<<Last_Name<<"\nBirth Information: "<<Birth_Date<<"in"<<Birth_Place<<"\nSex: "<<Sex<<"\nNationality: "<<Nationality;
}

int Student::getID()const{
    return ID;
}

string Student::getFullName()const{
    return First_Name+ ","+ Last_Name;
}

void Student::saveToFile()const{
    ofstream out("students.txt", ios::app);
    if(out.is_open()){
       out<<ID<<","<<Age<<","<<First_Name<<","<<Last_Name<<","<<Birth_Place<<","<<Birth_Date<<","<<Sex<<","<<Nationality<<endl;
       out.close();
    }else{cerr<<"Unable to open this file!!\n";}
}


