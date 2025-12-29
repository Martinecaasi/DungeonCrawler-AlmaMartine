#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
private:
    std::string name;
    int healthBonus;
    int strengthBonus;
    int defenseBonus;

public:
    Item(const std::string& name, int health, int strength, int defense);

    // Getters
    const std::string& getName() const;
    int getHealth() const;
    int getStrength() const;
    int getDefense() const;
};

#endif