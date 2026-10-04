#ifndef USER_H
#define USER_H
#include <string>


class User {
protected:
    int id;
    std::string login;
    std::string passwordHash;
public:
    User(int id, std::string login, std::string passwordHash);

    virtual ~User() = default;

    virtual void printInfo() const;
};



#endif //USER_H
