# Adventure Game

Text-based RPG written in C++17. Manage your character, collect weapons and armor, use potions, and embark on a procedural adventure from the terminal.

## Features

- **Character System**: Randomized stats based on profession (health, strength, agility, intelligence, defense, gold).
- **Inventory Management**: Add, remove, resize, and manage weapons, armor, and potions.
- **Equipment**: Equip and unequip weapons and armor to modify attack and defense values.
- **Potion Effects**: Apply active buffs/debuffs with different potencies and durations.
- **Dynamic Events**: Randomized encounters, traders, and StoryFunction-driven plot points.
- **Combat & Stats**: Real-time stat display with active effect processing.
- **Cross-platform**: Compiles on Windows (MinGW/MSVC), Linux, and macOS.

## Project Structure

| File | Purpose |
|------|---------|
| `Main.cpp` | Entry point (`main()` → calls `MainFunction()`). |
| `MainFunction.cpp` | Main menu, game loop, inventory interaction. |
| `Header.h` | Class declarations for `Character`, `Weapon`, `Armory`, `Potion`, `MyInventory`, `OtInventory`, `Item`, and global functions. |
| `Character.cpp` | Character stats, equip/unequip logic, effect processing. |
| `Weapon.cpp` | Weapon randomization, durability, info display. |
| `Armory.cpp` | Armor randomization, durability, info display. |
| `Potion.cpp` | Potion effects, database, usage. |
| `Inventory.cpp` | Inventory array management, display, add/delete/resize. |
| `Addition.cpp` | Startup (`StartGame`), difficulty choice (`ChoiceHard`), help text. |
| `Plot.cpp` | StoryFunction/lore events. |
| `Action.cpp` | Combat/action logic. |
| `OtherCharacter.cpp` | NPC and trader logic. |
| `OtherRandomizer.cpp` | Shared randomization helpers. |
| `Evets.cpp` | Random event triggers. |
| `Trade.cpp` | Trading/shop system. |

## Requirements

- A C++17 compiler:
  - **GCC / MinGW-w64** (recommended)
  - **Microsoft Visual C++ (MSVC)**
  - **Clang**
- **Git** (optional, for cloning)
- Windows, Linux, or macOS

## Building

### GCC / MinGW-w64 (Recommended)

Compile **all** `.cpp` files together:

```bash
g++ -Wall -Wextra -g3 *.cpp -o AdventureGame.exe
Or explicitly:

g++ -Wall -Wextra -g3 Main.cpp MainFunction.cpp Character.cpp Weapon.cpp Armory.cpp Potion.cpp Inventory.cpp Addition.cpp Plot.cpp OtherCharacter.cpp Action.cpp OtherRandomizer.cpp Evets.cpp Trade.cpp -o AdventureGame.exe
Static Build (Portable)
To generate a standalone executable without requiring MinGW DLLs on the target machine:

g++ -static-libgcc -static-libstdc++ -static *.cpp -o AdventureGame.exe
```

## Microsoft Visual Studio
Open Visual Studio → Open a Local Folder → select the project folder.
Build → Build Solution.
Run with Local Windows Debugger.
Visual Studio Code
Install the C/C++ Extension by Microsoft.
Open the project folder.
In the integrated terminal (`Ctrl + ``), run the GCC command above.
Running
After compilation, run the executable:

Windows: AdventureGame.exe
Linux/macOS: ./AdventureGame
Gameplay
Upon launch, the main menu appears:

=== MAIN MENU ===
1. Start game
2. Show character stats
3. Show your inventory
4. Manage your Inventory
5. Get info
6. Help
0. Exit
Commands
Start Game — chooses difficulty and begins the adventure.
Show Character Stats — displays health, strength, agility, intelligence, defense, gold, equipped weapon/armor, and active effects.
Show Inventory — lists all items with IDs, names, types, and values.
Manage Inventory — submenu for additional inventory operations.
Get Info — detailed weapon/armor inspection, equip/unequip commands.
Help — quick reference for controls.
Exit — closes the application.
Submenu: Get Info
1. Display inventory
2. Show weapon stats
3. Equip weapon
4. Unequip weapon
5. Show armor stats
6. Equip armor
7. Unequip armor
0. Back to main menu

![Screenshot](https://github.com/Perry1231/Adventure-Game/blob/main/Photo.png)


## GitHub Actions
This repository includes a GitHub Actions workflow (.github/workflows/c-cpp.yml) that automatically builds the project on every push to main.

## To download the latest automated build:

Open the repository on GitHub.
Go to Actions → latest successful workflow.
Download the generated artifact.
Extract and run AdventureGame.
Windows Defender / SmartScreen Warning
Because the executable is not digitally signed, Windows SmartScreen may display a warning when running for the first time:

## Windows protected your PC

Click More Info → Run Anyway. This is expected behavior for unsigned educational projects.

## Troubleshooting
undefined reference errors during linking
Make sure all .cpp files are passed to the compiler. The project relies on definitions spread across multiple translation units. The wildcard *.cpp is the easiest way to avoid this.

g++: command not found
Install MinGW-w64 or MSYS2 and ensure g++ is in your system PATH. Verify with:

g++ --version
Missing features or crashes
Verify all source files are present in the same directory and none have been renamed or removed. The project requires C++17 support.

## Contributing
Contributions are welcome. Please open an issue or pull request on GitHub.

## Author
Developed by Vladyslav Vytrykush to demonstrate C++ programming practices, OOP design, and project structure.

## License
This project is for educational purposes. No explicit license is set; contact the author for reuse permissions. ```
