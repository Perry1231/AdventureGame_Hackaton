#include <iostream>
#include "Header.h"

char ChoiceInput_YN()
{
    char choice;
std::cout << "Enter your choice (y/n): ";
std::cin >> choice;

return choice;
}


int ChoiceInput_Number()
{
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}