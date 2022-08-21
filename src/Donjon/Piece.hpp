#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include "Donjon.hpp"
#include "../Objet/Objet.hpp"

using namespace std;

class Joueur;
class Personnage;

class Piece {
friend Donjon;
private:
    static int count;
    const int id;
    bool visited; // cet attribut nous permet de savoir si le joueur a parcouru cette pièce
    bool humainHere; // true si le joueur est présent dans la pièce
    vector<Piece *> piecesVoisines; // 4 voisins {N,W,S,E}, nullptr si pas de voisin
    vector<Objet *> objets;  // les objest présents dans la salle
    vector<Joueur *> joueurs;   // les personnages présents dans la salle

    Piece();
    // == setter ==
    void addNextPiece(Piece * &);
    void putJoueur(Joueur * &);
    void removeJoueur(Joueur * &);
public:
    Piece(const Piece &) = delete;
    virtual ~Piece(){}

    // == getter ==
    static int getCount();
    const int getId() const;
    vector<Piece *> getPiecesVoisines();
    vector<Objet *> getObjets();
    vector<Joueur *> & getJoueurs();

    // == getter Question ==
    const bool isVisited() const {return visited; }
    const bool isHumainHere() const { return humainHere; }
    const bool isEmpty() const {return joueurs.empty(); }
    
    Objet & getObjetAt(int i) {
        Objet & o = *objets.at(i);
        objets.erase(objets.begin()+i);
        return o;
    }
    void addObjet(Objet *);

    const int getSizeObjets() const { return objets.size(); }
    const bool getVisited() const {return visited; }
    vector<Piece *> getVoisins(){ return piecesVoisines; }
    void setVisited(bool b){visited=b;}
    void setJoueurHere(bool b){humainHere=b;}
    
    // == autre methode ==
    Piece * updateMoveJoueur(int, Joueur *);// déplace un personnage de la piece a la piece voisine
    void updateJoueurDead(); // enlève un joueur de la piece
friend
    ostream & operator<<(ostream &, const Piece *);
};

#endif /*PIECE_HPP*/