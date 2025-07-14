#include "Task.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <vector>

// Конструктор
Task::Task(const std::string& desc, Priority prio, const std::string& cat)
    : description(desc.empty() ? "Unnamed task" : desc),
      priority(prio),
      category(cat),
      status(Status::PENDING),
      creationDate(std::chrono::system_clock::now()) {}

// Методы изменения состояния
void Task::markCompleted() {
    status = Status::COMPLETED;
}
// Методы проверки состояния
bool Task::isCompleted() const noexcept {
    return status == Status::COMPLETED;
}
// Форматирование дат
std::string Task::getCreationDateString() const {
    std::time_t time = std::chrono::system_clock::to_time_t(creationDate);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", std::localtime(&time));
    return buffer;
}

// Сериализация
std::string Task::serialize() const {
    std::ostringstream oss;
    oss << id << ","
        << description << ","
        << static_cast<int>(priority) << ","
        << static_cast<int>(status) << ","
        << category << ","
        << getCreationDateString();
    return oss.str();
}

// Десериализация
Task Task::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() != 7) {
        throw std::runtime_error("Invalid task data format");
    }

    try {
        Task task(tokens[1], 
                 static_cast<Priority>(std::stoi(tokens[2])), 
                 tokens[4]);
        
        task.id = std::stoi(tokens[0]);
        task.status = static_cast<Status>(std::stoi(tokens[3]));

        // Парсинг даты создания
        std::tm tm = {};
        std::istringstream dateStream(tokens[5]);
        dateStream >> std::get_time(&tm, "%Y-%m-%d %H:%M");
        if (dateStream.fail()) {
            throw std::runtime_error("Invalid creation date format");
        }
        task.creationDate = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        return task;
    } 
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Deserialization failed: ") + e.what());
    }
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Task& task) {
    os << "Task #" << task.id << " ["
       << (task.isCompleted() ? "COMPLETED" : "PENDING") << "]\n"
       << "Description: " << task.description << "\n"
       << "Priority: ";
    
    switch (task.priority) {
        case Priority::LOW: os << "LOW"; break;
        case Priority::MEDIUM: os << "MEDIUM"; break;
        case Priority::HIGH: os << "HIGH"; break;
    }
    
    os << "\nCategory: " << task.category << "\n"
       << "Created: " << task.getCreationDateString() << "\n";
    
   return os;
}
