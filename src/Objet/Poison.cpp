#include "Poison.hpp"

using namespace std;

bool Poison::exist = true;

Poison::Poison() : Objet("Poison", true), damage(3){}

Poison::~Poison() { exist = false; }

void Poison::curseRandJoueur() { 
    cout << "\n\t***censer empoisonner un ennemi random***" << endl;
}

Poison * Poison::forgePoison(){
    if(!exist) return nullptr;
    return new Poison();
}

int Poison::getStat(){ return damage; }