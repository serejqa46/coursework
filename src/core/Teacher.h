#ifndef TEACHER_H
#define TEACHER_H
#include "User.h"
#include <string>

class Teacher : public User {
private:
    std::string department;
    int createdTasks;
public:
    Teacher(int id, const std::string& login, const std::string& passwordHash,
        const std::string& department, int createdTasks = 0);

    void printInfo() const override;
};


#endif //TEACHER_H
