#pragma once

#include <string>
#include <iostream>

namespace ConsoleUtils {
    // ANSI коды цветов
    namespace Colors {
        const std::string RESET   = "\033[0m";
        const std::string RED     = "\033[31m";
        const std::string GREEN   = "\033[32m";
        const std::string YELLOW  = "\033[33m";
        const std::string BLUE    = "\033[34m";
        const std::string MAGENTA = "\033[35m";
        const std::string CYAN    = "\033[36m";
        const std::string WHITE   = "\033[37m";
        const std::string BOLD    = "\033[1m";
        const std::string DIM     = "\033[2m";
    }

    // Очистка консоли
    void clearScreen();

    // Вывод цветного текста
    void printColored(const std::string& text, const std::string& color);
    
    // Вывод заголовка
    void printHeader(const std::string& text);
    
    // Вывод ошибки
    void printError(const std::string& message);
    
    // Вывод успешного сообщения
    void printSuccess(const std::string& message);
    
    // Вывод предупреждения
    void printWarning(const std::string& message);
    
    // Получение ввода с сообщением
    std::string getInput(const std::string& prompt);
    
    // Ожидание нажатия клавиши
    void waitForAnyKey(const std::string& message = "Press any key to continue...");
}
