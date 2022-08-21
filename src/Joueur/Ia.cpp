#include "Ia.hpp"
#include "../Personnage/Personnage.hpp"

Ia::Ia(Personnage * p) : Joueur(p){}

Ia * Ia::forgeJoueurIa(int choix){
    return new Ia(Personnage::forgePersonnage(choix));
}

void Ia::takeObjet(int) {}

void Ia::dropObjet(int) {}

void Ia::stay(){}

void Ia::useObjet(int i){}

void Ia::move(){
    // on récupère d'abord les prochaines salles disponibles
    vector<Piece *> piecesVoisines = actualPiece->getPiecesVoisines();
    // choix aléa de la prochaine salle
    int cIa;
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> randChoix(0, 3); // écart de choix
    do{
        cIa = randChoix(gen);
    }while(piecesVoisines.at(cIa) == nullptr);

    actualPiece = actualPiece->updateMoveJoueur(cIa, this); // maj de la position de l'IA
}

void Ia::behave(){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> randChoix(0, 1); // écart de choix
    if(randChoix(gen) == 0) move();
    else stay();
}