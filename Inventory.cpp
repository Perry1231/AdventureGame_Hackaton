#include "Header.h"
#include <iostream>
#include <iomanip>
//====================================================Inventory_functions=======================================================================================================

int MyInventory::ResizeInventoryBig()
{
   int new_capacity = capacity + 1;
    Item** temp = new Item*[new_capacity];
    for (int i = 0; i < count; i++)
        temp[i] = items[i];
    delete[] items;
    items = temp;
    capacity = new_capacity;
    return 0;
}


void MyInventory::DisplayInventory() const 
{
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* GRAY = "\033[90m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* RESET = "\033[0m";

    if (count == 0)
    {
        std::cout << RED << "\n[!] Inventory is completely empty.\n" << RESET;
        return;
    }

    std::cout << CYAN << "\n================ INVENTORY (" << count << " items) ================\n" << RESET;

    for (int i = 0; i < count; ++i)
    {
        std::cout << YELLOW << "#" << (i + 1) << " " << RESET
                  << items[i]->GetName() 
                  << GRAY << " [ID: " << items[i]->GetItemId() 
                  << " | Type: " << items[i]->GetType() << "]" << RESET << "\n";

  
        items[i]->ShowInfo();//Details here are

        if (i < count - 1) {
            std::cout << GRAY << "--------------------------------------------------\n" << RESET;
        }
    }

    std::cout << CYAN << "====================================================\n\n" << RESET;
}


int MyInventory::AddItem(Item* item) {
    if (count >= capacity) ResizeInventoryBig();
    item->SetItemId(id);   
    items[count++] = item;
    id++;
    return 0;
}


int MyInventory::DelItem(int itemId) {
    for (int i = 0; i < count; i++) {
        if (items[i]->GetItemId() == itemId) {
            delete items[i];
            for (int j = i; j < count - 1; j++) {
                items[j] = items[j + 1];
            }
            count--;
            std::cout << "Item with ID " << itemId << " deleted." << std::endl;
            return 0;
        }
    }
    std::cout << "Item with ID " << itemId << " not found!" << std::endl;
    return -1;
}

void MyInventory::InventoryFunctions()                                                       //For displaying functions , like : show items , delete items; (MENU)
{
    while(true)
    {
        ChoiceInput_Number();
    int choice =ChoiceInput_Number();
    std::cout << "\n\n" << std::endl;
    std::cout <<"==================Inventory================="<< std::endl;
    std::cout << "Size: " << count << std::endl;
    std::cout <<"=================Functions=================="<< std::endl;
    std::cout <<"Disaply all items in : 1 \nDelete item from id  : 2 \nEquip item from id   : 3 " << std::endl;
    std::cout << "Exit: 0" << std::endl;
    std::cout <<"============================================="<< std::endl;
                
    std::cout << "\n\n" << std::endl;
    while (true)
    {//Show inventory
        std::cout << "Choice: ";
        std::cin >>choice;
        if (choice == 1) DisplayInventory();

        else if (choice == 2)
        {//Display all items
            
            std::cout << "Eneter id of item to delete : " ;
            int choice_2= ChoiceInput_Number();
            if (DelItem(choice_2) == -1) {
                std::cout << "Error: Item not found! Cannot delete." << std::endl;
            }
        }

        else if (choice == 3)         
{//Equip item
    int itemId;
    std::cout << "Enter item ID to equip: ";
    std::cin >> itemId;
    
    //Search items in inventory
    for (int i = 0; i < count; i++)
    {
        if (items[i]->GetItemId() == itemId)
        {
            if (items[i]->GetType() == "Weapon")
            {
                owner->EquipWeapon(dynamic_cast<Weapon*>(items[i]));
            }
            else if (items[i]->GetType() == "Armor")
            {
                owner->EquipArmor(dynamic_cast<Armory*>(items[i]));
            }
            else
            {
                std::cout << "This item cannot be equipped!" << std::endl;
            }
            continue;
        }
    }
    
} 
else if (choice == 4) {
    int itemId;
    std::cout << "Enter item ID to use: ";
    std::cin >> itemId;
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (items[i]->GetItemId() == itemId) {
            found = true;
            if (items[i]->GetType() == "Potion") 
            {
                Potion* potion = dynamic_cast<Potion*>(items[i]);
                potion->SetOwner(owner); 
                potion->Use();             
                DelItem(itemId);
                break;
            }
        }
    }
    if (!found) {
        std::cout << "Item with ID " << itemId << " not found!" << std::endl;
    }
    }
    }
    }
}



void MyInventory::Clear()
{
    for (int i = 0; i < count; i++)
    {
        delete items[i];
    }
    count = 0;
    capacity = 0;
    id = 1;
    delete[] items;
    items = nullptr;
}

Item* MyInventory::GetItem(int index) const { 
    if (index >= 0 && index < count) { return items[index]; } 
    return nullptr; }


