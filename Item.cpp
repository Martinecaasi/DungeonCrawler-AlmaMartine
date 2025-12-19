#include "Item.hpp"

Item::Item(char* newName,int newHealthB,int newStrengthB,int newDefenseB):
          name(newName),healthBonus(newHealthB),strengthBonus(newStrengthB),defenseBonus(newDefenseB){}

Item::Item(const Item& other):name(other.name),healthBonus(other.healthBonus),strengthBonus(other.strengthBonus),defenseBonus(other.defenseBonus){}

Item& Item::operator=(const Item& other){
          if(this==&other) return *this;

          delete[] name;
          name=other.name;
          healthBonus=other.healthBonus;
          strengthBonus=other.strengthBonus;
          defenseBonus=other.defenseBonus;

          return *this;
}

Item::~Item(){
          delete[] name;
          name=nullptr;
}

char* Item::getName() const{ return name;};
int Item::getHealthBonus()const{return healthBonus;};
int Item:: getStrengthBonus()const{return strengthBonus;};
int Item:: getDefenseBonus() const{return defenseBonus;};