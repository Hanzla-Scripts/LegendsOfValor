#include "24F-0505_24F-0580_Classes.h"
using namespace std;

Character::Character(const string& n, int hp, int atk, int def)
    : name(n), health(hp), maxHealth(hp), Attack(atk), defense(def) {
}
int Player::playerCount = 0;

Player::Player(const string& n, PLAYER_CLASS pc, int hp, int mp, int atk, int def, int lvl)
    : Character(n, hp, atk, def), playerClass(pc), inventory(new Inventory()),
    mana(mp), maxMana(mp), level(lvl), experience(0), gold(0) {
    playerCount++;
}

Player::Player(const Player& other)
    : Character(other.getName(), other.getHealth(), other.getAttack(), other.getDefense()),
    playerClass(other.getPlayerClass()), inventory(new Inventory(*other.getInventory())),
    mana(other.getMana()), maxMana(other.getMaxMana()), level(other.getLevel()),
    experience(other.getExperience()), gold(other.getGold()) {
    playerCount++;
}

Player::~Player() {
    delete inventory;
    playerCount--;
}

void Player::displayStats() const {
    cout << *this;
}

void Player::attack(Character* target) {
    int damage = getAttack() + (rand() % 10);
    cout << getName() << " attacks " << target->getName() << " for " << damage << " damage!\n";
    target->takeDamage(damage);
}

void Player::takeDamage(int damage) {
    int actualDamage = damage - getDefense();
    if (actualDamage < 0) actualDamage = 0;
    setHealth(getHealth() - actualDamage);
    if (getHealth() < 0) setHealth(0);
    cout << getName() << " takes " << actualDamage << " damage! Health: " << getHealth() << "/" << getMaxHealth() << "\n";
}

void Player::levelUp() {
    setLevel(getLevel() + 1);
    setMaxHealth(getMaxHealth() + 30);
    setHealth(getMaxHealth());
    setMaxMana(getMaxMana() + 10);
    setMana(getMaxMana());
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 3);
    cout << getName() << " leveled up to " << getLevel() << "!\n";
}

void Player::gainXP(int xp) {
    setExperience(getExperience() + xp);
    int xpNeeded = getLevel() * 100;
    while (getExperience() >= xpNeeded) {
        setExperience(getExperience() - xpNeeded);
        levelUp();
        xpNeeded = getLevel() * 100;
    }
}

void Player::useHelpingObject(int index) {
    if (index < 0 || index >= getInventory()->getItemCount()) {
        cout << "Invalid item index!\n";
        return;
    }
    HelpingObject* item = getInventory()->getItem(index);
    if (!item) {
        cout << "Error: Invalid item!\n";
        return;
    }
    string itemName = item->getName(); 
    if (getInventory()->useItem(index, this)) {
        if (item->getQuantity() > 1) {
            item->setQuantity(item->getQuantity() - 1);
            cout << itemName << " used. " << item->getQuantity() << " remaining.\n";
        }
        else {
            getInventory()->removeItem(index);
            cout << itemName << " used and removed from inventory.\n";
        }
    }
}

void Player::useSkill(Character* target) {
    if (getMana() < 20) {
        cout << "Not enough mana!\n";
        return;
    }
    setMana(getMana() - 20);
    int damage = getAttack() * 2;
    switch (getPlayerClass()) {
    case PLAYER_CLASS::WARRIOR:
        cout << getName() << " uses Power Slash, dealing " << damage << " damage!\n";
        target->takeDamage(damage);
        break;
    case PLAYER_CLASS::MAGE:
        cout << getName() << " casts Fireball, dealing " << damage << " damage!\n";
        target->takeDamage(damage);
        break;
    case PLAYER_CLASS::RANGER:
        cout << getName() << " shoots Crippling Arrow, dealing " << damage << " damage and reducing defense!\n";
        target->takeDamage(damage);
        target->setDefense(max(0, target->getDefense() - 5));
        cout << target->getName() << "'s defense reduced to " << target->getDefense() << "!\n";
        break;
    }
}

void Player::defensiveSkill() {
    if (getMana() < 20) {
        cout << "Not enough mana!\n";
        return;
    }
    setMana(getMana() - 20);
    switch (getPlayerClass()) {
    case PLAYER_CLASS::WARRIOR:
        setDefense(getDefense() * 2);
        cout << getName() << " uses Iron Stance, increasing defense to " << getDefense() << "!\n";
        break;
    case PLAYER_CLASS::MAGE:
        setDefense(getDefense() * 2);
        setMana(getMana() + 10);
        if (getMana() > getMaxMana()) setMana(getMaxMana());
        cout << getName() << " casts Arcane Shield, increasing defense to " << getDefense()
            << " and restoring 10 mana!\n";
        break;
    case PLAYER_CLASS::RANGER:
        setDefense(getDefense() * 2);
        setMana(getMana() + 10);
        if (getMana() > getMaxMana()) setMana(getMaxMana());
        cout << getName() << " performs Evasive Maneuver, increasing defense to " << getDefense()
            << " and restoring 10 mana!\n";
        break;
    }
}

void Player::heal(int amount) {
    setHealth(getHealth() + amount);
    if (getHealth() > getMaxHealth()) setHealth(getMaxHealth());
    cout << getName() << " heals for " << amount << "! Health: " << getHealth() << "/" << getMaxHealth() << "\n";
}

bool Player::addItem(const HelpingObject& item) {
    HelpingObject* newItem = new HelpingObject(item);
    getInventory()->addItem(newItem);
    cout << item.getName() << " added to inventory.\n";
    return true;
}

bool Player::removeItem(const string& itemName) {
    int index = getInventory()->getItemIndex(itemName);
    if (index == -1) {
        cout << "Item not found!\n";
        return false;
    }
    getInventory()->removeItem(index);
    cout << itemName << " removed from inventory.\n";
    return true;
}

void Player::showInventory() const {
   cout << getInventory();
}

bool Player::buyItem(const HelpingObject& item) {
    if (getGold() < item.getPrice()) {
        cout << "Not enough gold!\n";
        return false;
    }
    if (!addItem(item)) {
        cout << "Inventory full!\n";
        return false;
    }
    setGold(getGold() - item.getPrice());
    cout << "Bought " << item.getName() << " for " << item.getPrice() << " gold.\n";
    return true;
}

ostream& operator<<(ostream& os, const Player& player) {
    cout << "\n" << string(35, '=') << "\n";
    cout << setw(35) << left << "          Player Stats          " << "\n";
    cout << string(35, '-') << "\n";
    cout << setw(15) << left << "Name:" << setw(20) << right << player.getName() << "\n";
    cout << setw(15) << left << "Class:" << setw(20) << right
        << (player.getPlayerClass() == PLAYER_CLASS::WARRIOR ? "Warrior" :
            player.getPlayerClass() == PLAYER_CLASS::MAGE ? "Mage" : "Ranger") << "\n";
    cout << setw(15) << left << "Level:" << setw(20) << right << player.getLevel() << "\n";
    cout << setw(15) << left << "Experience:" << setw(20) << right << player.getExperience() << "\n";
    cout << string(35, '-') << "\n";
    cout << setw(15) << left << "Health:" << setw(16) << right
        << player.getHealth() << "/" << player.getMaxHealth() << "\n";
    cout << setw(15) << left << "Mana:" << setw(17) << right
        << player.getMana() << "/" << player.getMaxMana() << "\n";
    cout << setw(15) << left << "Attack:" << setw(20) << right << player.getAttack() << "\n";
    cout << setw(15) << left << "Defense:" << setw(20) << right << player.getDefense() << "\n";
    cout << string(35, '-') << "\n";
    cout << setw(15) << left << "Gold:" << setw(20) << right << player.getGold() << "\n";
    cout << string(35, '=') << "\n\n";
    return os;
}

Warrior::Warrior(const string& name)
    : Player(name, PLAYER_CLASS::WARRIOR, 200, 50, 20, 15, 1) {
}

Mage::Mage(const string& name)
    : Player(name, PLAYER_CLASS::MAGE, 150, 100, 15, 10, 1) {
}

Ranger::Ranger(const string& name)
    : Player(name, PLAYER_CLASS::RANGER, 150, 70, 18, 12, 1) {
}

