cmake_minimum_required(VERSION 4.0)
project(TaskManager CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включение поддержки Unicode для Windows
if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0601)
    add_compile_options(/utf-8)
endif()

# Исходные файлы проекта
set(SOURCES
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/ConsoleUtils.cpp
)

# Заголовочные файлы
set(HEADERS
    include/Task.h
    include/TaskManager.h
    include/ConsoleUtils.h
)

# Создание исполняемого файла
add_executable(task_manager ${SOURCES} ${HEADERS})

# Установка путей для include-директорий
target_include_directories(task_manager PRIVATE include)

# Настройки для Windows
if(WIN32)
    target_link_libraries(task_manager PRIVATE Advapi32)
    target_compile_definitions(task_manager PRIVATE NOMINMAX)
endif()

# Опции для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(task_manager PRIVATE DEBUG)
    target_compile_options(task_manager PRIVATE -Wall -Wextra -pedantic)
endif()

# Установка выходного каталога
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
