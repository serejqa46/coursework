#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>


class SystemException : public std::exception {
public:
    enum ErrorCode {
        // 1xx: Ошибки данных, параметров и индексов
        InvalidArgument = 101,
        OutOfRange = 102,
        NegativeTestCount = 103,

        // 2xx: Ошибки файловой системы и работы с файлами
        DirectoryCreateErr = 201,
        FileOpenReadErr = 202,
        FileOpenWriteErr = 203,
        FileReadErr = 204,
        FileWriteErr = 205,

        // 3xx: Ошибки формата и целостности файлов-пакетов
        InvalidPackageSig = 301,
        CorruptedPackage = 302,

        // 9xx: прочее
        UnknownSystemError = 999
    };

private:
    std::string message;
    int code;


public:
    SystemException(std::string& errorMessage, int errorCode);

    SystemException(std::string errorMessage, int errorCode);

    const char* what() const noexcept override;
    int getErrorCode() const noexcept;

    static SystemException invalidTestCount(int count);
    static SystemException outOfRange(int index, int size);
    static SystemException fileOpenError(const std::string& path, bool forWriting);
    static SystemException corruptedPackage(const std::string& details);
};

#endif //EXCEPTION_H