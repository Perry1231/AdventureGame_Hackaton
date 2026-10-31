#include "Header.h"

void Chest::ChestCreate(ChestType type, Character& hero)
{
    chestType = type;
    capacity = 5; // Default capacity
    isOpen = false;
    
    // TODO: Add items based on chest type
    std::cout << "Chest created with type: " << type << "\n";
}

void Chest::RandomizeChest(Character& hero)
{
    int randType = rand() % 4;
    ChestType types[] = {COMMON, RARE, EPIC, LEGENDARY};
    chestType = types[randType];
    
    // TODO: Add items based on chest type
    capacity = 5 + randType; // Higher rarity = more capacity
    isOpen = false;
    
    std::cout << "Chest randomized with type: " << chestType << "\n";
}

void Chest::Open(Character* target)
{
    if (IsOpen()) {
        std::cout << "Chest is already open!\n";
        return;
    }
    
    isOpen = true;
    std::cout << "Chest opened!\n";
    
    // TODO: Give items to target
}

void Chest::Close()
{
    isOpen = false;
    std::cout << "Chest closed!\n";
}

void Chest::ShowInfo() const
{
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                  CHEST INFORMATION               │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│ Type: " << chestType << "\n";
    std::cout << "│ Capacity: " << capacity << "\n";
    std::cout << "│ Status: " << (isOpen ? "Open" : "Closed") << "\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}

void Chest::ShowItems() const
{
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                    CHEST ITEMS                   │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    
    // TODO: Display items in chest
    
    std::cout << "└───────────────────────────────────────────────────┘\n";
}

void Chest::RemoveItem(int index)
{
    // TODO: Remove item at index
    std::cout << "Item removed from chest (index " << index << ")!\n";
}