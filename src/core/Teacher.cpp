#include "Teacher.h"
#include <iostream>

Teacher::Teacher(int id, const std::string& login, const std::string& passwordHash,
        const std::string& department, int createdTasks)
   : User(id, login, passwordHash), department(department), createdTasks(createdTasks) {}

void Teacher::printInfo() const {
        User::printInfo();
        std::cout << " | department " << department << " | createdTasks: " << createdTasks << std::endl;
}