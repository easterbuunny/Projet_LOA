#ifndef SORCIERE_HPP
#define SORCIERE_HPP
#include "Personnage.hpp"

using namespace std;

class Sorciere : public Personnage {
    friend class Personnage;
    private:
        Sorciere();
    public :
        Sorciere(const Sorciere &) = delete;
        virtual ~Sorciere(){}
};


#endif /*SORCIERE_HPP*/