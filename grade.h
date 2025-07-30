#ifndef grade_h
#define grade_h
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

class Grades{
    private:
    int ID;
    std::string Subject;
    std::vector<int>Scores;

    public:
    Grades(){}
    Grades(const int& ID, const std::string& subject, const std::vector<int>& scores);
    int getID() const;
    std:: string getSubject() const;
    std:: vector<int> getScores() const;
    void displayGrades() const;
    void saveGradesToFile() const;
    static Grades loadGradesFromFile();
};
#endif