#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>


class SystemException : public std::exception {
private:
    std::string message;
    int code;
public:
    SystemException(std::string errorMessage, int errorCode);

    const char* what() const noexcept override;

    int getErrorCode() const noexcept;
};

#endif //EXCEPTION_H