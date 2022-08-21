#include "Armure.hpp"

bool Armure::exist = true;

Armure::Armure() : Objet("Armure", false), defence{1}{}

Armure::~Armure() { exist = false; }

Armure * Armure::forgeArmure(){
    if(!exist) return nullptr;
    return new Armure();
}

int Armure::getStat(){
    return defence;
}

