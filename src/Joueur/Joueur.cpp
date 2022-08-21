#include "Joueur.hpp"
#include "../Donjon/Donjon.hpp"
#include "../Personnage/Personnage.hpp"
#include "Humain.hpp"
#include "Ia.hpp"

int Joueur::count = 0;

Joueur::Joueur(Personnage * p) : id(count), alive(true), personnage(p){ count++; }


// getter
const int Joueur::getId() const { return id; }
const Personnage * Joueur::getPersonnage() const { return personnage; }
const Piece * Joueur::getActualPiece() const { return actualPiece; }

// == method qu'un joueur peut utiliser ==
bool Joueur::isAlive() const { return alive; }

void Joueur::dead(){
    alive = false;
    cout << personnage->getName() << " est mort !" << endl;
    actualPiece->updateJoueurDead();
    actualDonjon->updateJoueurDead();
}

bool Joueur::isFasterThan(const Joueur * p) const {
    return personnage->getHabiltyPoint() > p->personnage->getHabiltyPoint();
}

/* true s'il a tué l'adversaire*/
bool Joueur::fight(Joueur * adv){
    Personnage * padv = adv->personnage;
    cout << '\t' << personnage->getName() << " attaque " << padv->getName() << " !!!\n";
    // -- l'ennemie essaie d'esquiver l'attaque --
    if(padv->tryDodge()){
        cout <<padv->getName() << " a esquive l'attaque!!!\n";
        return false;
    }
    // -- on attaque l'ennemie --
    cout << "PV " << padv->getName() << ' ' << padv->getHealthPoint() << " -> ";
    personnage->attack(padv);
    // -- on vérifie s'il est mort --
    if(padv->getHealthPoint() <= 0){
        cout << "0" << endl;
        adv->dead();
        return true;
    }
    cout << padv->getHealthPoint() << endl;
    return false;
}


