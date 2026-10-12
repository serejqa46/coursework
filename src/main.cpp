#include <vector>
#include <windows.h>
#include <iostream>
#include "core/Task.h"
#include "core/Teacher.h"
#include "core/Student.h"
#include "Exception.h"
#include <clocale>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    try {
        cout << "1. Попытка сделать задачу с неверным ограничением по времени..." << endl;
        Task badTask("Bad Task", -500, 3, -10, 1);
    }
    catch (const SystemException& e) {
        cout << "[Поймана SystemException #" << e.getErrorCode() << "] " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "[Поймана standart exception]: " << e.what() << endl;
    }

    try {
        cout << "\n2. Попытка обратиться к несуществующему индексу [4]..." << endl;
        Task normalTask ("Normal Task", 1000, 2, 20, 2);
        cout << normalTask[5] << endl;
    }
    catch (const SystemException& e) {
        cout << "[Поймана SystemException #" << e.getErrorCode() << "] " << e.what() << endl;
    }

    cout << "Программа завершена без ошибок!" << endl;

    return 0;
}