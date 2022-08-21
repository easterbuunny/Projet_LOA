#ifndef GUERRIER_HPP
#define GUERRIER_HPP
#include "Personnage.hpp"

using namespace std;

class Guerrier : public Personnage {
    friend class Personnage;
    private:
        Guerrier();
    public :
        Guerrier(const Guerrier &) = delete;
        virtual ~Guerrier(){}
};

#endif /*GUERRIER_HPP*/