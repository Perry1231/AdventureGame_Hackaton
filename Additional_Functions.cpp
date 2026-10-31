#include <iostream>
#include <limits>
#include "Header.h"

char ChoiceInput_YN()
{
    char choice;
    std::cout << "Enter your choice (y/n): ";
    std::cin >> choice;

    while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter y or n: ";
        std::cin >> choice;
    }

    return choice;
}


int ChoiceInput_Number()
{
    int choice;
    std::cout << "Enter your choice: ";
    while (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    return choice;
}


int ChoiceInput_NumberInRange(int min, int max)
{
    int choice = ChoiceInput_Number();
    while (choice < min || choice > max) {
        std::cout << "Choice must be between " << min << " and " << max << ". ";
        choice = ChoiceInput_Number();
    }
    return choice;
}


std::string ChoiceInput_Text()
{
    std::string text;
    std::cout << "Enter text: ";
    std::cin >> text;
    return text;
}