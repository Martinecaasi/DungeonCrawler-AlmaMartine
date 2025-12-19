#pragma once
#include <cstring>

class Item
{
private:
          char* name;
          int healthBonus;
          int strengthBonus;
          int defenseBonus;
public:
//Def Con
Item(char* newName, int newHealthB, int newStrengthB, int newDefenseB);
//Cpy Con
Item(const Item& other);
//Deep Cpy
Item& operator=(const Item& other);
~Item();

//Getters
char* getName() const;
int getHealthBonus() const;
int getStrengthBonus() const;
int getDefenseBonus() const;
};


