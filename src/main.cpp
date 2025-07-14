#include "TaskManager.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <limits>

using namespace ConsoleUtils;

void displayMainMenu() {
    clearScreen();
    printHeader("Task Manager");
    std::cout << "1. Show all tasks\n"
              << "2. Add task\n"
              << "3. Mark as completed\n"
              << "4. Delete task\n"
              << "5. Save to file\n"
              << "6. Upload from file\n"
              << "7. Exit\n";
}

void showAllTasks(const TaskManager& manager) {
    clearScreen();
    printHeader("Task list");
    
    if (manager.getAllTasks().empty()) {
        printWarning("There're no tasks to display");
        return;
    }

    for (const auto& task : manager.getAllTasks()) {
        const std::string& statusColor = task.isCompleted() ? Colors::GREEN : Colors::RED;
        const char* statusText = task.isCompleted() ? "[V]" : "[X]";
        
        printColored(statusText, statusColor);
        std::cout << " #" << task.id << ": " << task.description;
        
        if (!task.category.empty()) {
            std::cout << " (" << Colors::MAGENTA << task.category << Colors::RESET << ")";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nTotal tasks: " << manager.getTaskCount() 
              << ", completed: " << manager.getCompletedCount() << "\n";
}

void addNewTask(TaskManager& manager) {
    clearScreen();
    printHeader("Add task");
    
    std::string desc = getInput("Enter the task's description");
    std::string category = getInput("Select a category (optional)");
    
    std::string priorityInput = getInput("Priority (1-low, 2-middle, 3-high)");
    Priority priority = static_cast<Priority>(std::stoi(priorityInput) - 1);
    
    manager.addTask(Task(desc, priority, category));
    printSuccess("The task was successfully added!");
}

void markTaskCompleted(TaskManager& manager) {
    showAllTasks(manager);
    if (manager.getAllTasks().empty()) return;
    
    int id = std::stoi(getInput("Enter the task ID to mark"));
    if (manager.markTaskCompleted(id)) {
        printSuccess("The task was marked as completed!");
    } else {
        printError("Couldn't find a task with the specified ID");
    }
}

void deleteTask(TaskManager& manager) {
    showAllTasks(manager);
    if (manager.getAllTasks().empty()) return;
    
    int id = std::stoi(getInput("Enter the task ID to delete"));
    if (manager.deleteTask(id)) {
        printSuccess("The task was successfully deleted!");
    } else {
        printError("Couldn't find a task with the specified ID");
    }
}

void saveToFile(TaskManager& manager) {
    std::string filename = getInput("Enter the filename to save");
    try {
        manager.saveToFile(filename);
        printSuccess("Tasks were successfully saved to " + filename);
    } catch (const std::exception& e) {
        printError(std::string("Save error: ") + e.what());
    }
}

void loadFromFile(TaskManager& manager) {
    std::string filename = getInput("Enter the filename to upload");
    try {
        if (manager.loadFromFile(filename)) {
            printSuccess("Tasks were successfully uploaded from " + filename);
        } else {
            printError("Failed to upload file");
        }
    } catch (const std::exception& e) {
        printError(std::string("Upload error: ") + e.what());
    }
}

int main() {
    // Инициализация консоли (для Windows)
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif

    TaskManager manager;
    int choice = 0;

    do {
        displayMainMenu();
        std::cout << "> ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch(choice) {
                case 1: showAllTasks(manager); break;
                case 2: addNewTask(manager); break;
                case 3: markTaskCompleted(manager); break;
                case 4: deleteTask(manager); break;
                case 5: saveToFile(manager); break;
                case 6: loadFromFile(manager); break;
                case 7: clearScreen(); break;
                default: printError("Wrong input");
            }
        } catch (const std::exception& e) {
            printError(std::string("Error: ") + e.what());
        }

        if (choice != 7) waitForAnyKey();
    } while (choice != 7);

    return 0;
}
