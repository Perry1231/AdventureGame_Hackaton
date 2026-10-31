#include "Header.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    srand((unsigned)time(nullptr));

    MainFunction();
    return 0;
}
