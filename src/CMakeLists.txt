cmake_minimum_required(VERSION 3.20)
project(coursework CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Отсчитываем пути прямо от папки src/
add_executable(coursework
        main.cpp
        core/User.cpp
        core/Student.cpp
        core/Teacher.cpp
        core/Task.cpp
)

# Подключаем папки с заголовочными файлами (.h)
target_include_directories(coursework PRIVATE
        .
        core
)