#include "Potion.hpp"

bool Potion::exist = true;

Potion::Potion() : Objet("Potion", true), heal(3){}

Potion::~Potion() { exist = false; }

Potion * Potion::forgePotion(){
    if(!exist) return nullptr;
    return new Potion();
}

int Potion::getStat(){ return heal; }
