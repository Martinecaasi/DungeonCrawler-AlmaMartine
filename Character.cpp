#include "Character.hpp"
#include <algorithm>
#include <sstream>

// ---------------- Helpers ----------------

std::string Character::toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return (char)std::tolower(c); });
    return s;
}

Character::ClassType Character::parseClass(const std::string& className) {
    std::string c = toLower(className);
    if (c == "warrior") return ClassType::Warrior;
    if (c == "thief")   return ClassType::Thief;
    return ClassType::Mage;
}

std::string Character::classToString(ClassType c) {
    switch (c) {
    case ClassType::Warrior: return "Warrior";
    case ClassType::Thief:   return "Thief";
    case ClassType::Mage:    return "Mage";
    }
    return "Unknown";
}

void Character::defaultStats(ClassType c, int& hp, int& str, int& def) {

    if (c == ClassType::Warrior) { hp = 100; str = 15; def = 10; }
    else if (c == ClassType::Thief) { hp = 60; str = 20; def = 7; }
    else { hp = 40; str = 25; def = 5; }
}

bool Character::isPotionName(const std::string& itemName) {
    std::string n = toLower(itemName);
    return (n == "healthpotion" || n == "strengthpotion" || n == "defensepotion");
}

bool Character::isWeaponName(const std::string& itemName) {
    std::string n = toLower(itemName);
    return (n == "sword" || n == "dagger" || n == "wand");
}

bool Character::isShieldName(const std::string& itemName) {
    std::string n = toLower(itemName);
    return (n == "shield");
}

// ---------------- Ctor / Dtor ----------------

Character::Character(const std::string& className, const std::string& name)
    : name(name),
      cls(parseClass(className)),
      currentRoom(nullptr),
      equippedWeapon(nullptr),
      equippedShield(nullptr)
{
    defaultStats(cls, health, strength, defense);
}

Character::~Character() {
    delete equippedWeapon;
    delete equippedShield;
}

// ---------------- Getters ----------------

const std::string& Character::getName() const {
    return name;
}

Room* Character::getCurrentRoom() const {
    return currentRoom;
}

void Character::setCurrentRoom(Room* room) {
    currentRoom = room;
}

int Character::getHealth() const {
    return health;
}

int Character::getStrength() const {
    return strength;
}

int Character::getDefense() const {
    return defense;
}

int Character::getEffectiveStrength() const {
    int bonus = 0;
    if (equippedWeapon) bonus += equippedWeapon->getStrength();
    if (equippedShield) bonus += equippedShield->getStrength();
    return strength + bonus;
}

int Character::getEffectiveDefense() const {
    int bonus = 0;
    if (equippedWeapon) bonus += equippedWeapon->getDefense();
    if (equippedShield) bonus += equippedShield->getDefense();
    return defense + bonus;
}

bool Character::isAlive() const {
    return health > 0;
}

// ---------------- Potion ----------------

void Character::applyPotionByName(const std::string& potionName) {
    std::string p = toLower(potionName);


    if (p == "healthpotion") {
        health += 10;
    } else if (p == "strengthpotion") {
        strength += 5;
    } else if (p == "defensepotion") {
        defense += 5;
    }
}

// ---------------- Equip rules ----------------

bool Character::canEquipItem(const Item* item) const {
    if (!item) return false;
    std::string n = toLower(item->getName());


    if (cls == ClassType::Warrior) {
        return (n == "sword" || n == "shield");
    }
    if (cls == ClassType::Thief) {
        return (n == "dagger");
    }
    return (n == "wand");
}

Character::EquipSlot Character::slotForItem(const Item* item) const {
    std::string n = toLower(item->getName());
    if (n == "shield") return EquipSlot::Shield;
    return EquipSlot::Weapon;
}

int Character::totalStatsWithItem(const Item* item) const {
    if (!item) return 0;
    return item->getHealth() + item->getStrength() + item->getDefense();
}

int Character::totalStatsOfEquipped(EquipSlot slot) const {
    Item* cur = (slot == EquipSlot::Weapon) ? equippedWeapon : equippedShield;
    return totalStatsWithItem(cur);
}

bool Character::tryEquip(Item* item) {
    if (!item) return false;

    if (!canEquipItem(item)) return false;

    EquipSlot slot = slotForItem(item);
    Item*& cur = (slot == EquipSlot::Weapon) ? equippedWeapon : equippedShield;

    if (!cur) {
        cur = item;
        return true;
    }

    int newTotal = totalStatsWithItem(item);
    int oldTotal = totalStatsWithItem(cur);

    if (newTotal > oldTotal) {
        delete cur;
        cur = item;
        return true;
    }

    return false;
}

// ---------------- Actions ----------------

void Character::move(const std::string& direction) {
    if (!currentRoom) {
        std::cout << name << " cannot move: not in dungeon.\n";
        return;
    }

    Room* next = currentRoom->getNeighbor(direction);
    if (!next) {
        std::cout << name << " tries to move " << direction << ": Failed (no connection).\n";
        return;
    }

    currentRoom = next;
    std::cout << name << " moves " << direction << " to " << currentRoom->getName() << ".\n";
}

void Character::pickUp(const std::string& itemName) {
    if (!currentRoom) {
        std::cout << name << " tries to pick up " << itemName << ": Failed (not in dungeon).\n";
        return;
    }

    if (!currentRoom->hasItem(itemName)) {
        std::cout << name << " tries to pick up " << itemName << ": Failed (item not in room).\n";
        return;
    }

    // Remove from room
    Item* item = currentRoom->takeItem(itemName);
    if (!item) {
        std::cout << name << " tries to pick up " << itemName << ": Failed.\n";
        return;
    }

    if (isPotionName(item->getName())) {
        applyPotionByName(item->getName());
        std::cout << name << " picks up " << item->getName() << ": Consumed.\n";
        delete item;
        return;
    }

    bool equipped = tryEquip(item);
    if (equipped) {
        std::cout << name << " picks up " << item->getName() << ": Equipped.\n";
        return;
    }

    currentRoom->addItem(item);
    std::cout << name << " picks up " << itemName << ": Failed (cannot equip or not better).\n";
}

void Character::fight(const std::string& monsterName) {
    if (!currentRoom) {
        std::cout << name << " fights " << monsterName << ": Failed (not in dungeon).\n";
        return;
    }

    Monster* m = currentRoom->getMonster(monsterName);
    if (!m) {
        std::cout << name << " fights " << monsterName << ": Failed (monster not in room).\n";
        return;
    }

    while (this->isAlive() && m->isAlive()) {
        // Player attack
        int dmgToMonster = std::max(1, this->getEffectiveStrength() - m->getDefense());
        m->takeDamage(dmgToMonster);

        if (!m->isAlive())
            break;

        // Monster attack
        int dmgToPlayer = std::max(1, m->getStrength() - this->getEffectiveDefense());
        health -= dmgToPlayer;
        if (health < 0) health = 0;
    }

    if (this->isAlive() && !m->isAlive()) {
        currentRoom->removeMonster(monsterName);
        std::cout << name << " fights " << monsterName << ": Victory\n";
    }
    else if (!this->isAlive()) {
        std::cout << name << " fights " << monsterName << ": Lose\n";
    }
}

// ---------------- Status ----------------

std::string Character::getStatus() const {
    std::ostringstream out;
    out << name << " (" << classToString(cls) << ") "
        << "HP=" << health
        << " STR=" << getEffectiveStrength()
        << " DEF=" << getEffectiveDefense()
        << " Room=" << (currentRoom ? currentRoom->getName() : "None")
        << " Weapon=" << (equippedWeapon ? equippedWeapon->getName() : "None")
        << " Shield=" << (equippedShield ? equippedShield->getName() : "None");
    return out.str();
}