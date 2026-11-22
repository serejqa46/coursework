#include "Task.h"
#include "Exception.h"
#include <iostream>

// 1. Конструктор по умолчанию
Task::Task() : title("Untitled Task"), difficulty(1), points(10), timeLimit(1000), testCount(0),
        tests(nullptr), statement(""), examples(""), codeTemplate("") {}

// 2. Конструктор с параметрами (с использованием списка инициализации)
Task::Task(string title, int difficulty, int points, int timeLimit, int testCount, string statement, string examples, string codeTemplate)
    : title(title), difficulty(difficulty), points(points), timeLimit(timeLimit), testCount(testCount),
        tests(nullptr), statement(statement), examples(examples), codeTemplate(codeTemplate) {

    if (testCount < 0) {
        throw SystemException::invalidTestCount(testCount);
    }

    if (testCount > 0) {
        tests = new TestCase[testCount];
    } else {
        tests = nullptr;
    }
}

// 3. Конструктор копирования
Task::Task(const Task& other)
    : title(other.title), timeLimit(other.timeLimit), testCount(other.testCount), difficulty(other.difficulty),
        points(other.points), tests(nullptr), statement(other.statement), examples(other.examples), codeTemplate(other.codeTemplate) {
    if (testCount > 0) {
        tests = new TestCase[testCount];
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
void Task::setTest(int index, const string& input, const string& expectedOutput) {
    if (index < 0 || index >= testCount) {
        throw SystemException::outOfRange(index, testCount);
    }
    if (tests != nullptr) {
        tests[index].input = input;
        tests[index].expectedOutput = expectedOutput;
    }
}

void Task::printInfo() const {
    cout << "Task: " << title << " | TL: " << timeLimit << "ms" << endl;
    cout << "Tests count: " << testCount << endl;
    for (int i = 0; i < testCount; ++i) {
        cout << "  Test #" << i + 1
             << " | IN: " << tests[i].input
             << " | OUT: " << tests[i].expectedOutput << endl;
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
    difficulty = other.difficulty;
    points = other.points;
    statement = other.statement;
    examples = other.examples;
    codeTemplate = other.codeTemplate;

    if (testCount > 0) {
        tests = new TestCase[testCount];
        for (int i = 0; i < testCount; ++i) {
            tests[i] = other.tests[i];
        }
    } else {
        tests = nullptr;
    }
    return *this;
}

TestCase& Task::operator[](int index){
    if (index < 0 || index >= testCount) {
        throw SystemException::outOfRange(index, testCount);
    }

    return tests[index];
}

const TestCase& Task::operator[](int index) const {
    if (index < 0 || index >= testCount) {
        throw SystemException::outOfRange(index, testCount);
    }

    return tests[index];
}

ostream& operator<<(ostream& os, const Task& task) {
    os << "== Задача: " << task.title << " ===" << endl;
    os << "=== Ограничение по времени: " << task.timeLimit << " ms" << endl;
    os << "=== Количество тестов: " << task.testCount << " tests" << endl;

    if (task.testCount == 0 && task.tests != nullptr) {
        os << "Тесты:" << endl;
        for (int i = 0; i < task.testCount; ++i) {
            os << " Тест #" << i + 1
               << " [IN: " << task.tests[i].input
               << " | OUT: " << task.tests[i].expectedOutput << "]" << endl;
        }
    } else {
        os << "Тесты отсутствуют" << endl;
    }
    return os;
}

bool Task::operator==(const Task& other) const {
    if (title != other.title || timeLimit != other.timeLimit || testCount != other.testCount
        || difficulty != other.difficulty || points != other.points || statement != other.statement ||
        examples != other.examples || codeTemplate != other.codeTemplate) {
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

istream& operator>>(istream& is, Task& otherTask) {
    is >> otherTask.title >> otherTask.timeLimit >> otherTask.testCount >> otherTask.points >> otherTask.difficulty;

    delete[] otherTask.tests;

    if (otherTask.testCount > 0) {
        otherTask.tests = new TestCase[otherTask.testCount];
        for (int i = 0; i < otherTask.testCount; ++i) {
            is >> otherTask.tests[i].input >> otherTask.tests[i].expectedOutput;
        }
    }
    else {
        otherTask.tests = nullptr;
    }

    return is;
}

bool Task::operator<(const Task& otherTask) const {
    return this->difficulty < otherTask.difficulty;
}