#include <fstream>
#include <random>
#include <typeinfo>

#include "../Joueur/Joueur.hpp"
#include "../Joueur/Humain.hpp"
#include "../Joueur/Ia.hpp"
#include "../Personnage/Personnage.hpp"

#include "Piece.hpp"
#include "../Objet/Objet.hpp"

// ctor & dtor;
int Piece::count = 0;
Piece::Piece() : id(count), visited(false), humainHere(false){ count++; }

// setter
void Piece::addObjet(Objet * obj) { objets.push_back(obj); }
void Piece::addNextPiece(Piece * & piece) { piecesVoisines.push_back(piece); }
void Piece::putJoueur(Joueur * & joueur) {
    if(dynamic_cast<Humain*>(joueur)){
        visited = true;
        humainHere = true;
    }
    joueurs.push_back(joueur);
}
void Piece::removeJoueur(Joueur * & joueur) { 
    for(int i = 0; i < (int)joueurs.size(); i++){
        // sachant que chaque joueur à un id
        if(joueur->getId() == joueurs.at(i)->getId()){
            joueurs.erase(joueurs.begin()+i);
            // On vérifie si le personnage enlevé est le joueur
            if(dynamic_cast<Humain*>(joueur))
                humainHere = false;
            break;
        }
    }
}

// getter
int Piece::getCount() {return count; }
const int Piece::getId() const { return id; }
vector<Piece *> Piece::getPiecesVoisines(){ return piecesVoisines; }
vector<Objet *> Piece::getObjets(){ return objets; }
vector<Joueur *> & Piece::getJoueurs(){ return joueurs; }

// == autre méthode ==
/* Dans cette fonction on met en hypothèse que la prochaine salle n'est pas vide
 * elle peut être vérifier lorsqu'on demande au joueur de choisir une salle */
Piece * Piece::updateMoveJoueur(int nextDoor, Joueur *joueur){
    // on enlève le personnage de la pièce
    removeJoueur(joueur);
    // on rajoute le personnage à la prochaine pièce
    piecesVoisines.at(nextDoor)->putJoueur(joueur);
    return piecesVoisines.at(nextDoor);
}

void Piece::updateJoueurDead(){
    for(int i = 0; i < (int)joueurs.size(); i++)
        if(!joueurs.at(i)->isAlive()) removeJoueur(joueurs.at(i));
}

ostream & operator<<(ostream & out, const Piece *p) {   
    out << "\n\t+++ Objets présents +++" << endl;
    if(p->objets.size() == 0) out << "Aucun objet ..." << endl;
    else{
        for(int i = 0; i < (int)p->objets.size(); i++){
            Objet * o = p->objets.at(i);
            if(o == nullptr) cout << "prblm ...";
            else out << "\t" << i+1 << "- " << o->getName() << endl;
        }
    }
    return out;
}