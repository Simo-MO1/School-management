#include "grade.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

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
    if (line.empty()) continue;
    std::stringstream ss(line);
    std::string idstr, subjectstr, markstr;

    if (!std::getline(ss, idstr, ',')) continue;
    if (!std::getline(ss, subjectstr, ',')) continue;

    int currentID;
        try {
            currentID = std::stoi(idstr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid ID '" << idstr << "' in grades.txt. Skipping line.\n";
            continue;
        }

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
    result.push_back(Grades(currentID, subjectstr, currentScores));
  }

  file.close();
  return result; // why??
}
// This function overwrites the grades.txt file with a new set of grades.
// It's a helper function for edit and delete operations.
static void saveAllGrades(const std::vector<Grades>& allGrades) {
    // Open with std::ios::trunc to clear the file before writing
    std::ofstream outFile("grades.txt", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "ERROR! Unable to open grades.txt for writing!\n";
        return;
    }
    for (const auto& grade : allGrades) {
        outFile << grade.getID() << "," << grade.getSubject();
        for (float score : grade.getScores()) {
            outFile << "," << score;
        }
        outFile << "\n";
    }
    outFile.close();
}


void Grades::loadGradesForStudent(int studentID) {
    this->ID = studentID; // Set the ID for the current object
    this->Scores.clear(); // Clear any previous scores
    this->Subject = "";   // Reset subject

    std::vector<Grades> allGrades = loadGradesFromFile(studentID);
    for (const auto& grade : allGrades) {
        if (grade.getID() == studentID) {
            // Found the grades for our student, copy them over
            this->Subject = grade.getSubject();
            this->Scores = grade.getScores();
            return;
        }
    }
}

void Grades::editGrade(int studentID, const std::string& subjectToEdit) {
    // find the one line to change, modify it in memory, and then write the entire updated list back to the file.
    std::vector<Grades> allGrades = loadGradesFromFile(studentID);
    bool found = false;

    for (Grades& g : allGrades) {
        if (g.getID() == studentID && g.getSubject() == subjectToEdit) {
            found = true;
            std::cout << "Editing grades for student " << studentID << " in '" << subjectToEdit << "'.\n";
            std::cout << "How many new grades do you want to enter?\n";
            int count;
            std::cin >> count;

            //  `newScores` is a temporary vector to hold the new grades
            std::vector<float> newScores;
            std::cout << "Enter the new grades:\n";
            for (int i = 0; i < count; ++i) {
                float score;
                std::cin >> score;
                newScores.push_back(score);
            }
            // This line replaces the old grade object in the `allGrades` vector with a new one containing the updated scores.
            g = Grades(studentID, subjectToEdit, newScores);
            break; // Exit loop once found and edited
        }
    }

    if (!found) {
        std::cout << "No grade entry found for ID: " << studentID << " and subject: " << subjectToEdit << std::endl;
    } else {
        // This loop writes the entire, now-modified, `allGrades` vector back to the file, overwriting the old content.
        saveAllGrades(allGrades);
        std::cout << "Grades updated successfully!\n";
    }
}
void Grades::deleteGrade(int studentID, const std::string& subjectToDelete) {
    std::vector<Grades> allGrades = loadGradesFromFile(studentID);
    std::vector<Grades> modifiedGrades;
    bool found = false;

    for (const auto& g : allGrades) {
        // This `if` statement checks if the current grade is NOT the one we want to delete.
        // If it's not the one to delete, we add it to our new `remainingGrades` vector.
        if (!(g.getID() == studentID && g.getSubject() == subjectToDelete)) {
            modifiedGrades.push_back(g);
        } else {
            found = true; // We found the record to delete (and skip adding it)
        }
    }

    if (!found) {
        std::cout << "No grade entry found for ID: " << studentID << " and subject: " << subjectToDelete << " to delete.\n";
    } else {
        saveAllGrades(modifiedGrades);
        std::cout << "Grades deleted successfully!\n";
    }
}