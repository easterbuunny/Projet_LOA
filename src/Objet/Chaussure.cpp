#include "Chaussure.hpp"

bool Chaussure::exist = true;

Chaussure::Chaussure() : Objet("Chaussure", false), hability{5}{}

Chaussure::~Chaussure() { exist = false; }

Chaussure * Chaussure::forgeChaussure(){
    if(!exist) return nullptr;
    return new Chaussure();
}

int Chaussure::getStat(){
    return hability;
}