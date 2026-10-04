#include "User.h"
#include <iostream>

User::User(int id, std::string login, std::string passwordHash)
    : id(id), login(login), passwordHash(passwordHash) {}


void User::printInfo() const {
    std::cout << "ID: " << id << " | Login: " << login;
}