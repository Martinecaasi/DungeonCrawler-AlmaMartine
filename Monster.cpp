#include "Monster.hpp"

Monster::Monster(const std::string& name, int health, int strength, int defense)
    : name(name), health(health), strength(strength), defense(defense) {}

const std::string& Monster::getName() const {
    return name;
}

int Monster::getHealth() const {
    return health;
}

int Monster::getStrength() const {
    return strength;
}

int Monster::getDefense() const {
    return defense;
}

void Monster::takeDamage(int damage) {
    if (damage < 0) damage = 0;
    health -= damage;
    if (health < 0)
        health = 0;
}

bool Monster::isAlive() const {
    return health > 0;
}