#pragma once
#include <string>
#include <chrono>
#include <ostream>

// Приоритеты задач
enum class Priority { 
	LOW = 0,
       	MEDIUM = 1,
       	HIGH = 2
};

//Статусы задач
enum class Status { 
	PENDING = 0,
       	COMPLETED = 1,
	DELETED = 2
};

//Структура задачи
struct Task {

	// === Поля ===
	int id;						// Уникальный идентификатор
	std::string description;			// Описание задачи
	std::chrono::system_clock::time_point creationDate;	// Дата создания
	Priority priority;				// Приоритет задачи
	Status status;					// Текущий статус
	std::string category;				// Категория/тег

	// === Конструкторы ===
	explicit Task(const std::string& desc,
		       	Priority prio = Priority::MEDIUM,
		       	const std::string& cat = "");

	// === Методы ===
	void markCompleted();				// Пометить как выполненную

	bool isCompleted() const noexcept;		// Проверить статус

	std::string getCreationDateString() const;	// Дата создания (форматированная)

	std::string serialize() const;			// Сериализация в строку
	static Task deserialize(const std::string& data);	// Десериализация
};

// === Внешние функции ===
std::ostream& operator<<(std::ostream& os, const Task& task);	// Оператор вывода
