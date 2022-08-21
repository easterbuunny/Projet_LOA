#ifndef POTION_HPP
#define POTION_HPP
#include <iostream>
#include "Objet.hpp"

using namespace std;

class Potion : public Objet{
    private :
        static bool exist;
        int heal;
        Potion();
    public :
        // création & dtor
        Potion(const Potion &) = delete;
        static Potion * forgePotion();
        virtual ~Potion();
        // methodes possibles par les autres classes
        virtual int getStat();
};

#endif /*POTION_HPP*/
