#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

using namespace std;

struct TestCase {
    string input;
    string expectedOutput;

    bool operator==(const TestCase& other) const {
        return input == other.input && expectedOutput == other.expectedOutput;
    }

    bool operator!=(const TestCase& other) const {
        return !(*this == other);
    }
};


class Task {
private:
    string title;
    int timeLimit;
    int testCount;
    int difficulty;
    int points;
    TestCase* tests;
    string statement;
    string examples;
    string codeTemplate;

public:
    // конструктор по умолчанию
    Task();

    // конструктор с параметрами
    Task(string title, int difficulty, int points, int timeLimit, int testCount,
        string statement = "", string examples = "", string codeTemplate = "");

    //конструктор копирования
    Task(const Task& other);

    //деструктор
    ~Task();

    //вспомогательные методы
    void setTest(int index, const string& input, const string& expectedOutput);
    void printInfo() const;

    //перегрузка
    Task& operator=(const Task& other);
    TestCase& operator[](int index);
    const TestCase& operator[](int index) const;
    friend ostream& operator<<(ostream& os, const Task& task);
    friend istream& operator>>(istream& is, Task& otherTask);
    bool operator<(const Task& Task) const;
    bool operator==(const Task& other) const;
    bool operator!=(const Task& other) const;

    // getter's
    const string& getTitle()const { return title; }
    int getTimeLimit()const { return timeLimit; }
    int getTestCount()const { return testCount; }
    int getDifficulty()const { return difficulty; }
    int getPoints()const { return points; }
    const string& getStatement() const { return statement; }
    const string& getExamples() const { return examples; }
    const string& getCodeTemplate() const { return codeTemplate; }

    // setter's
    void setTitle(const string& newTitle) { title = newTitle; }
    void setTimeLimit(int newTimeLimit) { timeLimit = newTimeLimit; }
    void setDifficulty(int newDifficulty) { difficulty = newDifficulty; }
    void setPoints(int newPoints) { points = newPoints; }
    void setStatement(const string& newStatement) { statement = newStatement; }
    void setExamples(const string& newExamples) { examples = newExamples; }
    void setCodeTemplate(const string& newCodeTemplate) { codeTemplate = newCodeTemplate; }
};

#endif //TASK_H