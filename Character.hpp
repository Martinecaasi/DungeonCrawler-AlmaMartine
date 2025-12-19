#pragma once
#include <cstring>
#include "Item.hpp"

class Character
{
private:
          char* name;
          int health;
          int strength;
          int defense;
public:
          Character(char* newName,int newHealth,int newStrength, int newDefense);

          Character(const Character& other);
          Character& operator=(const Character& other);

          virtual ~Character();

          void attack(Monster& target);
          void defend(int damage);
          bool isALive() const;

          Character operator+(const Item& item);

          //Getters
          char* getName() const;
          int getHealth() const;
          int getStrength() const;
          int getDefense()const;

protected:

          void setHealth(int h);
          void setStrength(int s);
          void setDefense(int d);
};

