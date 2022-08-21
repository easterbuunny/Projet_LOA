#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <iostream>

#include "../Donjon/Donjon.hpp"

using namespace std;

class Personnage;
class Piece;

/* Abstrait */
class Joueur{
friend
    void Donjon::initJoueurPieceVide(Joueur *);
friend
    void Donjon::initJoueurPiece(int i , int j, int id, Joueur * p);
protected:
    static int count;
    // == caractéristique du Joueur ==
    int id;
    bool alive;
    Personnage * personnage;
    Donjon * actualDonjon;
    Piece * actualPiece;
    // == methodes cachées ==
    Joueur(Personnage *);
public:
    Joueur(const Joueur &) = delete;
    virtual ~Joueur(){}
    static Joueur * forgeJoueur(int);
    // == getter ==
    const int getId() const;
    const Personnage * getPersonnage() const;
    const Piece * getActualPiece() const;
    // == methodes qu"un joueur peut utiliser ==
    virtual void takeObjet(int) = 0;
    virtual void dropObjet(int) = 0;
    virtual void useObjet(int) = 0;
    virtual void stay() = 0;
    virtual void move() = 0;
    virtual bool fight(Joueur *);
    // == methode a utiliser a part ==
    bool isAlive() const;
    virtual void dead();
    bool isFasterThan(const Joueur *) const;

};

#endif // JOUEUR_HPP