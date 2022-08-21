#include "CleTeleportation.hpp"

bool CleTeleportation::exist = true;

CleTeleportation::CleTeleportation() : Objet("CleTeleportation", true){}

CleTeleportation::~CleTeleportation() { exist = false; }

void CleTeleportation::teleportToIa(){
    cout << "\n\t***censer se teleporter vers un ennemi pour combattre directement***" << endl;
}

CleTeleportation * CleTeleportation::forgeCleTeleportation(){
    if(!exist) return nullptr;
    return new CleTeleportation();
}

// ce serait son nombre d'utilisation
int CleTeleportation::getStat(){ return 1; }
