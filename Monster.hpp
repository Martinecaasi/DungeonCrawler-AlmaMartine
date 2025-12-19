#pragma once
#include <cstring>
#include "Character.hpp"

class Monster
{
private:
          char* name;
          int health;
          int strength;
          int defense;
public:
          Monster(char* newName,int newHealth, int newStrength, int newDefense);
          Monster(const Monster& other);
          Monster& operator=(const Monster& other);

          ~Monster();

          void attack(Character& target);
          
          bool isDefeated() const;

          //Getters
          char* getName() const;
          int getHealth()const;
          int getStrength() const;
          int getDefense() const;

          void takeDamage(int dmg);
};


