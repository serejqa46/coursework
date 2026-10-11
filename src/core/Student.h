#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <iostream>
#include <string>


using namespace std;

class Student : public User {
private:
    int solvedTaskCount;
    double rating;
public:
    Student(int id, const string& login, const string& passwordHash, int solvedTaskCount = 0, double rating = 0.0);

    void printInfo() const override;

    bool operator<(const Student& otherStudent) const;

    bool operator>(const Student& otherStudent) const;

    Student& operator+=(double points);

    Student& operator-=(double penalty);
};




#endif //STUDENT_H
