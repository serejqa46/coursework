cmake_minimum_required(VERSION 3.20)
project(coursework CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку файлов Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Явно перечисляем все файлы проекта (это надежнее, чем GLOB)
add_executable(coursework
    main.cpp
    src/core/Task.cpp
    src/core/User.cpp
    src/core/Student.cpp
    src/core/Teacher.cpp
)

# Подключаем директорию src для инклюдов
target_include_directories(coursework PRIVATE src)

# Если используешь Qt6 (или Qt5):
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# target_link_libraries(coursework PRIVATE Qt6::Widgets)