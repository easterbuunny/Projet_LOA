#ifndef ARME_HPP
#define ARME_HPP
#include <string>
#include <iostream>
#include "Objet.hpp"

using namespace std;

class Arme : public Objet{
    private :
        static bool exist;
        int attack;
        Arme();
    public :
        // création & dtor
        Arme(const Arme &) = delete;
        static Arme * forgeArme();
        virtual ~Arme();
        // methodes possibles par les autres classes
        virtual int getStat();
};

#endif /*ARME_HPP*/