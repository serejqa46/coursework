#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Task {
private:
	string title;
	int timeLimit;
	int testCount;
	string* tests;
public:
	Task() { title = "Untitled"; timeLimit = 1000; testCount = 0; tests = nullptr; }

	Task(string title, int timeLimit, int testCount) : 
		title(title), timeLimit(timeLimit), testCount(testCount) 
	{
		if (testCount > 0) {
			tests = new string[testCount];
		}
		else {
			tests = nullptr;
		}
	}

	Task(const Task& newbie) 
		: title(newbie.title), timeLimit(newbie.timeLimit), testCount(newbie.testCount)
	{
		if (testCount > 0) {
			tests = new string[testCount];
			for (int i = 0; i < testCount; ++i) {
				tests[i] = newbie.tests[i];
			}
		}
		else {
			tests = nullptr;
		}
	}

	~Task() {
		delete[] tests;
	}

	void setTest(int index, const string& testData) {
		if (index >= 0 && index < testCount) {
			tests[index] = testData;
		}
	}

	void printInfo() const {
		cout << "Task: " << title << " | TL: " << timeLimit << "ms" << endl;
		cout << "Tests count: " << testCount << endl;
		for (int i = 0; i < testCount; ++i) {
			cout << " Test #" << i + 1 << ": " << tests[i] << endl;
		}
	}
};

int main() {
	system("chcp 1251");

	cout << "Конструктор по умолчанию: " << endl;
	Task t1;
	t1.printInfo();

	cout << "Конструктор с параметрами: " << endl;
	Task t2("A + B", 1000, 3);
	t2.setTest(0, "1 2 -> 3");
	t2.setTest(1, "10 20 -> 30");
	t2.printInfo();

	cout << "Конструктор копирования" << endl;
	Task t3 = t2;
	t3.printInfo();

	cout << "Динамический объект" << endl;
	Task* t4 = new Task("Matrix", 2000, 1);
	t4->setTest(0, "3x3 matrix input");
	t4->printInfo();
	delete t4;

	cout << "Ссылка" << endl;
	Task& copy_t2 = t2;
	copy_t2.setTest(0, "updated test 5 5 -> 10");
	t2.printInfo();

	cout << "Массив объектов" << endl;
	Task taskArr[2] = { Task("Task #1", 500, 1), Task() };
	taskArr[0].printInfo();

	return 0;
}