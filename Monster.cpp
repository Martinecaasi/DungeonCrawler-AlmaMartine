#include "Monster.hpp"
#include "Character.hpp"

Monster:: Monster(char* newName,int newHealth,int newStrength, int newDefense)
          : name(newName),health(newHealth),strength(newStrength),defense(newDefense){};

Monster:: Monster(const Monster& other): name(other.name),health(other.health),strength(other.strength),defense(other.defense){};

Monster& Monster::operator=(const Monster& other){
          if(this== &other) return *this;
          delete[]name;
          name=other.name;
          health=other.health;
          strength=other.strength;
          defense=other.defense;

          return *this;
};

Monster::~Monster(){
          delete[] name;
          name=nullptr;
}


void Monster:: attack(Character& target){
          int dmg= strength-target.getDefense();
          if(dmg<1) dmg=1;
          target.defend(dmg);
};

bool Monster::isDefeated() const{
          return health<=0;
}

char* Monster:: getName()const{ return name;};
int Monster:: getHealth()const{ return health;};
int Monster:: getStrength()const{ return strength;};
int Monster:: getDefense() const{ return defense; };

void Monster::takeDamage(int dmg){
          health-=dmg;
};