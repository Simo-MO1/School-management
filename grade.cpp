#include "grade.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>

Grades::Grades() {}
Grades::Grades(const int &id, const std::string &subject, const std::vector<float> &scores) : ID(id), Subject(subject), Scores(scores) {}
int Grades::getID() const { return ID; }
std::string Grades::getSubject() const { return Subject; }
std::vector<float> Grades::getScores() const { return Scores; }

void Grades::addGrade()
{

  std::cout << "\n Enter student's ID:\n";
  std::cin >> ID;

  std::cout << "\Enter the subject:\n";
  std::cin.ignore();
  std::getline(std::cin, Subject);

  Scores.clear();
  std::cout << "How many grades do you want to enter?\n";
  int count;
  std::cin >> count;

  std::cout << "\nEnter his/her grades:\n";
  for (int i = 0; i < count; ++i)
  {
    float score;
    std::cin >> score;
    Scores.push_back(score);
  }

  saveGradesToFile();
  std::cout << "Grades saved successfully!\n";
}

void Grades::saveGradesToFile() const
{
  std::ofstream out("grades.txt", std::ios::app);
  if (out.is_open())
  {
    out << ID << ", " << Subject;
    for (float score : Scores)
    {
      out << "," << score;
    }
    out << "\n";
    out.close();
  }
  else
  {
    std::cerr << "Unable to open the file!\n";
  }
}

void Grades::displayGrades() const
{
  if (Scores.empty())
  {
    std::cout << "No grade available yet!\n";
    return;
  }
  std::cout << "\n--- Grades Details ---\n";
  std::cout << std::left << std::setw(15) << "Student ID:" << ID << "\n";
  std::cout << std::left << std::setw(15) << "Subject:" << Subject << "\n";
  std::cout << std::left << std::setw(15) << "Scores:";

  for (size_t i = 0; i < Scores.size(); ++i)
  {
    std::cout << Scores[i];
    if (i < Scores.size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << "\n"; 
  std::cout << "----------------------\n";
}

std::vector<Grades> Grades::loadGradesFromFile(int gID)
{
  std::ifstream file("grades.txt");
  std::vector<Grades> result;
  if (!file.is_open())
  {
    std::cerr << "Error: Could not open grades.txt for reading!";
    return result; //why return result here
  }
  // static functions don’t have access to this pointer. They operate at class level, not instance level.
  std::string line;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string idstr, subjectstr, markstr;
    std::getline(ss, idstr, ',');
    std::getline(ss, subjectstr, ',');

    if(!std::getline(ss,idstr,','))continue; // Handle empty line or missing ID (need to be clarified)
    int curentID = std::stoi(idstr);

    std::vector<float> currentScores;  // Local vector for scores
    while (std::getline(ss, markstr, ',')) //why??
    {
      try
      {
        currentScores.push_back(std::stof(markstr));
      }
      catch (const std::invalid_argument &e)
      {
        std::cerr << "Error! invalid score found in line"<<line<<"Details: "<<e.what() << std::endl;
      }
    }
    result.push_back(Grades(curentID, subjectstr, currentScores));
  }

  file.close();
  return result; // why??
}

void Grades::editGrade(int ID, const std::string& Subject){
    std:: ifstream ginFile("grades.txt");
    std:: vector<Grades>allGrades; //why this
    std:: string line;

    if(!ginFile.is_open()){
      std::cerr<<"ERROR! Unable to open the file\n";
      return;
    }

    while(std::getline(ginFile, line)){
      std:: stringstream ss(line);
      std:: string idStr, subtStr, markStr;

      std::getline(ss, idStr, ',');
      std::getline(ss, subtStr, ',');

      int ID = stoi(idStr); //why we do this

      std::vector<float>scores;

      while(getline(ss, markStr, ',')){ //why this 
        try{
          scores.push_back(stof(markStr)); //whyyyy how could it modified it, while just adding extra instance
        } catch(const std:: invalid_argument &e){std::cerr<<"Error! in line: "<<line<<e.what();}
      }
      allGrades.push_back(Grades(ID, Subject, scores)); //whyyyyyy no idea
    }
    ginFile.close();

    bool found=false; //need to be clarified
    for(Grades& g: allGrades){
      if(g.getID()==ID && g.getSubject()==Subject){
        found=true;
        std::cout<<"Editing the grades for subject: '"<<Subject<<"'.\n";
        std::cout<<"how many new grades?\n";
        int count;
        std::cin>>count;

        std::vector<float>newScores; //why another vector
        std::cout<<"Enter the new grade: \n";

        for(int i=0;i<count;++i){
          float score;
          std::cin>>score;
          newScores.push_back(score); //need to be clarifieeed
        }
        g=Grades(ID, Subject, newScores); //this one too
        break;
      }
    }
    if(!found){
      std::cout<<"No grade found for the entered ID: "<<ID<<"and subject: "<<Subject<<std::endl;
    }

    std::ofstream goutFile("grades.txt");
    for(const Grades& g: allGrades){     //this one too need to be clarified
      goutFile<<g.getID()<<","<<g.getSubject();
      for(float score: g.getScores())
        goutFile<<","<<score;
      goutFile.close();
    }

    std::cout<<"Grades updated successfully!\n";
}

void Grades::deleteGrade(int studentID, const std::string& Subject){
  std:: ifstream ginFile("grades.txt");
    std:: vector<Grades>allGrades; 
    std:: string line;

    if(!ginFile.is_open()){
      std::cerr<<"ERROR! Unable to open the file\n";
      return;
    }

while(std::getline(ginFile, line)){
      std:: stringstream ss(line);
      std:: string idStr, subtStr, markStr;

      std::getline(ss, idStr, ',');
      std::getline(ss, subtStr, ',');

      int ID = stoi(idStr); //why we do this

      std::vector<float>scores; //why another vector

      while(getline(ss, markStr, ',')){ //why this 
        try{
          scores.push_back(stof(markStr)); //whyyyy how could it modified it, while just adding extra instance
        } catch(const std:: invalid_argument &e){std::cerr<<"Error! in line: "<<line<<e.what();}
      }
    
      if(!(ID==studentID && subtStr==Subject)){
        allGrades.push_back(Grades(ID, Subject, scores)); //only grades that aren't entered will not be delete it or what?
      }
}
ginFile.close();

std::ofstream goutFile("grades.txt");
 for(const Grades& g: allGrades){     //this one too need to be clarified
      goutFile<<g.getID()<<","<<g.getSubject();
      for(float score: g.getScores())
        goutFile<<","<<score;
      goutFile.close();
    }

 std::cout<<"Grades deleted successfully1\n";
}