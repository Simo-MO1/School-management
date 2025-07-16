#include "grade.h"
#include<iostream>
#include<fstream>

Grades::Grades(const std::string& subject, float score):Subject(subject),Score(score){}
std::string Grades::getSubject() const{return Subject;}
float Grades::getScore() const{return Score;}