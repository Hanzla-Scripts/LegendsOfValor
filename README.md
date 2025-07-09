# LegendsOfValor
Legends of Valor is a console-based RPG game developed in C++ as an Object-Oriented Programming (OOP) semester project by Hanzla Khurram. The game features a rich class hierarchy, dynamic gameplay, and data structures to manage players, enemies, inventory, and game locations.
Features

Player Classes: Choose between Warrior, Mage, or Ranger, each with unique abilities and stats.
Locations: Explore four distinct places (Forest, Village, Castle, Desert), each with unique enemies and final bosses.
Inventory System: Collect and use helping objects like Health Potions, Power Amulets, and Traps.
Combat System: Engage in turn-based battles with enemies and bosses, utilizing attacks, skills, and items.
Game Management: Save/load game progress, view battle history, and track stats like battles won and secrets found.
OOP Principles: Implements inheritance, polymorphism, encapsulation, and abstraction for modular code.

How to Build and Run

Prerequisites:

C++ compiler (e.g., g++ or MSVC)
Git (to clone the repository)


Clone the Repository:
git clone https://github.com/Hanzla-Scripts/LegendsOfValor.git
cd LegendsOfValor


Compile the Code:

For g++:
g++ -o LegendsOfValor GameManager.cpp Players.cpp Places.cpp helpingobjects.cpp


For MSVC:
cl /EHsc GameManager.cpp Players.cpp Places.cpp helpingobjects.cpp




Run the Game:
./LegendsOfValor


Gameplay:

Create a player by choosing a name and class.
Explore locations, fight enemies, collect items, and defeat bosses.
Use the shop to buy items and save/load progress as needed.



File Structure

Classes.h: Header file with class definitions, enums, and forward declarations.
GameManager.cpp: Main game loop, menu, and exploration logic.
Players.cpp: Implementation of player-related classes (Character, Player, Warrior, Mage, Ranger).
Places.cpp: Implementation of location classes (Forest, Village, Castle, Desert).
helpingobjects.cpp: Inventory and helping object management.

Credits

Developed by Hanzla Khurram.
Built as part of an OOP course project.
