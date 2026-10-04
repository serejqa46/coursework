#include "Student.h"
#include <iostream>

Student::Student(int id, const string &login, const string &passwordHash, int solvedTaskCount, double rating)
    : User(id, login, passwordHash), solvedTaskCount(solvedTaskCount), rating(rating) {}

void Student::printInfo() const {
    User::printInfo();
    std::cout << " | Solved tasks: " << solvedTaskCount << " | Rating: " << rating << std::endl;
}