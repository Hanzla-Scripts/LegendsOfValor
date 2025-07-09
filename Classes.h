#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include<stdexcept>
using namespace std;

// Forward Declarations
class Inventory;
class HelpingObject;
class Character;
class Player;
class Warrior;
class Mage;
class Ranger;
class Places;
class Forest;
class Village;
class Castle;
class Desert;
class GameManager;

// Enums
enum class PLACES { FOREST, VILLAGE, CASTLE, DESERT };
enum class PLAYER_CLASS { WARRIOR, MAGE, RANGER };
struct ENEMY {
    enum class FOREST_ENEMIES { BANDIT, ARCHER, DRUID, SCOUT };
    enum class VILLAGE_ENEMIES { THUG, TRAPPER, ZEALOT, ARSONIST };
    enum class CASTLE_ENEMIES { KNIGHT, SORCERER, GOLEM, ASSASSIN };
    enum class DESERT_ENEMIES { RAIDER, NOMAD, CULTIST, MERCENARY };
};
enum class helpingObjects {
    AXE, SHIELD, ARMOR, HORN, STAFF, TOME, AMULET, CLOAK, BOW,
    QUIVER, BOOTS, TRAP, HEALTH, POWER, SPEED, VISION, VITALITY
};

class Character {
protected:
    string name;
    int health;
    int maxHealth;
    int Attack;
    int defense;

public:
    Character(const string& n, int hp, int atk, int def);
    virtual ~Character() = default;
    virtual void displayStats() const = 0;
    virtual void attack(Character* target) = 0;
    virtual bool isAlive() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual string getName() const { return name; }
    virtual int getHealth() const { return health; }
    virtual int getMaxHealth() const { return maxHealth; }
    virtual int getAttack() const { return Attack; }
    virtual int getDefense() const { return defense; }
    virtual void setName(const string& n) { name = n; }
    virtual void setHealth(int h) { health = h; }
    virtual void setMaxHealth(int mh) { maxHealth = mh; }
    virtual void setAttack(int a) { Attack = a; }
    virtual void setDefense(int d) { defense = d; }
};

class Player : public Character {
private:
    PLAYER_CLASS playerClass;
    static int playerCount;
    Inventory* inventory;
    int mana;
    int maxMana;
    int level;
    int experience;
    int gold;

public:
    Player(const string& n, PLAYER_CLASS pc, int hp, int mp, int atk, int def, int lvl);
    Player(const Player& other);
    ~Player();

    PLAYER_CLASS getPlayerClass() const { return playerClass; }
    Inventory* getInventory() const { return inventory; }
    int getMana() const { return mana; }
    int getMaxMana() const { return maxMana; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    int getGold() const { return gold; }
    void setPlayerClass(PLAYER_CLASS pc) { playerClass = pc; }
    void setInventory(Inventory* inv) { inventory = inv; }
    void setMana(int m) { mana = m; }
    void setMaxMana(int mm) { maxMana = mm; }
    void setLevel(int l) { level = l; }
    void setExperience(int exp) { experience = exp; }
    void setGold(int g) { gold = g; }

    void gainXP(int xp);
    void useHelpingObject(int index);
    void useSkill(Character* target);
    void defensiveSkill();
    void heal(int amount);

    void displayStats() const override;
    void attack(Character* target) override;
    bool isAlive() const override { return getHealth() > 0; }
    void takeDamage(int damage) override;
    string getName() const override { return Character::getName(); }
    int getHealth() const override { return Character::getHealth(); }

    bool addItem(const HelpingObject& item);
    bool removeItem(const string& itemName);
    void showInventory() const;
    bool buyItem(const HelpingObject& item);

    static int getPlayerCount() { return playerCount; }
    friend ostream& operator<<(ostream& os, const Player& player);

protected:
    void levelUp();
};

class Warrior : public Player {
public:
    Warrior(const string& name);
};

class Mage : public Player {
public:
    Mage(const string& name);
};

class Ranger : public Player {
public:
    Ranger(const string& name);
};

class ForestEnemy : public Character {
private:
    ENEMY::FOREST_ENEMIES type;
public:
    ForestEnemy(const string& n, ENEMY::FOREST_ENEMIES t, int hp, int atk, int def);
    ~ForestEnemy();
    ENEMY::FOREST_ENEMIES getType() const { return type; }
    void setType(ENEMY::FOREST_ENEMIES t) { type = t; }
    void displayStats() const override;
    void attack(Character* target) override;
    void takeDamage(int damage) override;
    bool isAlive() const override { return getHealth() > 0; }
    string getName() const override { return Character::getName(); }
    int getHealth() const override { return Character::getHealth(); }
};

class VillageEnemy : public Character {
private:
    ENEMY::VILLAGE_ENEMIES type;
public:
    VillageEnemy(const string& n, ENEMY::VILLAGE_ENEMIES t, int hp, int atk, int def);
    ~VillageEnemy();
    ENEMY::VILLAGE_ENEMIES getType() const { return type; }
    void setType(ENEMY::VILLAGE_ENEMIES t) { type = t; }
    void displayStats() const override;
    void attack(Character* target) override;
    void takeDamage(int damage) override;
    bool isAlive() const override { return getHealth() > 0; }
    string getName() const override { return Character::getName(); }
    int getHealth() const override { return Character::getHealth(); }
};

class CastleEnemy : public Character {
private:
    ENEMY::CASTLE_ENEMIES type;
public:
    CastleEnemy(const string& n, ENEMY::CASTLE_ENEMIES t, int hp, int atk, int def);
    ~CastleEnemy();
    ENEMY::CASTLE_ENEMIES getType() const { return type; }
    void setType(ENEMY::CASTLE_ENEMIES t) { type = t; }
    void displayStats() const override;
    void attack(Character* target) override;
    void takeDamage(int damage) override;
    bool isAlive() const override { return getHealth() > 0; }
    string getName() const override { return Character::getName(); }
    int getHealth() const override { return Character::getHealth(); }
};

class DesertEnemy : public Character {
private:
    ENEMY::DESERT_ENEMIES type;
public:
    DesertEnemy(const string& n, ENEMY::DESERT_ENEMIES t, int hp, int atk, int def);
    ~DesertEnemy();
    ENEMY::DESERT_ENEMIES getType() const { return type; }
    void setType(ENEMY::DESERT_ENEMIES t) { type = t; }
    void displayStats() const override;
    void attack(Character* target) override;
    void takeDamage(int damage) override;
    bool isAlive() const override { return getHealth() > 0; }
    string getName() const override { return Character::getName(); }
    int getHealth() const override { return Character::getHealth(); }
};

class FinalBoss : public Character {
private:
    PLACES place;
    bool barrierActive;
    int sandstormCounter;

public:
    FinalBoss(const string& n, PLACES p, int hp, int atk, int def);
    ~FinalBoss();
    PLACES getPlace() const { return place; }
    bool getBarrierActive() const { return barrierActive; }
    int getSandstormCounter() const { return sandstormCounter; }
    void setPlace(PLACES p) { place = p; }
    void setBarrierActive(bool ba) { barrierActive = ba; }
    void setSandstormCounter(int sc) { sandstormCounter = sc; }
    void displayStats() const override;
    void attack(Character* target) override;
    void takeDamage(int damage) override;
    bool isAlive() const override { return getHealth() > 0; }
    string getName() const override { return Character::getName(); }
    int getHealth() const override { return Character::getHealth(); }
    void toggleBarrier();
    bool hasBarrier() const { return getBarrierActive(); }
    void triggerSandstorm(Player* player);
};

class HelpingObject {
private:
    string name;
    helpingObjects type;
    string description;
    int quantity;
    int effectValue;
    int price;

public:
    HelpingObject(const string& n = "Empty", helpingObjects t = helpingObjects::HEALTH, const string& desc = "", int qty = 0, int effect = 0, int p = 0);
    HelpingObject(const HelpingObject& other);
    ~HelpingObject();

    string getName() const { return name; }
    helpingObjects getType() const { return type; }
    string getDescription() const { return description; }
    int getQuantity() const { return quantity; }
    int getEffectValue() const { return effectValue; }
    int getPrice() const { return price; }
    void setName(const string& n) { name = n; }
    void setType(helpingObjects t) { type = t; }
    void setDescription(const string& desc) { description = desc; }
    void setQuantity(int qty) { quantity = qty; }
    void setEffectValue(int ev) { effectValue = ev; }
    void setPrice(int p) { price = p; }
};

class Inventory {
private:
    HelpingObject* items[10];
    int itemCount;

public:
    Inventory();
    ~Inventory();
    HelpingObject* getItem(int index) const { return items[index]; }
    int getItemCount() const { return itemCount; }
    void setItem(int index, HelpingObject* item) { items[index] = item; }
    void setItemCount(int count) { itemCount = count; }
    void addItem(HelpingObject* item);
    void removeItem(int index);
    int getItemIndex(const string& name) const;
    bool useItem(int index, Player* player);
    bool isEmpty() const { return getItemCount() == 0; }
    friend ostream& operator<<(ostream& os, const Inventory& inv);
};

class Places {
protected:
    PLACES place;
    int totalEnemies;
    Character* enemies[3];
    int totalObjects;
    HelpingObject* objects[3];
    FinalBoss* finalBoss;
    bool bossDefeated;

public:
    Places(PLACES p);
    virtual ~Places();
    int getTotalEnemies() { return totalEnemies; }
    int getTotalObjects() { return totalObjects; }
    virtual void addEnemy(Character& enemy) = 0;
    virtual void addObject(HelpingObject& object) = 0;
    PLACES getPlace() const { return place; }
    Character* getEnemy(int index) const { return enemies[index]; }
    HelpingObject* getObject(int index) const { return objects[index]; }
    FinalBoss* getFinalBoss() const { return finalBoss; }
    bool isBossDefeated() const { return bossDefeated; }
    void setPlace(PLACES p) { place = p; }
    void setTotalEnemies(int te) { totalEnemies = te; }
    void setEnemy(int index, Character* e) { enemies[index] = e; }
    void setTotalObjects(int to) { totalObjects = to; }
    void setObject(int index, HelpingObject* o) { objects[index] = o; }
    void setFinalBoss(FinalBoss* fb) { finalBoss = fb; }
    void setBossDefeated(bool bd) { bossDefeated = bd; }
    void removeEnemy(int index);
    void removeObject(int index);
};

class Forest : public Places {
public:
    Forest(int playerLevel);
    void addEnemy(Character& enemy) override;
    void addObject(HelpingObject& object) override;
};

class Village : public Places {
public:
    Village(int playerLevel);
    void addEnemy(Character& enemy) override;
    void addObject(HelpingObject& object) override;
};

class Castle : public Places {
public:
    Castle(int playerLevel);
    void addEnemy(Character& enemy) override;
    void addObject(HelpingObject& object) override;
};

class Desert : public Places {
public:
    Desert(int playerLevel);
    void addEnemy(Character& enemy) override;
    void addObject(HelpingObject& object) override;
};

class GameManager {
private:
    Player* player;
    Places* currentPlace;
    bool gameRunning;
    string battleLog[10];
    int battleLogCount;
    int battlesWon;
    int itemsUsed;
    int secretsFound;
    bool placesUnlocked[4];

public:
    GameManager();
    ~GameManager();
    void run();

private:
    void createPlayer();
    void displayMenu();
    void exploreMap();
    void selectPlace();
    void fightEnemy(Character* enemy);
    void fightFinalBoss();
    void saveGame();
    void loadGame();
    void viewBattleHistory();
    void finalScoreReport();
    void shop();
    void moveToNextPlace();

};

void displayBanner();