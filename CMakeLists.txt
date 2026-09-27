cmake_minimum_required(VERSION 3.20)
project(coursework CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку файлов Qt (если есть .ui / Q_OBJECT)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Подключаем директорию src для корректных инклюдов
include_directories(src)

# Собираем все файлы .cpp из src, src/core и src/gui
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
)

add_executable(coursework ${SOURCES})

# Если используешь Qt, раскомментируй строки ниже:
# find_package(Qt6 REQUIRED COMPONENTS Widgets) # или Qt5
# target_link_libraries(coursework PRIVATE Qt6::Widgets)