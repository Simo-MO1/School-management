#include "user.h"
#include<iostream>
#include <fstream>
#include <sstream>
using namespace std;

User::User() {}
User::User(std::string u, std::string p, std::string r) : Username(u), Password(p), Role(r) {}

string User::getUsername() const { return Username; }
string User::getPassword() const { return Password; }
string User::getRole() const { return Role; }

bool User::authenticate(const string& inputUser, const string& inputPass,  string& outRole) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string usern, passw, rol;
        getline(ss, usern, ',');
        getline(ss, passw, ',');
        getline(ss, rol, ',');

        if (usern == inputUser && passw == inputPass) {
            outRole = rol;
            return true;
        }
    }
    return false;
}