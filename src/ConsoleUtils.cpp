#include "ConsoleUtils.h"
#include <iostream>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

using namespace ConsoleUtils;

void ConsoleUtils::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleUtils::printColored(const std::string& text, const std::string& color) {
    std::cout << color << text << Colors::RESET;
}

void ConsoleUtils::printHeader(const std::string& text) {
    std::cout << Colors::BOLD << Colors::CYAN 
              << "=== " << text << " ===\n" 
              << Colors::RESET;
}

void ConsoleUtils::printError(const std::string& message) {
    printColored("[ERROR] " + message + "\n", Colors::RED);
}

void ConsoleUtils::printSuccess(const std::string& message) {
    printColored("[SUCCESS] " + message + "\n", Colors::GREEN);
}

void ConsoleUtils::printWarning(const std::string& message) {
    printColored("[WARNING] " + message + "\n", Colors::YELLOW);
}

std::string ConsoleUtils::getInput(const std::string& prompt) {
    std::cout << Colors::BOLD << prompt << ": " << Colors::RESET;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleUtils::waitForAnyKey(const std::string& message) {
    std::cout << Colors::DIM << message << Colors::RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
