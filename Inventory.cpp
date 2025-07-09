
#include "24F-0505_24F-0580_Classes.h"
using namespace std;

Inventory::Inventory() : itemCount(0) {
    for (int i = 0; i < 10; ++i) {
        setItem(i, nullptr);
    }
}

Inventory::~Inventory() {
    for (int i = 0; i < getItemCount(); ++i) {
        delete getItem(i);
    }
}

void Inventory::addItem(HelpingObject* item) {
    if (getItemCount() < 10) {
        setItem(getItemCount(), item);
        setItemCount(getItemCount() + 1);
    }
    else {
        cout << "Inventory full!\n";
        delete item;
    }
}

void Inventory::removeItem(int index) {
    if (index < 0 || index >= getItemCount()) return;
    delete getItem(index);
    for (int i = index; i < getItemCount() - 1; ++i) {
        setItem(i, getItem(i + 1));
    }
    setItem(getItemCount() - 1, nullptr);
    setItemCount(getItemCount() - 1);
}

int Inventory::getItemIndex(const string& name) const {
    for (int i = 0; i < getItemCount(); ++i) {
        if (getItem(i)->getName() == name) {
            return i;
        }
    }
    return -1;
}

bool Inventory::useItem(int index, Player* player) {
    if (index < 0 || index >= getItemCount()) {
        cout << "Invalid item index!\n";
        return false;
    }
    HelpingObject* item = getItem(index);
    switch (item->getType()) {
    case helpingObjects::HEALTH:
        player->heal(item->getEffectValue());
        break;
    case helpingObjects::POWER:
        player->setAttack(player->getAttack() + item->getEffectValue());
        cout << player->getName() << "'s attack increased to " << player->getAttack() << "!\n";
        break;
    case helpingObjects::SPEED:
        cout << "Speed effect not implemented.\n";
        break;
    case helpingObjects::VISION:
        player->gainXP(item->getEffectValue());
        cout << player->getName() << " gains " << item->getEffectValue() << " XP!\n";
        break;
    case helpingObjects::AXE:
        player->setAttack(player->getAttack() + item->getEffectValue());
        cout << player->getName() << "'s attack increased to " << player->getAttack() << "!\n";
        break;
    case helpingObjects::SHIELD:
        player->setDefense(player->getDefense() + item->getEffectValue());
        cout << player->getName() << "'s defense increased to " << player->getDefense() << "!\n";
        break;
    case helpingObjects::ARMOR:
        player->setMaxHealth(player->getMaxHealth() + item->getEffectValue());
        player->setHealth(player->getHealth() + item->getEffectValue());
        cout << player->getName() << "'s max health increased to " << player->getMaxHealth() << "!\n";
        break;
    case helpingObjects::HORN:
        player->setAttack(player->getAttack() + item->getEffectValue());
        player->setDefense(player->getDefense() + item->getEffectValue());
        cout << player->getName() << "'s attack and defense boosted!\n";
        break;
    case helpingObjects::STAFF:
        player->setMaxMana(player->getMaxMana() + item->getEffectValue());
        player->setMana(player->getMana() + item->getEffectValue());
        cout << player->getName() << "'s max mana increased to " << player->getMaxMana() << "!\n";
        break;
    case helpingObjects::TOME:
        player->gainXP(item->getEffectValue());
        cout << player->getName() << " gains " << item->getEffectValue() << " XP!\n";
        break;
    case helpingObjects::AMULET:
        player->setMaxMana(player->getMaxMana() + item->getEffectValue());
        player->setMana(player->getMana() + item->getEffectValue());
        cout << player->getName() << "'s max mana increased to " << player->getMaxMana() << "!\n";
        break;
    case helpingObjects::CLOAK:
        cout << "Cloak effect not implemented.\n";
        break;
    case helpingObjects::BOW:
        player->setAttack(player->getAttack() + item->getEffectValue());
        cout << player->getName() << "'s attack increased to " << player->getAttack() << "!\n";
        break;
    case helpingObjects::QUIVER:
        player->setAttack(player->getAttack() + item->getEffectValue());
        cout << player->getName() << "'s attack increased to " << player->getAttack() << "!\n";
        break;
    case helpingObjects::BOOTS:
        cout << "Boots effect not implemented.\n";
        break;
    case helpingObjects::TRAP:
        cout << player->getName() << " sets a trap, dealing " << item->getEffectValue() << " damage to enemies!\n";
        break;
    case helpingObjects::VITALITY:
        player->setMaxHealth(player->getMaxHealth() + item->getEffectValue());
        player->setHealth(player->getHealth() + item->getEffectValue());
        cout << player->getName() << "'s max health increased to " << player->getMaxHealth() << "!\n";
        break;
    }
    return true;
}

ostream& operator<<(ostream& os, const Inventory& inv) {
    if (inv.getItemCount() == 0) {
        cout << "Inventory is empty.\n";
        return os;
    }
    cout << "Inventory:\n";
    cout << left << setw(5) << "ID" << setw(20) << "Item" << setw(30) << "Description" << setw(10) << "Quantity" << "\n";
    cout << string(65, '-') << "\n";
    for (int i = 0; i < inv.getItemCount(); ++i) {
        HelpingObject* item = inv.getItem(i);
        cout << left << setw(5) << (i + 1) << setw(20) << item->getName()
            << setw(30) << item->getDescription() << setw(10) << item->getQuantity() << "\n";
    }
    return os;
}