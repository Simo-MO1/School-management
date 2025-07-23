#ifndef grade_h
#define grade_h
#include<iostream>
#include<string>

class Grades{
    private:
    std::string Subject;
    float Score;

    public:
    Grades(const std::string& subject, float score);
    std:: string getSubject() const {return Subject;}
    float getScore() const {return Score;}
};
#endif