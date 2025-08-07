#ifndef grade_h
#define grade_h
#include <string>
#include <vector>

class Grades
{
private:
    int ID;
    std::string Subject;
    std::vector<float> Scores;

public:
    Grades() {}
    Grades(const int &ID, const std::string &subject, const std::vector<float> &scores);
    int getID() const;
    std::string getSubject() const;
    std::vector<float> getScores() const;
    void addGrade();
    void displayGrades() const;
    void saveGradesToFile() const;
    static std::vector<Grades> loadGradesFromFile(int gID);
    void loadGradesForStudent(int ID);
    static void editGrade(int ID, const std::string &Subject);
    static void deleteGrade(int ID, const std::string &Subject);
};
#endif