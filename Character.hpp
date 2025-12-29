#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <iostream>

#include "Room.hpp"
#include "Item.hpp"
#include "Monster.hpp"

class Character {
public:
    enum class ClassType { Warrior, Thief, Mage };
    enum class EquipSlot { Weapon, Shield };

private:
    std::string name;
    ClassType cls;

    int health;
    int strength;
    int defense;

    Room* currentRoom;

    Item* equippedWeapon;
    Item* equippedShield;

private:
    static std::string toLower(std::string s);

    static ClassType parseClass(const std::string& className);
    static std::string classToString(ClassType c);

    static void defaultStats(ClassType c, int& hp, int& str, int& def);

    static bool isPotionName(const std::string& itemName);
    static bool isWeaponName(const std::string& itemName);
    static bool isShieldName(const std::string& itemName);

    void applyPotionByName(const std::string& potionName);

    bool canEquipItem(const Item* item) const;
    EquipSlot slotForItem(const Item* item) const;

    int totalStatsWithItem(const Item* item) const;
    int totalStatsOfEquipped(EquipSlot slot) const;

    bool tryEquip(Item* item);

public:
    Character(const std::string& className, const std::string& name);
    ~Character();

    // Basics
    const std::string& getName() const;
    Room* getCurrentRoom() const;
    void setCurrentRoom(Room* room);

    int getHealth() const;
    int getStrength() const;
    int getDefense() const;

    int getEffectiveStrength() const;
    int getEffectiveDefense() const;

    bool isAlive() const;

    // Actions
    void move(const std::string& direction);
    void pickUp(const std::string& itemName);
    void fight(const std::string& monsterName);

    std::string getStatus() const;
};

#endif