#include "Character.hpp"
#include "Monster.hpp"

Character::Character(char* newName, int newHealth, int newStrength,int newDefense):
          name(newName),health(newHealth),strength(newStrength),defense(newDefense){};

Character::Character(const Character& other): name(other.name),health(other.health),strength(other.strength),defense(other.defense){};

Character& Character:: operator=(const Character& other){
          if(this==&other) return *this;

          delete[]name;
          name=other.name;
          health=other.health;
          strength=other.strength;
          defense=other.defense;

          return *this;
}

Character::~Character(){
         delete[] name;
         name=nullptr;
}

void Character::attack(Monster& target){
          int dmg=strength-target.getDefense();
          if(dmg<1) dmg=1;
          target.takeDamage(dmg);
}

void Character::defend(int damage){
          health-=damage;
}

bool Character::isALive() const{
          return health>0;
}

Character Character::operator+(const Item& item){
          Character upgraded(*this);

          upgraded.health+= item.getHealthBonus();
          upgraded.strength+= item.getStrengthBonus();
          upgraded.defense+=item.getDefenseBonus();

          return upgraded;
}

//Getters
char* Character::getName() const {return name;}
int Character::getHealth() const { return health; }
int Character::getStrength() const { return strength; }
int Character::getDefense() const { return defense; }

//Setters
void Character::setHealth(int h) { health = h; }
void Character::setStrength(int s) { strength = s; }
void Character::setDefense(int d) { defense = d; }

