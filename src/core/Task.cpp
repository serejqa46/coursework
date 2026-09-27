#include "Task.h"
#include <iostream>

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

// Перегрузка
Task& Task::operator=(const Task& other) {
    if (this == &other) {
        return *this;
    }
    delete[] tests;
    title = other.title;
    timeLimit = other.timeLimit;
    testCount = other.testCount;

    if (testCount > 0) {
        tests = new string[testCount];
        for (int i = 0; i < testCount; ++i) {
            tests[i] = other.tests[i];
        }
    } else {
        tests = nullptr;
    }
    return *this;
}

string& Task::operator[](int index){
    return tests[index];
}

const string& Task::operator[](int index) const {
    return tests[index];
}

ostream& operator<<(ostream& os, const Task& task) {
    os << "== Задача: " << task.title << " ===" << endl;
    os << "=== Ограничение по времени: " << task.timeLimit << " ms" << endl;
    os << "=== Количество тестов: " << task.testCount << " tests" << endl;

    if (task.testCount == 0 && task.tests != nullptr) {
        os << "Тесты:" << endl;
        for (int i = 0; i < task.testCount; ++i) {
            os << " Тест #" << i + 1 << ": " << task.tests[i] << endl;
        }
    } else {
        os << "Тесты отсутствуют" << endl;
    }
    return os;
}

bool Task::operator==(const Task& other) const {
    if (title != other.title || timeLimit != other.timeLimit || testCount != other.testCount) {
        return false;
    }
    for (int i = 0; i < testCount; ++i) {
        if (tests[i] != other.tests[i]) {
            return false;
        }
    }
    return true;
}

bool Task::operator!=(const Task& other) const {
    return !(*this == other);
}