#ifndef POISON_HPP
#define POISON_HPP
#include <iostream>
#include "Objet.hpp"

using namespace std;

class Poison : public Objet{
    private :
        static bool exist;
        int damage;
        Poison();
    public :
        // création & dtor
        Poison(const Poison &) = delete;
        static Poison * forgePoison();
        virtual ~Poison();
        void curseRandJoueur();
        // methodes possibles par les autres classes
        virtual int getStat();
};

#endif /*POISON_HPP*/