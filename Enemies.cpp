
#include "24F-0505_24F-0580_Classes.h"
using namespace std;

ForestEnemy::ForestEnemy(const string& n, ENEMY::FOREST_ENEMIES t, int hp, int atk, int def)
    : Character(n, hp, atk, def), type(t) {
}

ForestEnemy::~ForestEnemy() {}

void ForestEnemy::displayStats() const {
    cout << "Enemy: " << getName() << ", Type: " << (getType() == ENEMY::FOREST_ENEMIES::BANDIT ? "Bandit" :
        getType() == ENEMY::FOREST_ENEMIES::ARCHER ? "Archer" :
        getType() == ENEMY::FOREST_ENEMIES::DRUID ? "Druid" : "Scout") << "\n";
    cout << "Health: " << getHealth() << "/" << getMaxHealth() << ", Attack: " << getAttack()
        << ", Defense: " << getDefense() << "\n";
}

void ForestEnemy::attack(Character* target) {
    int choice = rand() % 100;
    if (getHealth() < getMaxHealth() / 2 && choice < 30) {
        setDefense(getDefense() + 5);
        cout << getName() << " takes a defensive stance, increasing defense to " << getDefense() << "!\n";
        setDefense(getDefense() - 5);
    }
    else if (choice < 60) {
        int damage = getAttack() + (rand() % 10);
        cout << getName() << " attacks " << target->getName() << " for " << damage << " damage!\n";
        target->takeDamage(damage);
    }
    else {
        int damage = getAttack() * 1.5;
        cout << getName() << " uses a special move: ";
        switch (getType()) {
        case ENEMY::FOREST_ENEMIES::BANDIT:
            cout << "Ambush, dealing " << damage << " damage!\n";
            break;
        case ENEMY::FOREST_ENEMIES::ARCHER:
            cout << "Precise Shot, dealing " << damage << " damage!\n";
            break;
        case ENEMY::FOREST_ENEMIES::DRUID:
            cout << "Nature's Wrath, dealing " << damage << " damage!\n";
            break;
        case ENEMY::FOREST_ENEMIES::SCOUT:
            cout << "Swift Strike, dealing " << damage << " damage!\n";
            break;
        }
        target->takeDamage(damage);
        
    }
}

void ForestEnemy::takeDamage(int damage) {
    int actualDamage = damage - getDefense();
    if (actualDamage < 0) actualDamage = 0;
    setHealth(getHealth() - actualDamage);
    if (getHealth() < 0) setHealth(0);
    cout << getName() << " takes " << actualDamage << " damage! Health: " << getHealth() << "/" << getMaxHealth() << "\n";
}

VillageEnemy::VillageEnemy(const string& n, ENEMY::VILLAGE_ENEMIES t, int hp, int atk, int def)
    : Character(n, hp, atk, def), type(t) {
}

VillageEnemy::~VillageEnemy() {}

void VillageEnemy::displayStats() const {
    cout << "Enemy: " << getName() << ", Type: " << (getType() == ENEMY::VILLAGE_ENEMIES::THUG ? "Thug" :
        getType() == ENEMY::VILLAGE_ENEMIES::TRAPPER ? "Trapper" :
        getType() == ENEMY::VILLAGE_ENEMIES::ZEALOT ? "Zealot" : "Arsonist") << "\n";
    cout << "Health: " << getHealth() << "/" << getMaxHealth() << ", Attack: " << getAttack()
        << ", Defense: " << getDefense() << "\n";
}

void VillageEnemy::attack(Character* target) {
    int choice = rand() % 100;
    if (getHealth() < getMaxHealth() / 2 && choice < 30) {
        setDefense(getDefense() + 5);
        cout << getName() << " takes a defensive stance, increasing defense to " << getDefense() << "!\n";
        setDefense(getDefense() - 5);
    }
    else if (choice < 60) {
        int damage = getAttack() + (rand() % 10);
        cout << getName() << " attacks " << target->getName() << " for " << damage << " damage!\n";
        target->takeDamage(damage);
    }
    else {
        int damage = getAttack() * 1.5;
        cout << getName() << " uses a special move: ";
        switch (getType()) {
        case ENEMY::VILLAGE_ENEMIES::THUG:
            cout << "Brutal Slam, dealing " << damage << " damage!\n";
            break;
        case ENEMY::VILLAGE_ENEMIES::TRAPPER:
            cout << "Snare Trap, dealing " << damage << " damage!\n";
            break;
        case ENEMY::VILLAGE_ENEMIES::ZEALOT:
            cout << "Fanatic Charge, dealing " << damage << " damage!\n";
            break;
        case ENEMY::VILLAGE_ENEMIES::ARSONIST:
            cout << "Firebomb, dealing " << damage << " damage!\n";
            break;
        }
        target->takeDamage(damage);
    }
}

void VillageEnemy::takeDamage(int damage) {
    int actualDamage = damage - getDefense();
    if (actualDamage < 0) actualDamage = 0;
    setHealth(getHealth() - actualDamage);
    if (getHealth() < 0) setHealth(0);
    cout << getName() << " takes " << actualDamage << " damage! Health: " << getHealth() << "/" << getMaxHealth() << "\n";
}

CastleEnemy::CastleEnemy(const string& n, ENEMY::CASTLE_ENEMIES t, int hp, int atk, int def)
    : Character(n, hp, atk, def), type(t) {
}

CastleEnemy::~CastleEnemy() {}

void CastleEnemy::displayStats() const {
    cout << "Enemy: " << getName() << ", Type: " << (getType() == ENEMY::CASTLE_ENEMIES::KNIGHT ? "Knight" :
        getType() == ENEMY::CASTLE_ENEMIES::SORCERER ? "Sorcerer" :
        getType() == ENEMY::CASTLE_ENEMIES::GOLEM ? "Golem" : "Assassin") << "\n";
    cout << "Health: " << getHealth() << "/" << getMaxHealth() << ", Attack: " << getAttack()
        << ", Defense: " << getDefense() << "\n";
}

void CastleEnemy::attack(Character* target) {
    int choice = rand() % 100;
    if (getHealth() < getMaxHealth() / 2 && choice < 30) {
        setDefense(getDefense() + 5);
        cout << getName() << " takes a defensive stance, increasing defense to " << getDefense() << "!\n";
        setDefense(getDefense() - 5);
    }
    else if (choice < 60) {
        int damage = getAttack() + (rand() % 10);
        cout << getName() << " attacks " << target->getName() << " for " << damage << " damage!\n";
        target->takeDamage(damage);
    }
    else {
        int damage = getAttack() * 1.5;
        cout << getName() << " uses a special move: ";
        switch (getType()) {
        case ENEMY::CASTLE_ENEMIES::KNIGHT:
            cout << "Heavy Strike, dealing " << damage << " damage!\n";
            break;
        case ENEMY::CASTLE_ENEMIES::SORCERER:
            cout << "Arcane Blast, dealing " << damage << " damage!\n";
            break;
        case ENEMY::CASTLE_ENEMIES::GOLEM:
            cout << "Crushing Blow, dealing " << damage << " damage!\n";
            break;
        case ENEMY::CASTLE_ENEMIES::ASSASSIN:
            cout << "Shadow Strike, dealing " << damage << " damage!\n";
            break;
        }
        target->takeDamage(damage);
    }
}

void CastleEnemy::takeDamage(int damage) {
    int actualDamage = damage - getDefense();
    if (actualDamage < 0) actualDamage = 0;
    setHealth(getHealth() - actualDamage);
    if (getHealth() < 0) setHealth(0);
    cout << getName() << " takes " << actualDamage << " damage! Health: " << getHealth() << "/" << getMaxHealth() << "\n";
}

DesertEnemy::DesertEnemy(const string& n, ENEMY::DESERT_ENEMIES t, int hp, int atk, int def)
    : Character(n, hp, atk, def), type(t) {
}

DesertEnemy::~DesertEnemy() {}

void DesertEnemy::displayStats() const {
    cout << "Enemy: " << getName() << ", Type: " << (getType() == ENEMY::DESERT_ENEMIES::RAIDER ? "Raider" :
        getType() == ENEMY::DESERT_ENEMIES::NOMAD ? "Nomad" :
        getType() == ENEMY::DESERT_ENEMIES::CULTIST ? "Cultist" : "Mercenary") << "\n";
    cout << "Health: " << getHealth() << "/" << getMaxHealth() << ", Attack: " << getAttack()
        << ", Defense: " << getDefense() << "\n";
}

void DesertEnemy::attack(Character* target) {
    int choice = rand() % 100;
    if (getHealth() < getMaxHealth() / 2 && choice < 30) {
        setDefense(getDefense() + 5);
        cout << getName() << " takes a defensive stance, increasing defense to " << getDefense() << "!\n";
        setDefense(getDefense() - 5);
    }
    else if (choice < 60) {
        int damage = getAttack() + (rand() % 10);
        cout << getName() << " attacks " << target->getName() << " for " << damage << " damage!\n";
        target->takeDamage(damage);
    }
    else {
        int damage = getAttack() * 1.5;
        cout << getName() << " uses a special move: ";
        switch (getType()) {
        case ENEMY::DESERT_ENEMIES::RAIDER:
            cout << "Sand Slash, dealing " << damage << " damage!\n";
            break;
        case ENEMY::DESERT_ENEMIES::NOMAD:
            cout << "Dust Storm, dealing " << damage << " damage!\n";
            break;
        case ENEMY::DESERT_ENEMIES::CULTIST:
            cout << "Dark Ritual, dealing " << damage << " damage!\n";
            break;
        case ENEMY::DESERT_ENEMIES::MERCENARY:
            cout << "Blazing Strike, dealing " << damage << " damage!\n";
            break;
        }
        target->takeDamage(damage);
    }
}

void DesertEnemy::takeDamage(int damage) {
    int actualDamage = damage - getDefense();
    if (actualDamage < 0) actualDamage = 0;
    setHealth(getHealth() - actualDamage);
    if (getHealth() < 0) setHealth(0);
    cout << getName() << " takes " << actualDamage << " damage! Health: " << getHealth() << "/" << getMaxHealth() << "\n";
}

FinalBoss::FinalBoss(const string& n, PLACES p, int hp, int atk, int def)
    : Character(n, hp, atk, def), place(p), barrierActive(false), sandstormCounter(0) {
}

FinalBoss::~FinalBoss() {}

void FinalBoss::displayStats() const {
    cout << "Final Boss: " << getName() << "\n";
    cout << "Place: " << (getPlace() == PLACES::FOREST ? "Forest" :
        getPlace() == PLACES::VILLAGE ? "Village" :
        getPlace() == PLACES::CASTLE ? "Castle" : "Desert") << "\n";
    cout << "Health: " << getHealth() << "/" << getMaxHealth() << ", Attack: " << getAttack()
        << ", Defense: " << getDefense() << "\n";
    cout << "Barrier Active: " << (getBarrierActive() ? "Yes" : "No") << ", Sandstorm Counter: " << getSandstormCounter() << "\n";
}

void FinalBoss::attack(Character* target) {
    if (getPlace() == PLACES::DESERT) {
        setSandstormCounter(getSandstormCounter() + 1);
        if (getSandstormCounter() >= 3) {
            triggerSandstorm(dynamic_cast<Player*>(target));
            setSandstormCounter(0);
            return;
        }
    }
    if (getPlace() == PLACES::CASTLE && !getBarrierActive() && rand() % 100 < 20) {
        
        cout << getName() << " raises a magic barrier!\n";
        return;
    }
    int choice = rand() % 100;
    if (choice < 70) {
        int damage = getAttack() + (rand() % 15);
        cout << getName() << " attacks " << target->getName() << " for " << damage << " damage!\n";
        target->takeDamage(damage);
		if (getBarrierActive()) {
            toggleBarrier();
		}
    }
    else {
        int damage = getAttack() * 2;
        cout << getName() << " uses a devastating attack: ";
        switch (getPlace()) {
        case PLACES::FOREST:
            cout << "Overgrowth Crush, dealing " << damage << " damage!\n";
            break;
        case PLACES::VILLAGE:
            cout << "Rebel's Fury, dealing " << damage << " damage!\n";
            break;
        case PLACES::CASTLE:
            cout << "Monarch's Wrath, dealing " << damage << " damage!\n";
            break;
        case PLACES::DESERT:
            cout << "Sandstorm Blitz, dealing " << damage << " damage!\n";
            break;
        }
        target->takeDamage(damage);
        if (getBarrierActive()) {
            toggleBarrier();
        }
    }
}

void FinalBoss::takeDamage(int damage) {
    if (getBarrierActive()) {
        cout << getName() << "'s barrier absorbs the attack!\n";
        return;
    }
    int actualDamage = damage - getDefense();
    if (actualDamage < 0) actualDamage = 0;
    setHealth(getHealth() - actualDamage);
    if (getHealth() < 0) setHealth(0);
    cout << getName() << " takes " << actualDamage << " damage! Health: " << getHealth() << "/" << getMaxHealth() << "\n";
}

void FinalBoss::toggleBarrier() {
    setBarrierActive(!getBarrierActive());
    cout << getName() << (getBarrierActive() ? " raises a barrier!" : " lowers the barrier!") << "\n";
}

void FinalBoss::triggerSandstorm(Player* player) {
    if (player) {
        int damage = getAttack() * 3;
        cout << getName() << " unleashes Sandstorm Surge, dealing " << damage << " damage!\n";
        player->takeDamage(damage);
    }
}