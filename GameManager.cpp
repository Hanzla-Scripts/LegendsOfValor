#include "24F-0505_24F-0580_Classes.h"
using namespace std;

GameManager::GameManager() : player(nullptr), currentPlace(nullptr), gameRunning(true), battleLogCount(0), battlesWon(0), itemsUsed(0), secretsFound(0) {
    placesUnlocked[0] = true;
    placesUnlocked[1] = false;
    placesUnlocked[2] = false;
    placesUnlocked[3] = false;
    for (int i = 0; i < 10; ++i) {
        battleLog[i] = "";
    }
    currentPlace = new Forest(1);
}

GameManager::~GameManager() {
    delete player;
    delete currentPlace;
}

// Runs the main game loop, serving as the entry point for the game.
// Displays a welcome banner and a menu with options for starting a new game or loading a saved game.
// Handles user input to either create a new player (option 1) or load a saved game (option 2).
// For new game: clears input buffer, creates a player, pauses, clears the screen, and shows the main menu.
// Continues looping until gameRunning is set to false (e.g., on game completion or player death).
void GameManager::run() {
    while (gameRunning) {
        displayBanner();
        cout << "1. New Game.\n";
        cout << "2. Load Game.\n\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cin.clear();
            cin.ignore(1000, '\n');
           createPlayer();
            system("Pause");
            system("cls");
            displayMenu();
        }
        else if(choice == 2){
            loadGame();
        }
    }
}

// Creates a new player character based on user input.
// Prompts for the player's name and class choice (Warrior, Mage, or Ranger).
// Validates class choice (1-3); defaults to Warrior on invalid input via exception handling.
// Allocates a new player object of the chosen class with the provided name.
// Clears input buffer after reading the class choice to prevent input issues.
// Uses try-catch to handle invalid class selections gracefully.
void GameManager::createPlayer() {
    string name;
    cout << "\nEnter player name: ";
    getline(cin, name);
    int classChoice;
    cout << "\n1: Warrior\n2: Mage\n3: Ranger\n";
    cout << "Choose class: ";
    cin >> classChoice;
    cin.ignore();
    try {
        switch (classChoice) {
        case 1:
            player = new Warrior(name);
            break;
        case 2:
            player = new Mage(name);
            break;
        case 3:
            player = new Ranger(name);
            break;
        default:
            throw exception("Invalid class choice");
        }
        player->displayStats();
    }
    catch (const exception& e) {
        cout << e.what() << ". Defaulting to Warrior.\n";
        player = new Warrior(name);
    }
}

// Displays the main game menu with options for exploration, stats, shop, inventory, and more.
// Presents a visually appealing ASCII art header with the game title.
// Offers 8 options: explore map, view stats, visit shop, view inventory, view battle history, save/load game, and exit.
// Clears the screen before and after each action for a clean interface; pauses for user review.
// Handles user input, executing the corresponding action or reporting invalid choices.
// Calls finalScoreReport on exit (option 8) to show the game summary.
// Loops until gameRunning is false or the player chooses to exit.
void GameManager::displayMenu() {
    int choice;
    do {
        cout << "\n";
        cout << string(60, '=') << "\n";
        cout << "||                                                        ||\n";
        cout << "||                  LEGENDS  OF  VALOR                    ||\n";
        cout << "||                                                        ||\n";
        cout << string(60, '=') << "\n";
        cout << "\n";
        cout << "1. Explore Map\n";
        cout << "2. View Player Stats\n";
        cout << "3. Visit Shop\n";
        cout << "4. View Inventory\n";
        cout << "5. View Battle History\n";
        cout << "6. Save Game\n";
        cout << "7. Load Game\n";
        cout << "8. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            selectPlace();
            system("cls");
            break;
        case 2:
            system("cls");
            player->displayStats();
            system("pause");
            system("cls");
            break;
        case 3:
            shop();
            system("cls");
            break;
        case 4:
            system("cls");
            cout << *(player->getInventory());
            system("pause");
            system("cls");
            break;
        case 5:
            system("cls");
            viewBattleHistory();
            system("pause");
            system("cls");
            break;
        case 6:
            system("cls");
            saveGame();
            system("pause");
            system("cls");
            break;
        case 7:
            system("cls");
            loadGame();
            system("pause");
            system("cls");
            break;
        case 8:
            cout << "Exiting game...\n";
            gameRunning = false;
            system("pause");
            system("cls");
            finalScoreReport();
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (gameRunning && choice != 8);
}

// Simulates exploration in the current place (Forest, Village, Castle, or Desert).
// Checks if the player is alive; ends the game if not, setting gameRunning to false.
// Displays the current place's name based on its PLACES enum value.
// If all enemies are defeated and the boss is not, triggers a boss fight via fightFinalBoss.
// Uses random encounters (0-99) to determine events: 30% chance for enemy fight, 30% for finding an object, 20% for a secret, 20% for nothing.
// For enemy encounters: selects a random enemy, initiates combat, and removes the enemy if defeated, granting 50 XP.
// For object encounters: allows the player to pick up a HelpingObject, increasing quantity if already owned or adding to inventory if space allows.
// For secrets: grants 20 XP and increments secretsFound counter.
// Outputs appropriate messages for each event, enhancing immersion.
void GameManager::exploreMap() {
    if (!player->isAlive()) {
        cout << "Player is dead. Game Over.\n";
        gameRunning = false;
        return;
    }
    if (!currentPlace) return; 


    cout << "\nExploring " << (currentPlace->getPlace() == PLACES::FOREST ? "Forest" :
        currentPlace->getPlace() == PLACES::VILLAGE ? "Village" :
        currentPlace->getPlace() == PLACES::CASTLE ? "Castle" : "Desert") << "!\n";


    if (currentPlace->getTotalEnemies() == 0 && !currentPlace->isBossDefeated()) {
        cout << "All enemies defeated! Prepare to face the boss!\n";
        fightFinalBoss();
        return;
    }

    int encounter = rand() % 100;
    if (encounter < 30 && currentPlace->getTotalEnemies() > 0) {
        int enemyIndex = rand() % currentPlace->getTotalEnemies();
        Character* enemy = currentPlace->getEnemy(enemyIndex);
        cout << "You encounter a " << enemy->getName() << "!\n";
        fightEnemy(enemy);
        if (enemy->isAlive()) {
            cout << enemy->getName() << " defeated you!\n";
        }
        else {
            cout << "You defeated " << enemy->getName() << "!\n";
            player->gainXP(50);
            currentPlace->removeEnemy(enemyIndex);
        }
    }
    else if (encounter < 60 && currentPlace->getTotalObjects() > 0) {
        int objectIndex = rand() % currentPlace->getTotalObjects();
        HelpingObject* object = currentPlace->getObject(objectIndex);
        cout << "You found a " << object->getName() << "! Pick it up? (1: Yes, 2: No): ";
        int pickChoice;
        cin >> pickChoice;
        if (pickChoice == 1) {
            int itemIndex = player->getInventory()->getItemIndex(object->getName());
            if (itemIndex != -1) {
               
                player->getInventory()->getItem(itemIndex)->setQuantity(
                    player->getInventory()->getItem(itemIndex)->getQuantity() + 1);
                cout << "Increased quantity of " << object->getName() << " in inventory.\n";
                currentPlace->removeObject(objectIndex);
            }
            else if (player->getInventory()->getItemCount() < 10) {
             
                HelpingObject* newItem = new HelpingObject(*object);
                newItem->setQuantity(1);
                player->getInventory()->addItem(newItem);
                cout << object->getName() << " added to inventory.\n";
                currentPlace->removeObject(objectIndex);
            }
            else {
                cout << "Inventory full! Cannot pick up " << object->getName() << ".\n";
            }
        }
    }
    else if (encounter < 80) {
        cout << "You discovered a secret!\n";
        player->gainXP(20);
        secretsFound++;
        cout << "Gained 20 XP. Total secrets found: " << secretsFound << "\n";
    }
    else {
        cout << "Nothing interesting happens.\n";
    }
}
// Allows the player to choose a place to explore (Forest, Village, Castle, Desert) or return to the main menu.
// Displays unlocked/locked status for each place based on placesUnlocked array.
// Validates input (1-5); recursively calls itself on invalid input.
// Creates a new place instance if switching to a different unlocked place, deleting the current one.
// Calls exploreMap to start exploration in the selected place.
// Handles player death by setting gameRunning to false and ending the game.
void GameManager::selectPlace() {
    int choice;
    do {
        if (gameRunning == false) {
            return;
        }
        cout << "\nChoose a place to explore:\n";
        cout << "1. Forest" << (placesUnlocked[0] ? "" : " (Locked)") << "\n";
        cout << "2. Village" << (placesUnlocked[1] ? "" : " (Locked)") << "\n";
        cout << "3. Castle" << (placesUnlocked[2] ? "" : " (Locked)") << "\n";
        cout << "4. Desert" << (placesUnlocked[3] ? "" : " (Locked)") << "\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice (1-5): ";
        cin >> choice;

        if (choice == 5 || gameRunning == false) {
            return;
        }
        else if (choice < 1 || choice > 5) {
            cout << "Invalid choice! Please choose 1-5.\n";
            system("pause");
            system("cls");
        }
        else {
            PLACES newPlace;
            switch (choice) {
            case 1: newPlace = PLACES::FOREST; break;
            case 2: newPlace = PLACES::VILLAGE; break;
            case 3: newPlace = PLACES::CASTLE; break;
            case 4: newPlace = PLACES::DESERT; break;
            default:
                break;
            }
            if (!placesUnlocked[static_cast<int>(newPlace)]) {
                cout << "This place is locked!\n";
                system("pause");
                system("cls");
            }
            else if (currentPlace && currentPlace->getPlace() == newPlace) {
                exploreMap();
                system("pause");
                system("cls");
            }
            else if (currentPlace && static_cast<int>(newPlace) < static_cast<int>(currentPlace->getPlace())) {
                cout << "All the enemies and boss were killed and "
                    << (newPlace == PLACES::FOREST ? "Forest" :
                        newPlace == PLACES::VILLAGE ? "Village" :
                        newPlace == PLACES::CASTLE ? "Castle" : "Desert")
                    << " is cleared!\n";
                system("pause");
                system("cls");
            }
            else {
                if (currentPlace) {
                    delete currentPlace;
                    currentPlace = nullptr;
                }
                switch (newPlace) {
                case PLACES::FOREST: currentPlace = new Forest(player->getLevel()); break;
                case PLACES::VILLAGE: currentPlace = new Village(player->getLevel()); break;
                case PLACES::CASTLE: currentPlace = new Castle(player->getLevel()); break;
                case PLACES::DESERT: currentPlace = new Desert(player->getLevel()); break;
                }
                exploreMap();
                system("pause");
                system("cls");
            }
        }
    } while (true);
}

// Manages a battle between the player and a regular enemy.
// Displays the enemy's name and battle details, logging the encounter in battleDetails string.
// Continues combat while both player and enemy are alive, showing their HP and MP each turn.
// Offers five actions: Attack, Skill, Defensive Skill, Use Item, or Flee; validates user input.
// Executes the chosen action (e.g., player->attack, useHelpingObject); increments itemsUsed for item usage.
// Allows the enemy to counterattack if alive; reduces player defense after defensive skill use.
// Logs the outcome (Won, Lost, or Fled) in battleLog, updating battlesWon on victory.
// Ends the game and shows finalScoreReport if the player dies; updates battleLogCount.
void GameManager::fightEnemy(Character* enemy) {
    cout << "\nBattle: " << enemy->getName() << "!\n";
    string battleDetails = "Battle - " + player->getName()+ " vs " + enemy->getName() + " in " +
        (currentPlace->getPlace() == PLACES::FOREST ? "Forest" :
            currentPlace->getPlace() == PLACES::VILLAGE ? "Village" :
            currentPlace->getPlace() == PLACES::CASTLE ? "Castle" : "Desert");

    while (player->isAlive() && enemy->isAlive()) {
        cout << "\nPlayer: " << player->getHealth() << "/" << player->getMaxHealth()
            << " HP, " << player->getMana() << "/" << player->getMaxMana() << " MP\n";
        enemy->displayStats();
        cout << "1. Attack\n2. Skill\n3. Defensive Skill\n4. Use Item\n5. Flee\nChoose action: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            player->attack(enemy);
        }
        else if (choice == 2) {
            player->useSkill(enemy);
        }
        else if (choice == 3) {
            player->defensiveSkill();
        }
        else if (choice == 4) {
            cout << *(player->getInventory());
            cout << "Enter item ID to use: ";
            int itemIndex;
            cin >> itemIndex;
            player->useHelpingObject(itemIndex - 1);
            itemsUsed++;
        }
        else if (choice == 5) {
            cout << "You fled from the battle!\n";
            battleLog[battleLogCount % 10] = battleDetails + " - Fled";
            battleLogCount++;
            return;
        }
        else {
            cout << "Invalid choice!\n";
            continue;
        }

        if (enemy->isAlive()) {
            enemy->attack(player);
            if (choice == 3) {
                player->setDefense(player->getDefense() / 2);
            }
        }
    }

    string outcome;
    if (player->isAlive() && !enemy->isAlive()) {
        battlesWon++;
        outcome = "Won";
    }
    else if (!player->isAlive()) {
        gameRunning = false;
        outcome = "Lost";
        system("pause");
        system("cls");
        finalScoreReport();
    }
    battleLog[battleLogCount % 10] = battleDetails + " - " + outcome;
    battleLogCount++;
}

// Manages a battle against the place's final boss.
// Checks if a boss exists and is not already defeated; returns if not available.
// Displays the boss's name and battle details, logging the encounter in battleDetails string.
// Continues combat while both player and boss are alive, showing their HP and MP each turn.
// Offers five actions: Attack, Skill, Defensive Skill, Use Item, or Flee; validates user input.
// Executes the chosen action; increments itemsUsed for item usage.
// Allows the boss to counterattack if alive; reduces player defense after defensive skill use.
// On victory: grants 200 XP, marks boss as defeated, increments battlesWon, and calls moveToNextPlace.
// On defeat: ends the game, shows finalScoreReport, and logs the outcome (Won, Lost, or Fled) in battleLog.
void GameManager::fightFinalBoss() {
    FinalBoss* boss = currentPlace->getFinalBoss();
    if (!boss || currentPlace->isBossDefeated()) {
        cout << "No boss to fight!\n";
        return;
    }

    cout << "\nBoss Battle: " << boss->getName() << "!\n";
    string battleDetails = "Boss Battle - " + player->getName() + " vs " + boss->getName() + " in " +
        (currentPlace->getPlace() == PLACES::FOREST ? "Forest" :
            currentPlace->getPlace() == PLACES::VILLAGE ? "Village" :
            currentPlace->getPlace() == PLACES::CASTLE ? "Castle" : "Desert");

    while (player->isAlive() && boss->isAlive()) {
        cout << "\nPlayer: " << player->getHealth() << "/" << player->getMaxHealth()
            << " HP, " << player->getMana() << "/" << player->getMaxMana() << " MP\n";
        boss->displayStats();
        cout << "1. Attack\n2. Skill\n3. Defensive Skill\n4. Use Item\n5. Flee\nChoose action: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            player->attack(boss);
        }
        else if (choice == 2) {
            player->useSkill(boss);
        }
        else if (choice == 3) {
            player->defensiveSkill();
        }
        else if (choice == 4) {
            cout << *(player->getInventory());
            cout << "Enter item ID to use: ";
            int itemIndex;
            cin >> itemIndex;
            player->useHelpingObject(itemIndex - 1);
            itemsUsed++;
        }
        else if (choice == 5) {
            cout << "You fled from the battle!\n";
            battleLog[battleLogCount % 10] = battleDetails + " - Fled";
            battleLogCount++;
            return;
        }
        else {
            cout << "Invalid choice!\n";
            continue;
        }

        if (boss->isAlive()) {
            boss->attack(player);
            if (choice == 3) {
                player->setDefense(player->getDefense() / 2);
            }
        }
    }

    string outcome;
    if (player->isAlive() && !boss->isAlive()) {
        cout << "You defeated " << boss->getName() << "!\n";
        player->gainXP(200);
        currentPlace->setBossDefeated(true);
        battlesWon++;
        outcome = "Won";
        moveToNextPlace();
    }
    else if (!player->isAlive()) {
        cout << "You were defeated by " << boss->getName() << "!\n";
        gameRunning = false;
        outcome = "Lost";
        system("pause");
        system("cls");
        finalScoreReport();
    }
    battleLog[battleLogCount % 10] = battleDetails + " - " + outcome;
    battleLogCount++;
}

// Saves the current game state to a user-specified file.
// Prompts for a filename and writes player data (name, class, stats, inventory), game stats (battlesWon, itemsUsed, secretsFound), and place data (enemies, objects).
// Uses ofstream to write data in a structured format for loading.
// Saves only the current state of enemies and objects, ensuring killed enemies or collected objects are not saved.
// Closes the file and confirms successful saving; reports errors if the file cannot be opened.
void GameManager::saveGame() {
    string filename;
    cout << "Enter the name of the save file: ";
    cin.ignore();
    getline(cin, filename);

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error saving game to " << filename << "!\n";
        return;
    }

    file << player->getName() << "\n";
    file << static_cast<int>(player->getPlayerClass()) << "\n";
    file << player->getHealth() << " " << player->getMaxHealth() << " "
        << player->getMana() << " " << player->getMaxMana() << " ";
    file << player->getAttack() << " " << player->getDefense() << " ";
    file << player->getLevel() << " " << player->getExperience() << " " << player->getGold() << "\n";

    file << player->getInventory()->getItemCount() << "\n";
    for (int i = 0; i < player->getInventory()->getItemCount(); ++i) {
        HelpingObject* item = player->getInventory()->getItem(i);
        file << item->getName() << "\n" << static_cast<int>(item->getType()) << " ";
        file << item->getDescription() << "\n" << item->getQuantity() << " ";
        file << item->getEffectValue() << " " << item->getPrice() << "\n";
    }

    file << battlesWon << " " << itemsUsed << " " << secretsFound << "\n";
    file << static_cast<int>(currentPlace->getPlace()) << " " << currentPlace->isBossDefeated() << "\n";
    for (int i = 0; i < 4; ++i) {
        file << placesUnlocked[i] << " ";
    }
    file << "\n";

    file << currentPlace->getTotalEnemies() << "\n";
    for (int i = 0; i < currentPlace->getTotalEnemies(); ++i) {
        Character* enemy = currentPlace->getEnemy(i);
        file << enemy->getName() << " " << enemy->getHealth() << " "
            << enemy->getAttack() << " " << enemy->getDefense() << "\n";
    }

    file << currentPlace->getTotalObjects() << "\n";
    for (int i = 0; i < currentPlace->getTotalObjects(); ++i) {
        HelpingObject* item = currentPlace->getObject(i);
        file << item->getName() << "\n" << static_cast<int>(item->getType()) << " ";
        file << item->getDescription() << "\n" << item->getQuantity() << " ";
        file << item->getEffectValue() << " " << item->getPrice() << "\n";
    }

    file.close();
    cout << "Game saved successfully to " << filename << ".\n";
}

// Loads a saved game state from a user-specified file.
// Prompts for a filename and reads player data, game stats, and place data using ifstream.
// Reconstructs the player (Warrior, Mage, or Ranger), inventory, and current place (Forest, Village, Castle, or Desert).
// Clears default enemies and objects in the new place before loading saved ones to preserve the exact state (e.g., killed enemies stay dead).
// Handles exceptions for invalid data (e.g., unknown class or place) and reports loading errors.
// Ensures proper memory management by deleting old player and place objects before creating new ones.
void GameManager::loadGame() {
    string filename;
    cout << "Enter the name of the save file: ";
    cin.ignore();
    getline(cin, filename);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\nError in loading game from " << filename << "!\n";
        system("pause");
        system("cls");
        return;
    }

    try {
        string name;
        int classChoice, health, maxHealth, mana, maxMana, attack, defense, level, experience, gold;
        getline(file, name);
        file >> classChoice;
        file >> health >> maxHealth >> mana >> maxMana >> attack >> defense >> level >> experience >> gold;

        delete player;
        switch (classChoice) {
        case 0:
            player = new Warrior(name);
            break;
        case 1:
            player = new Mage(name);
            break;
        case 2:
            player = new Ranger(name);
            break;
        default:
            throw exception("Invalid class in save file");
        }
        player->setHealth(health);
        player->setMaxHealth(maxHealth);
        player->setMana(mana);
        player->setMaxMana(maxMana);
        player->setAttack(attack);
        player->setDefense(defense);
        player->setLevel(level);
        player->setExperience(experience);
        player->setGold(gold);
        player->displayStats();
        int itemCount;
        file >> itemCount;
        Inventory* newInventory = new Inventory();
        for (int i = 0; i < itemCount; ++i) {
            string itemName, desc;
            int type, qty, effect, price;
            file.ignore();
            getline(file, itemName);
            file >> type;
            file.ignore();
            getline(file, desc);
            file >> qty >> effect >> price;
            HelpingObject* item = new HelpingObject(itemName, static_cast<helpingObjects>(type), desc, qty, effect, price);
            newInventory->addItem(item);
        }
        delete player->getInventory();
        player->setInventory(newInventory);

        file >> battlesWon >> itemsUsed >> secretsFound;

        int placeChoice;
        bool bossDefeated;
        file >> placeChoice >> bossDefeated;
        delete currentPlace;
        switch (placeChoice) {
        case 0:
            currentPlace = new Forest(player->getLevel());
            break;
        case 1:
            currentPlace = new Village(player->getLevel());
            break;
        case 2:
            currentPlace = new Castle(player->getLevel());
            break;
        case 3:
            currentPlace = new Desert(player->getLevel());
            break;
        default:
            throw exception("Invalid place in save file");
        }
        currentPlace->setBossDefeated(bossDefeated);
        while (currentPlace->getTotalEnemies() > 0) {
            currentPlace->removeEnemy(0);
        }
        while (currentPlace->getTotalObjects() > 0) {
            currentPlace->removeObject(0);
        }

        for (int i = 0; i < 4; ++i) {
            file >> placesUnlocked[i];
        }

        int enemyCount;
        file >> enemyCount;
        for (int i = 0; i < enemyCount; ++i) {
            string enemyName;
            int hp, atk, def;
            file >> enemyName >> hp >> atk >> def;
            Character* enemy = nullptr;
            switch (currentPlace->getPlace()) {
            case PLACES::FOREST:
                enemy = new ForestEnemy(enemyName, ENEMY::FOREST_ENEMIES::BANDIT, hp, atk, def);
                break;
            case PLACES::VILLAGE:
                enemy = new VillageEnemy(enemyName, ENEMY::VILLAGE_ENEMIES::THUG, hp, atk, def);
                break;
            case PLACES::CASTLE:
                enemy = new CastleEnemy(enemyName, ENEMY::CASTLE_ENEMIES::KNIGHT, hp, atk, def);
                break;
            case PLACES::DESERT:
                enemy = new DesertEnemy(enemyName, ENEMY::DESERT_ENEMIES::RAIDER, hp, atk, def);
                break;
            }
            if (enemy) {
                currentPlace->addEnemy(*enemy);
            }
        }

        int objectCount;
        file >> objectCount;
        for (int i = 0; i < objectCount; ++i) {
            string itemName, desc;
            int type, qty, effect, price;
            file.ignore();
            getline(file, itemName);
            file >> type;
            file.ignore();
            getline(file, desc);
            file >> qty >> effect >> price;
            HelpingObject item(itemName, static_cast<helpingObjects>(type), desc, qty, effect, price);
            currentPlace->addObject(item);
        }

        file.close();
        cout << "Game loaded successfully from " << filename << ".\n";
        system("pause");
        system("cls");
        displayMenu();
    }
    catch (const exception& e) {
        cout << "Error loading game: " << e.what() << "\n";
        file.close();
    }
}

// Displays the last 10 recorded battle logs, showing moves used, enemies fought, and outcomes.
// Shows a formatted header and separator for clarity; reports "No battles recorded" if none exist.
// Iterates through battleLog array, printing non-empty entries.
// Prompts the user to save the history to a file; if chosen, writes the same formatted output to a user-specified file.
// Handles file errors and confirms successful saving, enhancing player engagement with battle tracking.
void GameManager::viewBattleHistory() {
    if (battleLogCount == 0) {
        cout << "No battles recorded.\n";
        return;
    }
    cout << "\nBattle History:\n";
    cout << string(60, '-') << "\n";
    for (int i = 0; i < min(battleLogCount, 10); ++i) {
        if (!battleLog[i].empty()) {
            cout << battleLog[i] << "\n";
        }
    }
    cout << string(60, '-') << "\n";
}

void GameManager::moveToNextPlace() {
    switch (currentPlace->getPlace()) {
    case PLACES::FOREST:
        placesUnlocked[1] = true;
        cout << "Village unlocked!\n";
        break;
    case PLACES::VILLAGE:
        placesUnlocked[2] = true;
        cout << "Castle unlocked!\n";
        break;
    case PLACES::CASTLE:
        placesUnlocked[3] = true;
        cout << "Desert unlocked!\n";
        break;
    case PLACES::DESERT:
        cout << "Congratulations! You've defeated all bosses!\n";
        gameRunning = false;
        finalScoreReport();
        break;
    }
}
// Displays a shop menu where the player can buy items using gold.
// Lists all items from the helpingObjects enum (e.g., Health Potion, Axe, Shield) with ID, name, description, and price.
// Formats output in a table for clarity, showing the player's current gold.
// Handles user input to buy an item or exit; recursively calls shop on invalid input.
// Calls player->buyItem to process purchases, displaying success or failure.
void GameManager::shop() {
    HelpingObject items[] = {
        HelpingObject("Health Potion", helpingObjects::HEALTH, "Restores 30 HP", 1, 30, 50),
        HelpingObject("Power Amulet", helpingObjects::POWER, "Increases attack", 1, 10, 100),
        HelpingObject("Vision Tome", helpingObjects::VISION, "Increases XP gain", 1, 20, 120),
        HelpingObject("Vitality Amulet", helpingObjects::VITALITY, "Increases health", 1, 20, 100),
        HelpingObject("Axe", helpingObjects::AXE, "Increases attack", 1, 15, 80),
        HelpingObject("Shield", helpingObjects::SHIELD, "Increases defense", 1, 10, 90),
        HelpingObject("Armor", helpingObjects::ARMOR, "Increases max health", 1, 25, 110),
        HelpingObject("Horn", helpingObjects::HORN, "Boosts attack and defense", 1, 10, 100),
        HelpingObject("Staff", helpingObjects::STAFF, "Increases max mana", 1, 20, 100),
        HelpingObject("Tome", helpingObjects::TOME, "Increases XP gain", 1, 15, 100),
        HelpingObject("Amulet", helpingObjects::AMULET, "Increases max mana", 1, 15, 90),
        HelpingObject("Cloak", helpingObjects::CLOAK, "Special effect", 1, 10, 80),
        HelpingObject("Bow", helpingObjects::BOW, "Increases attack", 1, 12, 85),
        HelpingObject("Quiver", helpingObjects::QUIVER, "Increases attack", 1, 10, 70),
        HelpingObject("Boots", helpingObjects::BOOTS, "Special effect", 1, 10, 75),
        HelpingObject("Trap", helpingObjects::TRAP, "Deals damage to enemies", 1, 20, 60),
        HelpingObject("Speed Potion", helpingObjects::SPEED, "Special effect", 1, 10, 70)
    };
    while (true) {
        system("cls");
        cout << "\nWelcome to the Shop!   Gold: " << player->getGold() << "\n";
        cout << "Available Items:\n";
        cout << string(65, '-') << "\n";
        cout << left << setw(5) << "ID" << setw(20) << "Item" << setw(30) << "Description" << setw(10) << "Price" << "\n";
        cout << string(65, '-') << "\n";
        for (int i = 0; i < 16; ++i) {
            cout << left << setw(5) << (i + 1) << setw(20) << items[i].getName()
                << setw(30) << items[i].getDescription() << setw(10) << items[i].getPrice() << "\n";
        }
        cout << "17. Exit Shop\n";
        cout << "Enter choice (1-17): ";
        int choice;
        cin >> choice;

        if (choice == 17) {
            cout << "Leaving the shop.\n";
            return;
        }

        else if (choice < 1 || choice > 17) {
            cout << "Invalid choice! Please choose 1-17.\n";
        }
        else {

            int itemIndex = choice - 1;
            HelpingObject& item = items[itemIndex];

            if (player->getGold() < item.getPrice()) {
                cout << "Not enough gold to buy " << item.getName() << "!\n";
            }
            else {
                cout << "Buy " << item.getName() << " for " << item.getPrice()
                    << " gold? (1: Yes, 2: No): ";
                int buyChoice;
                cin >> buyChoice;

                if (buyChoice == 1) {
              
                    int totalQuantity = 0;
                    for (int i = 0; i < player->getInventory()->getItemCount(); ++i) {
                        totalQuantity += player->getInventory()->getItem(i)->getQuantity();
                    }

                    if (totalQuantity < 10) {
                        int existingIndex = player->getInventory()->getItemIndex(item.getName());
                        if (existingIndex != -1) {
                            player->getInventory()->getItem(existingIndex)->setQuantity(
                                player->getInventory()->getItem(existingIndex)->getQuantity() + 1);
                            cout << item.getName() << " added to inventory.\n";
                            player->setGold(player->getGold() - item.getPrice());
                            system("pause");
                        }
                        else if (player->getInventory()->getItemCount() < 10) {
         
                            HelpingObject* newItem = new HelpingObject(item);
                            newItem->setQuantity(1);
                            player->getInventory()->addItem(newItem);
                            cout << item.getName() << " added to inventory.\n";
                            player->setGold(player->getGold() - item.getPrice());
                            system("pause");
                        }
                        else {
                            cout << "Inventory full! Cannot add new item type for " << item.getName() << ".\n";
                            system("pause");
                        }
                    }
                    else {
                        cout << "Inventory full! Total item quantity limit reached.\n";
                        system("pause");
                    }
                }
                else {
                    cout << "Purchase cancelled.\n";
                    system("pause");
                }
            }
        }
    }
}

// Shows player stats (name, level, XP), game stats (battles won, items used, secrets found), and game status.
// Aligns data with setw for consistent spacing within vertical bar borders.
// Prompts to save the report to a user-specified file, writing the same formatted output if chosen.
// Handles file errors and confirms successful saving; encourages replayability with a thematic message.
void GameManager::finalScoreReport() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "||                  FINAL SCORE REPORT                     ||\n";
    cout << "||                   Legends of Valor                      ||\n";
    cout << string(60, '=') << "\n";
    cout << "||                                                         ||\n";
    cout << "|| Name : " << left << setw(50) << player->getName() << "||\n";
    cout << "|| Level: " << left << setw(49) << player->getLevel() << "||\n";
    cout << "|| Total XP: " << left << setw(46) << player->getExperience() << "||\n";
    cout << "|| Battles Won: " << left << setw(43) << battlesWon << "||\n";
    cout << "|| Items Used: " << left << setw(44) << itemsUsed << "||\n";
    cout << "|| Secrets Found: " << left << setw(41) << secretsFound << "||\n";
    cout << "|| Game Status: " << left << setw(43) << (gameRunning ? "Completed" : "Game Over") << "||\n";
    cout << "||                                                         ||\n";
    cout << string(60, '=') << "\n\n";

    cout << "Would you like to save this report to a file? (1: Yes, 2: No): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string filename;
        cout << "Enter the name of the file to save the report: ";
        cin.ignore();
        getline(cin, filename);

        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error saving report to " << filename << "!\n";
            return;
        }

        file << string(60, '=') << "\n";
        file << "||                  FINAL SCORE REPORT                     ||\n";
        file << "||                   Legends of Valor                      ||\n";
        file << string(60, '=') << "\n";
        file << "||                                                         ||\n";
        file << "|| Name: " << left << setw(50) << player->getName() << "||\n";
        file << "|| Level: " << left << setw(49) << player->getLevel() << "||\n";
        file << "|| Total XP: " << left << setw(46) << player->getExperience() << "||\n";
        file << "|| Battles Won: " << left << setw(43) << battlesWon << "||\n";
        file << "|| Items Used: " << left << setw(44) << itemsUsed << "||\n";
        file << "|| Secrets Found: " << left << setw(41) << secretsFound << "||\n";
        file << "|| Game Status: " << left << setw(43) << (gameRunning ? "Completed" : "Game Over") << "||\n";
        file << "||                                                         ||\n";
        file << string(60, '=') << "\n";

        file.close();
        cout << "Report saved successfully to " << filename << ".\n";
    }

    cout << "Thank you for playing Legends of Valor! Try again to etch a greater legend!\n\n";
}

//banner for "Welcome to Legends of Valor" at game start.
void displayBanner() {
    cout << "\n";
    cout << string(60, '=') << "\n";
    cout << "||                                                        ||\n";
    cout << "||         WELCOME TO LEGENDS OF VALOR                    ||\n";
    cout << "||                                                        ||\n";
    cout << string(60, '=') << "\n";
    cout << "\n";
}