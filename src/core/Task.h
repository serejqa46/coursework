#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

using namespace std;

class Task {
private:
    string title;
    int timeLimit;
    int testCount;
    string* tests;

public:
    // конструктор по умолчанию
    Task();

    // конструктор с параметрами
    Task(string title, int timeLimit, int testCount);

    //конструктор копирования
    Task(const Task& other);

    //деструктор
    ~Task();

    //вспомогательные методы

    void setTest(int index, const string& testData);
    void printInfo() const;
};

#endif //TASK_H