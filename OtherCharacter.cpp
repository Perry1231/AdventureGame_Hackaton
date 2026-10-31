#include "Header.h"
#include <iostream>
#include <vector>

OtherCharacter OtherCharacter::CreateRoommate()
{
    OtherCharacter oc;
    oc.ctype = ROOMMATE;
    oc.SetName("Alex " + std::to_string(rand() % 100));
    oc.SetDescription("Your roommate. Studies " + std::string(rand() % 2 == 0 ? "Computer Science" : "Mathematics"));
    oc.SetAttitude(60 + rand() % 30);
    oc.SetLevel(1 + rand() % 3);
    oc.SetLocation("Dorm Room 204");
    return oc;
}

OtherCharacter OtherCharacter::CreateRA()
{
    OtherCharacter oc;
    oc.ctype = RA;
    oc.SetName("RA Jordan");
    oc.SetDescription("Resident Advisor. Keeps the floor in order and helps students.");
    oc.SetAttitude(70);
    oc.SetLevel(3 + rand() % 3);
    oc.SetLocation("RA Office - Floor 2");
    return oc;
}

OtherCharacter OtherCharacter::CreateProfessor()
{
    OtherCharacter oc;
    oc.ctype = PROFESSOR;
    oc.SetName("Prof. " + std::string(rand() % 2 == 0 ? "Williams" : "Chen"));
    oc.SetDescription("University professor. Office hours: Tue/Thu 2-4pm.");
    oc.SetAttitude(50);
    oc.SetLevel(5 + rand() % 5);
    oc.SetLocation("Academic Building - Room 301");
    return oc;
}

OtherCharacter OtherCharacter::CreateVendor()
{
    OtherCharacter oc;
    oc.ctype = VENDOR;
    oc.SetName("Campus Vendor");
    oc.SetDescription("Sells snacks, energy drinks, and school supplies.");
    oc.SetAttitude(40);
    oc.SetLevel(1);
    oc.SetLocation("Student Union - Food Court");
    return oc;
}

OtherCharacter OtherCharacter::CreateQuestGiver()
{
    OtherCharacter oc;
    oc.ctype = QUESTGIVERS;
    oc.SetName("Student Council Rep");
    oc.SetDescription("Offers campus tasks and part-time job opportunities.");
    oc.SetAttitude(60);
    oc.SetLevel(2);
    oc.SetLocation("Student Council Office");
    return oc;
}

OtherCharacter OtherCharacter::CreateMerchant()
{
    OtherCharacter oc;
    oc.ctype = MERCHANTS;
    oc.SetName("Textbook Reseller");
    oc.SetDescription("Buys and sells used textbooks and notes.");
    oc.SetAttitude(30);
    oc.SetLevel(1);
    oc.SetLocation("Library Entrance");
    return oc;
}

void OtherCharacter::DisplayInfo() const
{
    std::cout << "\n┌─────────────────────────────────────────────────────┐\n";
    std::cout << "│                      NPC INFO                       │\n";
    std::cout << "├─────────────────────────────────────────────────────┤\n";
    std::cout << "│  Name        : " << name << "\n";
    std::cout << "│  Type        : " << [this]() -> std::string {
        switch(ctype) {
            case ROOMMATE: return "Roommate";
            case RA: return "Resident Advisor";
            case PROFESSOR: return "Professor";
            case VENDOR: return "Vendor";
            case QUESTGIVERS: return "Quest Giver";
            case MERCHANTS: return "Merchant";
            default: return "Unknown";
        }
    }() << "\n";
    std::cout << "│  Location    : " << location << "\n";
    std::cout << "│  Level       : " << level << "\n";
    std::cout << "│  Attitude    : " << attitude << "/100\n";
    std::cout << "│  Description : " << description << "\n";
    std::cout << "└─────────────────────────────────────────────────────┘\n\n";
}

void OtherCharacter::RandomizeStats()
{
    // Randomize name and description based on type
    std::vector<std::string> firstNames = {"Alex", "Sam", "Jordan", "Taylor", "Casey", "Riley", "Morgan", "Avery", "Quinn", "Dakota"};
    std::vector<std::string> lastNames = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"};
    
    name = firstNames[rand() % firstNames.size()] + " " + lastNames[rand() % lastNames.size()];
    level = 1 + rand() % 5;
    attitude = 20 + rand() % 80;
}