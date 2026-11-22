#include "Exception.h"


SystemException::SystemException(std::string errorMessage, int errorCode)
    : message(errorMessage), code(errorCode) {}

const char* SystemException::what() const noexcept {
    return message.c_str();
}

int SystemException::getErrorCode() const noexcept {
    return code;
}

SystemException SystemException::invalidTestCount(int count) {
    return SystemException(
        "Invalid test count: " + std::to_string(count) + " (must be non-negative)",
        NegativeTestCount
    );
}

SystemException SystemException::outOfRange(int index, int size) {
    return SystemException(
        "Index out of range: " + std::to_string(index) + " (size: " + std::to_string(size) + ")",
        OutOfRange
    );
}

SystemException SystemException::fileOpenError(const std::string& path, bool forWriting) {
    const std::string mode = forWriting ? "writing" : "reading";
    const int errCode = forWriting ? FileOpenWriteErr : FileOpenReadErr;
    return SystemException(
        "Failed to open file for " + mode + ": " + path,
        errCode
    );
}

SystemException SystemException::corruptedPackage(const std::string& details) {
    return SystemException(
        "Corrupted task package: " + details,
        CorruptedPackage
    );
}