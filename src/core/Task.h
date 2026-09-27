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

    //перегрузка
    Task& operator=(const Task& other);

    string& operator[](int index);

    const string& operator[](int index) const;

    friend ostream& operator<<(ostream& os, const Task& task);

    bool operator==(const Task& other) const;

    bool operator!=(const Task& other) const;
};

#endif //TASK_H