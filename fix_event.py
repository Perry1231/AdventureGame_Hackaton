with open(r'C:\Users\Dell\Desktop\projetcs\GitHub Projects\AdventureGame_Hackaton\Events.cpp', 'r', encoding='utf-8') as f:
    content = f.read()

old = '''void FakeDistressCal(Character& hero, GameHard& levelDificulty) {                                       //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::cout << "If want to check -- 1 \\nIf you want pass --- 2" << std::endl;
    int choice =ChoiceInput_Number();

    if(choice == 1)
    {


    std::cout << "Event: Fake Distress Call!\\n";
    int event_fake_diss_call = rand() % 4 +1;

    switch(event_fake_diss_call)
    {
case 1:
std::cout << "It's only your tired imagination" << std::endl;
hero.SetLevel(hero.GetLevel() + 0.01);
break;
case 2:
std::cout << "It's only old granny" << std::endl;
Tired_Granny_Event(hero, levelDificulty);
break;
case 3:
std::cout << "IT'S WENDIGO RUN !!!" << std::endl;
Wendigo_Encounter_Event(hero, levelDificulty);
break;
case 4:
            std::cout << "You had entered an overgrown storage room" << std::endl;
            std::cout << "You see a small supply closet" << std::endl;

break;
    }
}


    else if (choice == 2)
    {
        std::cout << "You go away" << std::endl;
        exit(0);
    }
    else {std::cout << "You entere wrong answer !";}
}'''

new = '''void FakeDistressCal(Character& hero, GameHard& levelDificulty) {
    PrintEventCard("📱", "FAKE EMERGENCY TEXT", "You get a panicked group chat message: 'FIRE IN LAUNDRY ROOM!!!'", Color::RED);
    
    std::cout << "\\nWhat do you do?\\n";
    std::cout << "1. Sprint to laundry room with extinguisher\\n";
    std::cout << "2. Check if it's real first\\n";
    std::cout << "3. Ignore - probably a prank\\n";
    std::cout << "Choice: ";
    
    int choice = ChoiceInput_Number();
    
    switch(choice) {
        case 1:
            std::cout << "You burst in heroically... to find someone burning popcorn. Embarrassing but safe.\\n";
            hero.SetLevel(hero.GetLevel() + 0.03);
            GainGold(hero, 10);
            break;
        case 2:
            std::cout << "You check the group chat - sent 3 hours ago. It's old news.\\n";
            hero.SetLevel(hero.GetLevel() + 0.02);
            break;
        case 3:
            std::cout << "You stay in bed. Turns out it WAS real but RA handled it.\\n";
            hero.SetLevel(hero.GetLevel() + 0.01);
            break;
        default:
            std::cout << "You hesitate. The RA yells at you for blocking the hallway.\\n";
            DamageHero(hero, 3);
    }
}'''

if old in content:
    content = content.replace(old, new)
    with open(r'C:\Users\Dell\Desktop\projetcs\GitHub Projects\AdventureGame_Hackaton\Events.cpp', 'w', encoding='utf-8') as f:
        f.write(content)
    print("SUCCESS: FakeDistressCal updated")
else:
    print("FAILED: Old text not found")