#ifndef IA_HPP
#define IA_HPP

#include <iostream>
#include "Joueur.hpp"

using namespace std;

class Ia : public Joueur {
private:
    Ia(Personnage *);
public:
    Ia(const Ia &) = delete;
    static Ia * forgeJoueurIa(int);

    // method que l'ia peut utiliser
    virtual void takeObjet(int);
    virtual void dropObjet(int);
    virtual void useObjet(int);
    virtual void move();
    virtual void stay();
    void behave();
};

#endif //IA_HPP