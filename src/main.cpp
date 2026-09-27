#include <iostream>
#include "core/Task.h"

using namespace std;

int main() {
    system("chcp 1251");

    cout << "=== 1. Конструктор по умолчанию (на стеке) ===" << endl;
    Task t1;
    t1.printInfo();

    cout << "\n=== 2. Конструктор с параметрами (на стеке) ===" << endl;
    Task t2("A + B Problem", 1000, 2);
    t2.setTest(0, "1 2 -> 3");
    t2.setTest(1, "10 20 -> 30");
    t2.printInfo();

    cout << "\n=== 3. Конструктор копирования ===" << endl;
    Task t3 = t2;
    t3.printInfo();

    cout << "\n=== 4. Динамический объект (в куче) ===" << endl;
    Task* t4 = new Task("Matrix Search", 2000, 1);
    t4->setTest(0, "3x3 matrix input");
    t4->printInfo();
    delete t4; // Явное разрушение объекта

    cout << "\n=== 5. Ссылка на объект ===" << endl;
    Task& ref_t2 = t2;
    ref_t2.setTest(0, "UPDATED TEST: 5 5 -> 10");
    cout << "Проверяем t2 после изменения через ссылку:" << endl;
    t2.printInfo();

    cout << "\n=== 6. Массив объектов на стеке ===" << endl;
    Task taskArray[2] = {
        Task("Task #1", 500, 1),
        Task()
    };
    taskArray[0].printInfo();

    return 0;
}