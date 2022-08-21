#include "Arme.hpp"

bool Arme::exist = true;

Arme::Arme() : Objet("Arme", false), attack{1}{}

Arme::~Arme() { exist = false; }

Arme * Arme::forgeArme(){
    if(!exist) return nullptr;
    return new Arme();
}

int Arme::getStat(){
    return attack;
}