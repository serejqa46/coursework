#ifndef FIELAMANGER_H
#define FIELAMANGER_H

#include "Task.h"
#include <filesystem>
#include <string>
#include <vector>

class FileManager {
private:
    std::filesystem::path tasksDir;
    std::filesystem::path exportsDir;
public:
    explicit FileManager(const std::string& tasksDir = "data/tasks",
                         const std::string& exportsDir = "data/exports");

    void saveTask (const Task& task) const;
    std::vector<Task> loadAllTasks() const;

    void exportTask (const Task& task, const std::string& packageName) const;
    Task importTask (const std::string& packagePath) const;
};


#endif