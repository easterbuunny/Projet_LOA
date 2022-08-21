#ifndef HUMAIN_HPP
#define HUMAIN_HPP

#include <iostream>
#include "Joueur.hpp"

using namespace std;

class Humain : public Joueur{
private:
    Humain(Personnage *);
public:
    Humain(const Humain &) = delete;
    static Humain * forgeJoueurHumain(int);

    // action commun à tous Joueur
    virtual void takeObjet(int);
    virtual void dropObjet(int);
    virtual void useObjet(int);
    virtual void stay();
    virtual void move();

    // method que l'Humain peut utiliser
    bool amIAlone();
    bool fightRoom();
};

#endif //HUMAIN_HPP