#include "FileManager.h"
#include "Exception.h"
#include <fstream>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

FileManager::FileManager(const std::string& tasksDir, const std::string& exportsDir)
        : tasksDir(tasksDir), exportsDir(exportsDir) {}

void FileManager::saveTask(const Task &task) const {
        if (task.getTestCount() < 0) {
                throw SystemException::invalidTestCount(task.getTestCount());
        }

        std::error_code ec;
        fs::create_directories(tasksDir, ec);
        if (ec) {
                throw SystemException("Ошибка при создании директории задач '" + tasksDir.string() + "': " + ec.message(),
                        SystemException::DirectoryCreateErr
                        );
        }

        // 6-ти значный номер папки
        int nextId = 1;
        while (nextId < 100000) {
                std::ostringstream nameStream;
                nameStream << std::setw(6) << std::setfill('0') << nextId;
                fs::path candidate = tasksDir / nameStream.str();
                if (!fs::exists(candidate)) {
                        break;
                }
                ++nextId;
        }

        std::ostringstream folderName;
        folderName << std::setw(6) << std::setfill('0') << nextId;
        fs::path taskFolder = tasksDir / folderName.str();

        // meta
        fs::path metaPath = taskFolder / "meta.txt";
        std::ofstream metaOut (metaPath);
        if (!metaOut.is_open()) {
                throw SystemException::fileOpenError(metaPath.string(), true);
        }

        metaOut << task.getTitle() << '\n';
        metaOut << task.getDifficulty() << ' '
                << task.getPoints() << ' '
                << task.getTestCount() << ' '
                << task.getTimeLimit() << '\n';

        if (!metaOut.good()) {
                throw SystemException("Ошибка при записи метаданных в '" + metaPath.string() + "'",
                        SystemException::FileWriteErr
                        );
        }

        // каждый тест в отдельный файл
        for (int i = 0; i < task.getTestCount(); ++i) {
                fs::path testPath = taskFolder / ("test_" + std::to_string(i) + ".txt");
                std::ofstream testOut (testPath);
                if (!testOut.is_open()) {
                        throw SystemException::fileOpenError(testPath.string(), true);
                }

                testOut << task[i];
                if (!testOut.good()) {
                        throw SystemException("Ошибка при записи тестового файла '" + testPath.string() + "'",
                                SystemException::FileWriteErr
                                );
                }
        }
}


