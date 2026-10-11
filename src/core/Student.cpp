#include "Student.h"
#include <iostream>

Student::Student(int id, const string &login, const string &passwordHash, int solvedTaskCount, double rating)
    : User(id, login, passwordHash), solvedTaskCount(solvedTaskCount), rating(rating) {}

void Student::printInfo() const {
    User::printInfo();
    std::cout << " | Solved tasks: " << solvedTaskCount << " | Rating: " << rating << std::endl;
}

bool Student::operator<(const Student& otherStudent) const{
    return this->rating < otherStudent.rating;
};

bool Student::operator>(const Student& otherStudent) const{
    return this->rating > otherStudent.rating;
};

Student& Student::operator+=(double points) {
    this->rating += points;
    return *this;
}

Student& Student::operator-=(double penalty) {
    this->rating -= penalty;

    if (this->rating <= 0.0) {
        this->rating = 0.0;
    }

    return *this;
}