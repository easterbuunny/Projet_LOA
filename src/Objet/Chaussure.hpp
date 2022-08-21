#ifndef CHAUSSURE_HPP
#define CHAUSSURE_HPP
#include <iostream>
#include <string>
#include "Objet.hpp"

using namespace std;

class Chaussure : public Objet {
    private :
        static bool exist;
        int hability;
        Chaussure();
    public :
        // création & dtor
        Chaussure(const Chaussure &) = delete;
        static Chaussure * forgeChaussure();
        virtual ~Chaussure();
        // methodes possibles par les autres classes
        virtual int getStat();
};

#endif /*CHAUSSURE_HPP*/