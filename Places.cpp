#include "24F-0505_24F-0580_Classes.h"
using namespace std;

Places::Places(PLACES p) : place(p), totalEnemies(0), totalObjects(0), finalBoss(nullptr), bossDefeated(false) {
    for (int i = 0; i < 3; ++i) {
        setEnemy(i, nullptr);
        setObject(i, nullptr);
    }
}

Places::~Places() {
    for (int i = 0; i < totalEnemies; ++i) {
        delete enemies[i];
    }
    for (int i = 0; i < totalObjects; ++i) {
        delete objects[i];
    }
    delete finalBoss;
}

void Places::removeEnemy(int index) {
    if (index < 0 || index >= totalEnemies) return;
    delete enemies[index];
    for (int i = index; i < totalEnemies - 1; ++i) {
        enemies[i] = enemies[i + 1];
    }
    enemies[totalEnemies - 1] = nullptr;
    totalEnemies--;
}

void Places::removeObject(int index) {
    if (index < 0 || index >= totalObjects) return;
    delete objects[index];
    for (int i = index; i < totalObjects - 1; ++i) {
        objects[i] = objects[i + 1];
    }
    objects[totalObjects - 1] = nullptr;
    totalObjects--;
}

Forest::Forest(int playerLevel) : Places(PLACES::FOREST) {
    setFinalBoss(new FinalBoss("Sylvan Overlord", PLACES::FOREST, 200, 25, 15));
    addEnemy(*new ForestEnemy("Bandit", ENEMY::FOREST_ENEMIES::BANDIT, 50 + playerLevel * 10, 15 + playerLevel * 2, 10));
    addEnemy(*new ForestEnemy("Archer", ENEMY::FOREST_ENEMIES::ARCHER, 40 + playerLevel * 8, 18 + playerLevel * 3, 8));
    addEnemy(*new ForestEnemy("Druid", ENEMY::FOREST_ENEMIES::DRUID, 45 + playerLevel * 9, 16 + playerLevel * 2, 9));
    HelpingObject healthPotion("Health Potion", helpingObjects::HEALTH, "Restores 30 HP", 1, 30, 50);
    HelpingObject vitalityAmulet("Vitality Amulet", helpingObjects::VITALITY, "Increases health", 1, 20, 100);
    HelpingObject axe("Axe", helpingObjects::AXE, "Increases attack", 1, 15, 80);
    addObject(healthPotion);
    addObject(vitalityAmulet);
    addObject(axe);
}

void Forest::addEnemy(Character& enemy) {
    if (getTotalEnemies() < 5) {
        setEnemy(getTotalEnemies(), &enemy);
        setTotalEnemies(getTotalEnemies() + 1);
    }
}

void Forest::addObject(HelpingObject& object) {
    if (getTotalObjects() < 5) {
        setObject(getTotalObjects(), new HelpingObject(object));
        setTotalObjects(getTotalObjects() + 1);
    }
}

Village::Village(int playerLevel) : Places(PLACES::VILLAGE) {
    setFinalBoss(new FinalBoss("Rebel Warlord", PLACES::VILLAGE, 250, 30, 20));
    addEnemy(*new VillageEnemy("Thug", ENEMY::VILLAGE_ENEMIES::THUG, 60 + playerLevel * 12, 18 + playerLevel * 3, 12));
    addEnemy(*new VillageEnemy("Trapper", ENEMY::VILLAGE_ENEMIES::TRAPPER, 50 + playerLevel * 10, 20 + playerLevel * 4, 10));
    addEnemy(*new VillageEnemy("Zealot", ENEMY::VILLAGE_ENEMIES::ZEALOT, 55 + playerLevel * 11, 19 + playerLevel * 3, 11));
    HelpingObject powerAmulet("Power Amulet", helpingObjects::POWER, "Increases attack", 1, 10, 100);
    HelpingObject healthPotion("Health Potion", helpingObjects::HEALTH, "Restores 30 HP", 1, 30, 50);
    HelpingObject Bow("Bow", helpingObjects::BOW, "Increases attack", 1, 12, 85);
    addObject(powerAmulet);
    addObject(healthPotion);
    addObject(Bow);
}

void Village::addEnemy(Character& enemy) {
    if (getTotalEnemies() < 5) {
        setEnemy(getTotalEnemies(), &enemy);
        setTotalEnemies(getTotalEnemies() + 1);
    }
}

void Village::addObject(HelpingObject& object) {
    if (getTotalObjects() < 5) {
        setObject(getTotalObjects(), new HelpingObject(object));
        setTotalObjects(getTotalObjects() + 1);
    }
}

Castle::Castle(int playerLevel) : Places(PLACES::CASTLE) {
    setFinalBoss(new FinalBoss("Dark Monarch", PLACES::CASTLE, 300, 35, 25));
    addEnemy(*new CastleEnemy("Knight", ENEMY::CASTLE_ENEMIES::KNIGHT, 70 + playerLevel * 15, 20 + playerLevel * 4, 15));
    addEnemy(*new CastleEnemy("Sorcerer", ENEMY::CASTLE_ENEMIES::SORCERER, 60 + playerLevel * 12, 22 + playerLevel * 5, 12));
    addEnemy(*new CastleEnemy("Golem", ENEMY::CASTLE_ENEMIES::GOLEM, 80 + playerLevel * 18, 18 + playerLevel * 3, 18));
    addEnemy(*new CastleEnemy("Assassin", ENEMY::CASTLE_ENEMIES::ASSASSIN, 65 + playerLevel * 13, 21 + playerLevel * 4, 13));
    HelpingObject visionTome("Vision Tome", helpingObjects::VISION, "Increases XP gain", 1, 20, 120);
    HelpingObject manaPotion("Mana Potion", helpingObjects::HEALTH, "Restores 50 mana", 1, 50, 80);
    HelpingObject Shield("Shield", helpingObjects::SHIELD, "Increases defense", 1, 10, 90);
    addObject(visionTome);
    addObject(manaPotion);
    addObject(Shield);
}

void Castle::addEnemy(Character& enemy) {
    if (getTotalEnemies() < 5) {
        setEnemy(getTotalEnemies(), &enemy);
        setTotalEnemies(getTotalEnemies() + 1);
    }
}

void Castle::addObject(HelpingObject& object) {
    if (getTotalObjects() < 5) {
        setObject(getTotalObjects(), new HelpingObject(object));
        setTotalObjects(getTotalObjects() + 1);
    }
}

Desert::Desert(int playerLevel) : Places(PLACES::DESERT) {
    setFinalBoss(new FinalBoss("Sand Tyrant", PLACES::DESERT, 350, 40, 30));
    addEnemy(*new DesertEnemy("Raider", ENEMY::DESERT_ENEMIES::RAIDER, 80 + playerLevel * 18, 22 + playerLevel * 5, 18));
    addEnemy(*new DesertEnemy("Nomad", ENEMY::DESERT_ENEMIES::NOMAD, 70 + playerLevel * 15, 24 + playerLevel * 6, 15));
    addEnemy(*new DesertEnemy("Cultist", ENEMY::DESERT_ENEMIES::CULTIST, 75 + playerLevel * 16, 23 + playerLevel * 5, 16));
    addEnemy(*new DesertEnemy("Mercenary", ENEMY::DESERT_ENEMIES::MERCENARY, 85 + playerLevel * 20, 25 + playerLevel * 7, 20));
    HelpingObject vitalityAmulet("Vitality Amulet", helpingObjects::VITALITY, "Increases health", 1, 20, 100);
    HelpingObject healthPotion("Health Potion", helpingObjects::HEALTH, "Restores 30 HP", 1, 30, 50);
    HelpingObject Horn("Horn", helpingObjects::HORN, "Boosts attack and defense", 1, 10, 100);
    addObject(vitalityAmulet);
    addObject(healthPotion);
    addObject(Horn);
}

void Desert::addEnemy(Character& enemy) {
    if (getTotalEnemies() < 5) {
        setEnemy(getTotalEnemies(), &enemy);
        setTotalEnemies(getTotalEnemies() + 1);
    }
}

void Desert::addObject(HelpingObject& object) {
    if (getTotalObjects() < 5) {
        setObject(getTotalObjects(), new HelpingObject(object));
        setTotalObjects(getTotalObjects() + 1);
    }
}