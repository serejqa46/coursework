#include "Exception.h"


SystemException::SystemException(std::string errorMessage, int errorCode)
    : message(errorMessage), code(errorCode) {}

const char* SystemException::what() const noexcept {
    return message.c_str();
}

int SystemException::getErrorCode() const noexcept {
    return code;
}

