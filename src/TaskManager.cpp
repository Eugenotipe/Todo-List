#include "TaskManager.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <numeric>

// Добавление задачи с move-семантикой
void TaskManager::addTask(const Task& task) {
    	Task newTask = task;
	newTask.id = nextId++;
    	tasks.push_back(newTask);
}

// Удаление задачи по ID
bool TaskManager::deleteTask(int id) {
    auto it = findTaskById(id);
    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }
    return false;
}

// Пометка задачи как выполненной
bool TaskManager::markTaskCompleted(int id) {
    auto it = findTaskById(id);
    if (it != tasks.end() && !it->isCompleted()) {
        it->markCompleted();
        return true;
    }
    return false;
}

// === Доступ к задачам ===
const std::vector<Task>& TaskManager::getAllTasks() const noexcept {
    return tasks;
}

// === Статистика ===
size_t TaskManager::getTaskCount() const noexcept {
    return tasks.size();
}

size_t TaskManager::getCompletedCount() const noexcept {
    return std::count_if(tasks.begin(), tasks.end(),
        [](const Task& t) { return t.isCompleted(); });
}

// === Итераторы ===
TaskManager::TaskIterator TaskManager::begin() noexcept {
    return tasks.begin();
}

TaskManager::ConstTaskIterator TaskManager::begin() const noexcept {
    return tasks.begin();
}

TaskManager::TaskIterator TaskManager::end() noexcept {
    return tasks.end();
}

TaskManager::ConstTaskIterator TaskManager::end() const noexcept {
    return tasks.end();
}

// === Системные операции ===
bool TaskManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::vector<Task> loadedTasks;
    std::string line;
    
    while (std::getline(file, line)) {
        try {
            loadedTasks.push_back(Task::deserialize(line));
        } catch (...) {
            // Пропускаем некорректные записи
            continue;
        }
    }

    if (!loadedTasks.empty()) {
        tasks = std::move(loadedTasks);
        nextId = std::max_element(tasks.begin(), tasks.end(),
            [](const Task& a, const Task& b) { return a.id < b.id; })->id + 1;
    }
    
    return true;
}

bool TaskManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& task : tasks) {
        file << task.serialize() << '\n';
    }

    return true;
}

TaskManager::TaskIterator TaskManager::findTaskById(int id) {
    return std::find_if(tasks.begin(), tasks.end(),
        [id](const Task& t) { return t.id == id; });
}

TaskManager::ConstTaskIterator TaskManager::findTaskById(int id) const {
    return std::find_if(tasks.begin(), tasks.end(),
        [id](const Task& t) { return t.id == id; });
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const TaskManager& manager) {
    os << "Task Manager (Total: " << manager.getTaskCount() 
       << ", Completed: " << manager.getCompletedCount() << ")\n";
    
    for (const auto& task : manager.getAllTasks()) {
        os << task << "\n---\n";
    }
    
    return os;
}
