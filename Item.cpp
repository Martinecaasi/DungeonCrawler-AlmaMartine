#include "Item.hpp"

Item::Item(const std::string& name, int health, int strength, int defense)
    : name(name),
      healthBonus(health),
      strengthBonus(strength),
      defenseBonus(defense) {}

const std::string& Item::getName() const {
    return name;
}

int Item::getHealth() const {
    return healthBonus;
}

int Item::getStrength() const {
    return strengthBonus;
}

int Item::getDefense() const {
    return defenseBonus;
}