#include <iostream>
#include "Header.h"
//Here will be functions for objects db and their abillities



void Object::CreateObjectConstructor()
{

}


void Object::RecountObject()
{

}


void Object::DisplayObjectStats()
{
std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│              OBJECT CHARACTERISTICS             │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  Object : " << name_object << "\n";
    std::cout << "│  Description: " << describtion_object << "\n";
    std::cout << "│  Rarity   : " << rarityType_object << "\n";
    std::cout << "│  Value    : " << price_object << " gold\n";
    std::cout << "└───────────────────────────────────────────────────┘\n\n";
}



void Object::ShowInfo() const {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│              ARTIFACT CHARACTERISTICS             │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  Artifact : " << name_object << "\n";
    std::cout << "│  Description: " << describtion_object << "\n";
    std::cout << "│  Type     : " << GetType() << "\n";
    std::cout << "│  Value    : " << price_object << " gold\n";
    std::cout << "└───────────────────────────────────────────────────┘\n\n";
}


void Object::Use() {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    if (!owner_p) {
        std::cout << "│  Artifact " << name_object << " has no owner!\n";
        std::cout << "└───────────────────────────────────────────────────┘\n";
        return;
    }

    std::cout << "│  Using artifact: " << name_object << "!\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}
