#ifndef ARMURE_HPP
#define ARMURE_HPP
#include <string>
#include <iostream>
#include "Objet.hpp"

using namespace std;

class Armure : public Objet{
    private :
        static bool exist;
        int defence;
        Armure();
    public :
        // création & dtor
        Armure(const Armure &) = delete;
        static Armure * forgeArmure();
        virtual ~Armure();
        // methodes possibles par les autres classes
        virtual int getStat();
};

#endif /*ARMURE_HPP*/