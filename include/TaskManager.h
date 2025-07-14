#pragma once

#include "Task.h"
#include <vector>
#include <memory>
#include <functional>

class TaskManager {
public:
    // === Конструкторы/деструкторы ===
    TaskManager() = default;
    ~TaskManager() = default;

    // === Основные операции ===
    void addTask(const Task& task);               // Добавление задачи 
    bool deleteTask(int id);                       // Удаление по ID
    bool markTaskCompleted(int id);                // Пометка как выполненной
    
    // === Доступ к задачам ===
    const std::vector<Task>& getAllTasks() const noexcept;
    
    // === Операции с подмножествами ===
    
    // === Статистика ===
    size_t getTaskCount() const noexcept;
    size_t getCompletedCount() const noexcept;
    
    // === Итераторы ===
    using TaskIterator = std::vector<Task>::iterator;
    using ConstTaskIterator = std::vector<Task>::const_iterator;
    
    TaskIterator begin() noexcept;
    ConstTaskIterator begin() const noexcept;
    TaskIterator end() noexcept;
    ConstTaskIterator end() const noexcept;
    
    // === Системные операции ===
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
private:
    std::vector<Task> tasks;
    int nextId = 1;
    
    // Приватные методы
    TaskManager::TaskIterator findTaskById(int id);
    ConstTaskIterator findTaskById(int id) const;
};

// Вспомогательные функции
std::ostream& operator<<(std::ostream& os, const TaskManager& manager);
