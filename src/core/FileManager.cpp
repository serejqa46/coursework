#include "FileManager.h"
#include "Exception.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstring>

namespace fs = std::filesystem;

namespace {
        constexpr char PACKAGE_SIGNATURE[8] = {'O', 'L', 'Y', 'M', 'P', 'T', 'K', '1'};
}

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
        while (nextId < 1000000) {
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
        std::ofstream metaOut(metaPath);
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
                std::ofstream testOut(testPath);
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


std::vector<Task> FileManager::loadAllTasks() const {
        std::vector<Task> tasks;

        if (!fs::exists(tasksDir) || !fs::is_directory(tasksDir)) {
                return tasks;
        }

        for (const auto& entry : fs::directory_iterator(tasksDir)) {
                if (!entry.is_directory()) {
                        continue;
                }

                fs::path taskFolder = entry.path();
                fs::path metaPath = taskFolder / "meta.txt";
                if (!fs::exists(metaPath)) {
                        continue;
                }

                std::ifstream metaIn(metaPath);
                if (!metaIn.is_open()) {
                        throw SystemException::fileOpenError(metaPath.string(), false);
                }

                std::string title;
                if (!std::getline(metaIn, title)) {
                        throw SystemException::corruptedPackage("Отсутствует название теста в " + metaPath.string());
                }

                int difficulty = 0;
                int points = 0;
                int testCount = 0;
                int timeLimit = 0;

                if (!(metaIn >> difficulty >> points >> timeLimit >> testCount)) {
                        throw SystemException::corruptedPackage("Неверные параметры теста в " + metaPath.string());
                }

                if (testCount < 0) {
                        throw SystemException::invalidTestCount(testCount);
                }

                Task loadedTask(title, difficulty, points, timeLimit, testCount);

                for (int i = 0; i < testCount; ++i) {
                        fs::path testPath = taskFolder / ("test_" + std::to_string(i) + ".txt");
                        std::ifstream testIn(testPath);
                        if (!testIn.is_open()) {
                                throw SystemException::fileOpenError(testPath.string(), false);
                        }

                        std::ostringstream buffer;
                        buffer << testIn.rdbuf();
                        if (testIn.bad()) {
                                throw SystemException("Ошибка при чтении тестового файла '" + testPath.string() + "'",
                                        SystemException::FileReadErr);
                        }
                        loadedTask.setTest(i, buffer.str());
                }
                tasks.push_back(loadedTask);
        }
        return tasks;
}


void FileManager::exportTask(const Task& task, const std::string& packageName) const {
        if (task.getTestCount() < 0) {
                throw SystemException::invalidTestCount(task.getTestCount());
        }

        std::error_code ec;
        fs::create_directories(exportsDir, ec);
        if (ec) {
                throw SystemException("Ошибка при создании экспортируемой директории '" + exportsDir.string() + "': " + ec.message(),
                        SystemException::DirectoryCreateErr);
        }

        fs::path packagePath = exportsDir / packageName;
        std::ofstream out(packagePath, std::ios::binary);
        if (!out.is_open()) {
                throw SystemException::fileOpenError(packagePath.string(), true);
        }

        // 1. сигнатура
        out.write(PACKAGE_SIGNATURE, sizeof(PACKAGE_SIGNATURE));

        // 2. название задачи
        const std::string& title = task.getTitle();
        std::size_t titleLen = title.size();
        out.write(reinterpret_cast<const char*>(&titleLen), sizeof(titleLen));
        if (titleLen > 0) {
                out.write(title.data(), static_cast<std::streamsize>(titleLen));
        }

        // 3. остальные параметры
        int difficulty = task.getDifficulty();
        int points = task.getPoints();
        int timeLimit = task.getTimeLimit();
        int testCount = task.getTestCount();

        out.write(reinterpret_cast<const char*>(&difficulty), sizeof(difficulty));
        out.write(reinterpret_cast<const char*>(&points), sizeof(points));
        out.write(reinterpret_cast<const char*>(&timeLimit), sizeof(timeLimit));
        out.write(reinterpret_cast<const char*>(&testCount), sizeof(testCount));

        // 4. каждый тест
        for (int i = 0; i < testCount; ++i) {
                const std::string& testData = task[i];
                std::size_t testLen = testData.size();
                out.write(reinterpret_cast<const char*>(&testLen), sizeof(testLen));
                if (testLen > 0) {
                        out.write(testData.data(), static_cast<std::streamsize>(testLen));
                }
        }

        if (!out.good()) {
                throw SystemException("Ошибка при записи файла пакета '" + packagePath.string() + "'",
                        SystemException::FileWriteErr);
        }
}


Task FileManager::importTask(const std::string& packagePath) const {
        fs::path inputPath(packagePath);
        std::ifstream in(inputPath, std::ios::binary);
        if (!in.is_open()) {
                throw SystemException::fileOpenError(inputPath.string(), false);
        }

        // signature
        char sig[sizeof(PACKAGE_SIGNATURE)] = {};
        in.read(sig, sizeof(sig));
        if (in.gcount() != static_cast<std::streamsize>(sizeof(sig)) ||
                std::memcmp(sig, PACKAGE_SIGNATURE, sizeof(PACKAGE_SIGNATURE)) != 0) {
                throw SystemException("Неверная сиганутра пакета в '" + inputPath.string() + "'",
                        SystemException::InvalidPackageSig);
                }

        std::size_t titleLen = 0;
        in.read(reinterpret_cast<char*>(&titleLen), sizeof(titleLen));
        if (!in.good() || titleLen > 1000000) {
                throw SystemException::corruptedPackage("Неизвестная EOF при чтении названия теста в " + inputPath.string());
        }

        int difficulty = 0;
        int points = 0;
        int timeLimit = 0;
        int testCount = 0;

        in.read(reinterpret_cast<char*>(&difficulty), sizeof(difficulty));
        in.read(reinterpret_cast<char*>(&points), sizeof(points));
        in.read(reinterpret_cast<char*>(&timeLimit), sizeof(timeLimit));
        in.read(reinterpret_cast<char*>(&testCount), sizeof(testCount));

        if (in.fail() || in.bad()) {
                throw SystemException::corruptedPackage("Ошибка при чтении параметров теста в " + inputPath.string());
        }

        if (testCount < 0) {
                throw SystemException::invalidTestCount(testCount);
        }

        Task importedTask(title, difficulty, points, timeLimit, testCount);

        for (int i = 0; i < testCount; ++i) {
                std::size_t testLen = 0;
                in.read(reinterpret_cast<char*>(&testLen), sizeof(testLen));
                if (in.fail() || in.bad() || testLen > 1000000) {
                        throw SystemException::corruptedPackage(
                                "Неверная длина тестов в индексе " + std::to_string(i) + " в" + inputPath.string());
                }

                std::string testData(testLen, '\0');
                if (testLen > 0) {
                        in.read(&testData[0], static_cast<std::streamsize>(testLen));
                        if (in.gcount() != static_cast<std::streamsize>(testLen)) {
                                throw SystemException::corruptedPackage(
                                        "Неизвестная EOF при чтении теста " + std::to_string(i) + " в" + inputPath.string());
                        }
                }

                importedTask.setTest(i, testData);
        }
        return importedTask;
}