#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>

class Monster {
private:
    std::string name;
    int health;
    int strength;
    int defense;

public:
    Monster(const std::string& name, int health, int strength, int defense);

    const std::string& getName() const;
    int getHealth() const;
    int getStrength() const;
    int getDefense() const;

    void takeDamage(int damage);
    bool isAlive() const;
};

#endif