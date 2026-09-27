#include "Task.h"

// 1. Конструктор по умолчанию
Task::Task() : title("Untitled Task"), timeLimit(1000), testCount(0), tests(nullptr) {}

// 2. Конструктор с параметрами (с использованием списка инициализации)
Task::Task(string title, int timeLimit, int testCount)
    : title(title), timeLimit(timeLimit), testCount(testCount) {
    if (testCount > 0) {
        tests = new string[testCount];
    } else {
        tests = nullptr;
    }
}

// 3. Конструктор копирования
Task::Task(const Task& other)
    : title(other.title), timeLimit(other.timeLimit), testCount(other.testCount) {
    if (testCount > 0) {
        tests = new string[testCount];
        for (int i = 0; i < testCount; ++i) {
            tests[i] = other.tests[i];
        }
    } else {
        tests = nullptr;
    }
}

// 4. Деструктор
Task::~Task() {
    delete[] tests;
}

// Методы
void Task::setTest(int index, const string& testData) {
    if (index >= 0 && index < testCount && tests != nullptr) {
        tests[index] = testData;
    }
}

void Task::printInfo() const {
    cout << "Task: " << title << " | TL: " << timeLimit << "ms" << endl;
    cout << "Tests count: " << testCount << endl;
    for (int i = 0; i < testCount; ++i) {
        cout << "  Test #" << i + 1 << ": " << tests[i] << endl;
    }
}