cmake_minimum_required(VERSION 3.16)
project(AdventureGame_Hackaton VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Enable automoc, autouic, autorcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Source files (existing game logic)
set(GAME_SOURCES
    Addition.cpp
    AdditionalGames.cpp
    Additional_Functions.cpp
    Armory.cpp
    Artifact.cpp
    Character.cpp
    Chest.cpp
    Deleter.cpp
    Enemy.cpp
    ErrorCatcher.cpp
    Events.cpp
    Header.h
    Inventory.cpp
    Loader.cpp
    MainFunction.cpp
    Objects.cpp
    OtherCharacter.cpp
    Plot.cpp
    Potion.cpp
    Saver.cpp
    Task_Generator_For_Character.cpp
    Weapon.cpp
)

# Qt GUI sources
set(GUI_SOURCES
    src/gui/main.cpp
    src/gui/GameController.cpp
    src/gui/MainWindow.cpp
    src/gui/DifficultyWindow.cpp
    src/gui/GameWindow.cpp
    src/gui/SaveLoadWindow.cpp
)

# Headers for GUI
set(GUI_HEADERS
    src/gui/GameController.h
    src/gui/MainWindow.h
    src/gui/DifficultyWindow.h
    src/gui/GameWindow.h
    src/gui/SaveLoadWindow.h
)

# Resources
qt6_add_resources(RESOURCES resources/resources.qrc)

# Executable
add_executable(AdventureGame
    ${GAME_SOURCES}
    ${GUI_SOURCES}
    ${GUI_HEADERS}
    ${RESOURCES}
)

target_link_libraries(AdventureGame PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Include directories
target_include_directories(AdventureGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
)

# Output directory
set_target_properties(AdventureGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output
    WIN32_EXECUTABLE TRUE
)