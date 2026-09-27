#include <windows.h>
#include <iostream>
#include "core/Task.h"
#include <clocale>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 1. Создаем первый объект с 2 тестами
    Task task1("A + B Problem", 1000, 2);
    task1[0] = "1 2 -> 3";
    task1[1] = "10 20 -> 30";

    // 2. Создаем второй объект через конструктор копирования
    Task task2 = task1;

    // 3. Создаем третий объект через конструктор по умолчанию
    Task task3;

    // 4. Проверяем работу операторов сравнения
    cout << "--- Проверка сравнения ---" << endl;
    if (task1 == task2) {
        cout << "task1 и task2 равны (конструктор копирования сработал верно)" << endl;
    } else {
        cout << " Ошибка: task1 и task2 не равны" << endl;
    }

    if (task1 != task3) {
        cout << "task1 и task3 не равны (все верно)" << endl;
    }

    // 5. Выводим содержимое task1
    cout << "\n--- Информация о task1 ---" << endl;
    cout << task1;

    return 0; // В этот момент вызываются деструкторы для task3, task2, task1!
}